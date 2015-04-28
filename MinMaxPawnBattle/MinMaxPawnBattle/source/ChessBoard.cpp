#include "ChessBoard.hpp"
#include "BitOperations.hpp"
#include <iostream>

ChessBoard::ChessBoard(const ChessBoard& other)
{
    for (int i = 0; i < Piece::NUM_COLORS; ++i)
    {
        for (int j = 0; j < Piece::NUM_TYPES; ++j)
        {
            board_[i][j] = other.board_[i][j];
        }
    }
    from_ = other.from_;
    to_ = other.to_;
}

ChessBoard::ChessBoard(const std::string& board)
{
    for (int i = 0; i < Piece::NUM_TYPES; ++i)
    {
        board_[Piece::WHITE][i] = 0;
        board_[Piece::BLACK][i] = 0;
    }
    int i = 7, j = 0; // strange configuration in the string
    for (char tile : board)
    {
        switch (tile)
        {
        case 'p':
            board_[Piece::BLACK][Piece::PAWN][j + i * 8] = 1;
            break;
        case 'P':
            board_[Piece::WHITE][Piece::PAWN][j + i * 8] = 1;
            break;
        case 'n':
            board_[Piece::BLACK][Piece::KNIGHT][j + i * 8] = 1;
            break;
        case 'N':
            board_[Piece::WHITE][Piece::KNIGHT][j + i * 8] = 1;
            break;
        case 'q': // Queen
            board_[Piece::BLACK][Piece::QUEEN][j + i * 8] = 1;
            break;
        case 'Q':
            board_[Piece::WHITE][Piece::QUEEN][j + i * 8] = 1;
            break;
        // default: leave boards as zero, unoccupied
        }
        // Move to next tile
        if (j < 7)
        {
            ++j;
        }
        else
        {
            j = 0;
            i -= 1;
        }
    }
    from_ = { 0, 0 };
    to_ = from_;
}

int ChessBoard::countPieces(Piece::Color color, Piece::Type type)
{
    uint64 pieces = board_[color][type].to_ullong();
    int count = 0;
    do
    {
        if (pieces)
            ++count;
        pieces = LS1BReset(pieces); // Remove last bit (last piece)
    } while (pieces);
    return count;
}

int ChessBoard::countPieces(Piece::Color color)
{
    int count = 0;
    for (int i = 0; i < Piece::NUM_TYPES; ++i)
        count += countPieces(color, Piece::Type(i));
    return count;
}

const std::bitset<64>& ChessBoard::operator()(Piece::Color color, Piece::Type type) const
{
    return board_[color][type];
}

std::bitset<64> ChessBoard::operator()(Piece::Color color) const
{
    std::bitset<64> result = 0;
    for (int i = 0; i < Piece::NUM_TYPES; ++i)
    {
        result = result | board_[color][i];
    }
    return result;
}

std::bitset<64> ChessBoard::occupied() const
{
    std::bitset<64> result = 0;
    for (int i = 0; i < Piece::NUM_COLORS; ++i)
    {
        for (int j = 0; j < Piece::NUM_TYPES; ++j)
        {
            result = result | board_[i][j];
        }
    }
    return result;
}

std::vector<ChessBoard> ChessBoard::generateMoves(Piece::Color team)
{
    std::vector<ChessBoard> moves;
    generatePawnMoves(team, moves);
    generateKnightMoves(team, moves);
    generateQueenMoves(team, moves);
    return moves;
}

void ChessBoard::generatePawnMoves(Piece::Color team, std::vector<ChessBoard>& moves)
{
    std::bitset<64> occupied_tiles = occupied();
    std::bitset<64> enemy_tiles = (*this)(Piece::otherTeam(team));
    int row_increment = (team == Piece::BLACK) ? -8 : 8;

    uint64 pawns_to_move = board_[team][Piece::PAWN].to_ullong(), current_pawn;
    while ( (current_pawn = LS1B(pawns_to_move)) != 0)
    {
        int current_index = bitScan(current_pawn);
        int push_pos = current_index + row_increment;
        int double_push_pos = push_pos + row_increment;
        int left_capture_pos = push_pos - 1;
        int left_x = push_pos % 8 - 1;
        int right_capture_pos = push_pos + 1;
        int right_x = push_pos % 8 + 1;

        // Normal push
        if (0 <= push_pos && push_pos < 64)
        {
            if (occupied_tiles[push_pos] == 0)
            {
                moves.push_back(ChessBoard(*this).makeMove(team, Piece::PAWN,
                    current_index, push_pos));
            }
        }
        // Captures
        if (0 <= left_capture_pos && left_capture_pos < 64 
            && 0 <= left_x && left_x < 8)
        {
            if (enemy_tiles[left_capture_pos] == 1)
            {
                moves.push_back(ChessBoard(*this).makeCapture(team, Piece::PAWN,
                    current_index, left_capture_pos));
            }
        }
        if (0 <= right_capture_pos && right_capture_pos < 64 
            && 0 <= right_x && right_x < 8)
        {
            if (enemy_tiles[right_capture_pos] == 1)
            {
                moves.push_back(ChessBoard(*this).makeCapture(team, Piece::PAWN,
                    current_index, right_capture_pos));
            }
        }

        // Double push move, check if pawn is in initial position
        if (0 <= push_pos && push_pos < 64
            && 0 <= double_push_pos && double_push_pos < 64)
        {
            if ((team == Piece::WHITE && (current_index <= 15)) ||
                (team == Piece::BLACK && (current_index >= 48)))
            {
                if (occupied_tiles[push_pos] == 0 &&
                    occupied_tiles[double_push_pos] == 0)
                {
                    moves.push_back(ChessBoard(*this).makeMove(team, Piece::PAWN,
                        current_index, double_push_pos));
                }
            }
        }
        pawns_to_move = LS1BReset(pawns_to_move);
    }
}

void ChessBoard::generateKnightMoves(Piece::Color team, std::vector<ChessBoard>& moves)
{
    std::bitset<64> occupied_tiles = occupied();
    std::bitset<64> enemy_tiles = (*this)(Piece::otherTeam(team));

    uint64 knights_to_move = board_[team][Piece::KNIGHT].to_ullong(), current_knight;
    while (knights_to_move != 0)
    {
        current_knight = LS1B(knights_to_move);
        int current_index = bitScan(current_knight);

        // Generate all possible knight moves
        int offset_y[8] = { -2, -2, -1, -1,  1, 1, 2, 2 };
        int offset_x[8] = { -1,  1, -2,  2, -2, 2, -1, 1 };
        for (int i = 0; i < 8;++i)
        {
            int new_pos = current_index+offset_x[i]+8*offset_y[i];
            int x_index = (current_index % 8) + offset_x[i];
            if (new_pos >= 0 && new_pos < 64 && x_index >=0 && x_index < 8 )
            {
                if (occupied_tiles[new_pos] == 0)
                {
                    moves.push_back(ChessBoard(*this).makeMove(team,
                        Piece::KNIGHT, current_index, new_pos));
                }
                else if (enemy_tiles[new_pos] == 1)
                {
                    moves.push_back(ChessBoard(*this).makeCapture(team,
                        Piece::KNIGHT, current_index, new_pos));
                }
            }
        }        
        knights_to_move = LS1BReset(knights_to_move);
    }
}

void ChessBoard::generateQueenMoves(Piece::Color team, std::vector<ChessBoard>& moves)
{
    std::bitset<64> occupied_tiles = occupied();
    std::bitset<64> enemy_tiles = (*this)(Piece::otherTeam(team));

    uint64 queen_board = board_[team][Piece::QUEEN].to_ullong();
    if (queen_board != 0)
    {
        int current_index = bitScan(queen_board);
        // Generate queen moves in each direction (N, NE, E, SE, S, SW, W, NW)
        int offset_y[8] = { 1, 1, 0, -1, -1, -1,  0,  1};
        int offset_x[8] = { 0, 1, 1,  1,  0, -1, -1, -1};
        for (int i = 0; i < 8; ++i)
        {
            int distance = 1;
            bool stop = false;
            do 
            {
                int next_pos = current_index + 
                    distance * ( (offset_x[i]) + (8 * offset_y[i]) );
                int x_index = (current_index % 8) + distance*offset_x[i];
                if (next_pos < 0 || 64 <= next_pos || x_index < 0 || 8 <= x_index)
                {
                    stop = true;
                }
                else if ( ! occupied_tiles[next_pos])
                {
                    moves.push_back(ChessBoard(*this).makeMove(team,
                        Piece::QUEEN, current_index, next_pos));
                }
                else // position occupied
                {
                    if (enemy_tiles[next_pos] == 1)
                    {
                        moves.push_back(ChessBoard(*this).makeCapture(team,
                            Piece::QUEEN, current_index, next_pos));
                    }
                    stop = true;
                }
                ++distance;
            } while ( !stop );
        }
    }
}

ChessBoard& ChessBoard::makeMove(Piece::Color team, Piece::Type type, int from, int to)
{
    board_[team][type][from] = 0;
    board_[team][type][to] = 1;
    setFromTo(from, to);
    return *this;
}

ChessBoard& ChessBoard::makeCapture(Piece::Color team, Piece::Type type, int from, int to)
{
    makeMove(team, type, from, to);
    for (int i = 0; i < Piece::NUM_TYPES; ++i)
    if (board_[Piece::otherTeam(team)][Piece::Type(i)][to] == 1)
        board_[Piece::otherTeam(team)][Piece::Type(i)][to] = 0;
    return *this;
}

void ChessBoard::setFromTo(int from, int to)
{
    from_.first = from / 8;
    from_.second = from % 8;
    to_.first = to / 8; 
    to_.second = to % 8;
}

int ChessBoard::materialEvaluation(Piece::Color team)
{
    Piece::Color other_team = Piece::otherTeam(team);
    const int queen_weight = 9, knight_weight = 3, pawn_weight = 1;
    int score =
        queen_weight * (countPieces(team, Piece::QUEEN) - countPieces(other_team, Piece::QUEEN)) +
        knight_weight * (countPieces(team, Piece::KNIGHT) - countPieces(other_team, Piece::KNIGHT)) +
        pawn_weight * (countPieces(team, Piece::PAWN) - countPieces(other_team, Piece::PAWN));
    return score;
}





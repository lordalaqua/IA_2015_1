#include "ChessBoard.hpp"
#include "BitOperations.hpp"
#include <array>

ChessBoard::ChessBoard(const ChessBoard& other)
{
    for (int i = 0; i < Piece::NUM_COLORS; ++i)
    {
        for (int j = 0; j < Piece::NUM_TYPES; ++j)
        {
            board_[i][j] = other.board_[i][j];
        }
    }
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
    for (int i = 0; i < Piece::NUM_TYPES; ++i)
    {
        switch ( Piece::Type(i) )
        {
        case Piece::PAWN:
            generatePawnMoves(team, moves);
            break;
        case Piece::KNIGHT:
            generateKnightMoves(team, moves);
            break;
        case Piece::QUEEN:
            generateQueenMoves(team, moves);
            break;
        }
    }
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
        int right_capture_pos = push_pos + 1;

        // Normal push
        if (occupied_tiles[push_pos] == 0)
        {
            moves.push_back(ChessBoard(*this).makeMove(team, Piece::PAWN,
                current_index, push_pos));
        }

        // Captures
        if (enemy_tiles[left_capture_pos] == 1)
        {
            moves.push_back(ChessBoard(*this).makeCapture(team, Piece::PAWN, 
                current_index, left_capture_pos));
        }
        if (enemy_tiles[right_capture_pos] == 1)
        {
            moves.push_back(ChessBoard(*this).makeCapture(team, Piece::PAWN, 
                current_index, right_capture_pos));
        }

        // Double push move, check if pawn is in initial position
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
        pawns_to_move = LS1BReset(pawns_to_move);
    }
}

void ChessBoard::generateKnightMoves(Piece::Color team, std::vector<ChessBoard>& moves)
{
    std::bitset<64> occupied_tiles = occupied();
    std::bitset<64> enemy_tiles = (*this)(Piece::otherTeam(team));
    int row_increment = (team == Piece::BLACK) ? -8 : 8;

    uint64 knights_to_move = board_[team][Piece::KNIGHT].to_ullong(), current_knight;
    while ((current_knight = LS1B(knights_to_move)) != 0)
    {
        int current_index = bitScan(current_knight);

        // Generate all possible knight moves
        std::array<int,4> offsets = { -4, -2, 2, 4 };
        for (int& offset_y : offsets)
        {
            for (int& offset_x : offsets)
            {
                int new_position = current_index + offset_x + 
                    row_increment * offset_y;
                if (new_position >= 0 && new_position < 64)
                {
                    if (occupied_tiles[new_position] == 0)
                    {
                        moves.push_back(ChessBoard(*this).makeMove(team, 
                            Piece::KNIGHT, current_index, new_position));
                    }
                    else if (enemy_tiles[new_position] == 1)
                    {
                        moves.push_back(ChessBoard(*this).makeCapture(team, 
                            Piece::KNIGHT, current_index, new_position));
                    }
                }
            }
        }
        
        knights_to_move = LS1BReset(knights_to_move);
    }
}

void ChessBoard::generateQueenMoves(Piece::Color team, std::vector<ChessBoard>& moves)
{

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
    from_ = { from / 8, from % 8 };
    to_ = { to / 8, to % 8 };
}





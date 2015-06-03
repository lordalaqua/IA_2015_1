#include "FirstBot.hpp"


void FirstBot::onMove(BoardState state)
{
    ChessBoard board(state.board);
    team_ = Piece::intToColor(state.who_moves);
    Play play = negamax(board, depth_, 1, team_, -INF, +INF);
    if (!sendMove(play.from, play.to))
    {
        std::cout << "Failed to send move" << std::endl;
    }
}

void FirstBot::onGameOver(BoardState state)
{
    if (state.draw)
        std::cout << "DRAW! Boooring!" << std::endl;
    else if (Piece::intToColor(state.winner) == team_)
        std::cout << "WE WON!" << std::endl;
    else
        std::cout << "WE LOST!" << std::endl;
}

FirstBot::Play FirstBot::negamax(const ChessBoard& node, int depth, int color, Piece::Color root_team, int alpha, int beta)
{
    int end = node.endGameTest();
    if (end != 0)
    {
        if (Piece::intToColor(end) == root_team)
            return Play(INF, node.from(), node.to());
        else
            return Play(-INF, node.from(), node.to());
     } // For some reason this generates invalid moves sometimes, check!
    if (depth == 0)
    {
        return Play(color*(50 * node.materialEvaluation(root_team) +
            node.positionEvaluation(root_team)), node.from(), node.to());
    }
    // Calculate possible moves
    std::vector<ChessBoard> moves; 
    if (color == 1)
        moves = node.generateMoves(root_team);
    else
        moves = node.generateMoves(Piece::otherTeam(root_team));
    if (moves.size() == 0)
    {
        return Play(color*(10*node.materialEvaluation(root_team) +
            node.positionEvaluation(root_team)), node.from(), node.to());
    }

    // Initialize best value
    int best_score = -INF;
    std::pair<int, int> best_from, best_to;
    // choose alpha or beta
    for (auto move : moves)
    {
        Play play = negamax(move, depth-1, -color, root_team, -beta, -alpha);
        int score = -play.score;
        if (score > best_score)
        {
            best_score = score;
            best_from = move.from();
            best_to = move.to();
        }
        alpha = std::max(alpha, score);
        if (alpha >= beta)
            break;
    }
    return Play(best_score, best_from, best_to);
}

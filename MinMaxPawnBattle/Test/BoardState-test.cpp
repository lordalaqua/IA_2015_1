#include <UnitTest++.h>
#include "BoardState.hpp"

TEST(BoardStateReadJSONTest)
{
    std::string json =
        "{ "
        "\"board\" : \"rnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR\","
        "\"enpassant\" : [[2,1],[3,1], [ 5 , 2  ] , [6,3]], "
        "\"who_moves\" : -1, "
        "\"bad_move\" : false, "
        "\"black_infractions\" : 20 , "
        "\"winner\" : -1,"
        "\"50moves\" : true,"
        "\"draw\" : false ,"
        "\"white_infractions\" : 10"
        "}";

    BoardState state(json);

    CHECK(state.board == "rnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR");
    CHECK(state.enpassant.size() == 0);
//     CHECK(state.enpassant[0] == std::make_pair(2, 1));
//     CHECK(state.enpassant[1] == std::make_pair(3, 1));
//     CHECK(state.enpassant[2] == std::make_pair(5, 2));
//     CHECK(state.enpassant[3] == std::make_pair(6, 3));
    CHECK(state.who_moves == -1);
    CHECK(state.bad_move == false);
    CHECK(state.black_infractions == 20);
    CHECK(state.winner == -1);
    CHECK(state.fifty_moves == true);
    CHECK(state.draw == false);
    CHECK(state.white_infractions == 10);

}
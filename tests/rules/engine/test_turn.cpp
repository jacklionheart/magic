// tests/test_turn.cpp
#include <gtest/gtest.h>
#include <memory>
#include "rules/engine/game.h"
#include "rules/engine/turn.h"
#include "rules/engine/player.h"

TEST(TurnTest, ExecuteTurn) {
    std::vector<Player> players;
    players.emplace_back("Player1", Deck());
    players.emplace_back("Player2", Deck());

    Game game(players);

    // Simulate a turn
    Turn turn = Turn(game.activePlayer(), game);
    // turn.execute();

    // // Check that the turn count has increased
    // EXPECT_EQ(game.global_turn_count, 1);

    // // Verify that the current player has changed
    // EXPECT_EQ(game.current_player, game.players[1]);
}
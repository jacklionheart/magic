// tests/rules/zones/test_stack.cpp

#include <gtest/gtest.h>
#include <memory>
#include "rules/zones/stack/stack.h"
#include "rules/zones/stack/spell.h"
#include "rules/cards/card.h"
#include "rules/engine/game.h"
#include "rules/engine/player.h"
#include "rules/engine/mana.h"          // Include Mana if needed
#include "rules/cards/ability.h"        // Include if using abilities

// Ensure all necessary headers are included
// If 'ManaAbility' or other dependencies are used, include their headers

TEST(StackTest, AddAndResolveSpell) {
    std::vector<Player> players;
    players.emplace_back("Player1", Deck());
    players.emplace_back("Player2", Deck());
    
     // Create a test spell
    Card test_spell(
        "Test Spell",
        std::nullopt,
        CardTypes({CardType::INSTANT}),
        std::vector<std::string>(),
        std::vector<std::string>(),
        std::vector<ManaAbility>(),
        "",
        std::nullopt,
        std::nullopt,
        players[0].id // Owner
    );


    players[0].deck.push_back(test_spell);


    // Create the game
    Game game(players);
    Player& player = game.players[0];

    // Cast the spell
    game.castSpell(player.id, test_spell);

    // Check stack size
    EXPECT_EQ(game.zones.stack.size(), 1);

    // Resolve the top spell
    game.zones.stack.resolveTop();

    // Check that the stack is now empty
    EXPECT_EQ(game.zones.stack.size(), 0);
}
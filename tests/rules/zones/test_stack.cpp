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
    Player player(0, "Player0");
    std::vector<Deck> decks;
    decks.push_back(Deck());
    decks.push_back(Deck());
     // Create a test spell
    auto test_spell = std::make_unique<Card>(
        "Test Spell",
        std::nullopt,
        CardTypes({CardType::INSTANT}),
        std::vector<std::string>(),
        std::vector<std::string>(),
        std::vector<ManaAbility>(),
        "",
        std::nullopt,
        std::nullopt,
        player // Owner
    );

    decks.push_back(std::make_unique<Deck>());
    decks[0]->cards.push_back(std::move(test_spell));
    test_spell_card = decks[0]->cards[0].get();
    decks.push_back(std::make_unique<Deck>());

    // Create the game
    Game game(decks);
    Player& player = game.players[0];

    // Add the spell to the player's hand
    game.zones.hand.move(*test_spell_card);

    // Cast the spell
    game.castSpell(player, *test_spell_card);

    // Check stack size
    EXPECT_EQ(game.zones.stack.size(), 1);

    // Resolve the top spell
    game.zones.stack.resolveTop();

    // Check that the stack is now empty
    EXPECT_EQ(game.zones.stack.size(), 0);
}
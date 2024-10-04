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
    // **1. Correct Decks Initialization**
    // Initialize decks as a vector of vectors of Card objects
    std::vector<std::vector<Card>> decks(2); // Two empty decks for two players

    // **2. Initialize the Game**
    // Create a Game instance with the initialized decks
    Game game(decks);

    // **3. Create a Test Card**
    // Create a Card object representing a spell (e.g., an Instant)
    // Assuming 'Player' objects are already initialized in the Game constructor
    // and that 'players[0]' is a valid reference
    Card test_spell(
        "Test Spell",                         // Name
        std::nullopt,                         // No mana cost
        CardTypes({CardType::INSTANT}),        // Card types (Instant)
        std::vector<std::string>(),           // Supertypes
        std::vector<std::string>(),           // Subtypes
        std::vector<ManaAbility>(),           // Mana abilities (empty)
        "",                                    // Text box
        std::nullopt,                         // Power
        std::nullopt,                         // Toughness
        game.activePlayer()                     // Owner (Player 0)
    );

    // **4. Cast the Spell**
    // Use the Game's castSpell method to add the spell to the stack
    game.castSpell(game.activePlayer(), test_spell);

    // **5. Check Stack Size After Casting**
    // Verify that the stack size is now 1
    EXPECT_EQ(game.zones.stack.size(), 1);

    // **6. Resolve the Top Spell**
    // Resolve the top spell on the stack
    game.zones.stack.resolveTop();

    // **7. Check Stack Size After Resolving**
    // Verify that the stack size is now 0
    EXPECT_EQ(game.zones.stack.size(), 0);
}
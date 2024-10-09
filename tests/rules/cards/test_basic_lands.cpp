// tests/rules/cards/test_basic_lands.cpp

#include <gtest/gtest.h>
#include "rules/cards/basic_lands.h"
#include "rules/engine/game.h"
#include "rules/engine/player.h"
#include "rules/engine/mana.h"
#include "rules/zones/battlefield/permanent.h"

TEST(BasicLandsTest, CreateBasicPlains) {
    Player owner(0, "TestPlayer");
    Card plains = *basicPlains(owner);

    // Test card properties
    EXPECT_EQ(plains.name, "Plains");
    EXPECT_TRUE(plains.types.types.count(CardType::LAND));
    EXPECT_EQ(plains.supertypes.size(), 1);
    EXPECT_EQ(plains.supertypes[0], "basic");
    EXPECT_EQ(plains.subtypes.size(), 1);
    EXPECT_EQ(plains.subtypes[0], "Plains");
    EXPECT_EQ(plains.text_box, "{T}: Add {W}.");
    EXPECT_EQ(plains.mana_abilities.size(), 1);

    // Test mana ability
    ManaAbility* ability = &plains.mana_abilities[0];
    Mana expected_mana;
    expected_mana.mana[Color::WHITE] = 1;
    EXPECT_EQ(ability->mana.mana, expected_mana.mana);
}

TEST(BasicLandsTest, ManaAbilityActivation) {
    // Initialize decks with smart pointers
    std::vector<Deck> decks;
    decks.push_back(Deck());
    decks.push_back(Deck());

    // Player 0's deck
    Player owner0(0, "Player0");
    decks[0].cards.push_back(basicForest(owner0));
    decks[0].cards.push_back(basicPlains(owner0));
    decks[0].cards.push_back(basicIsland(owner0));

    // Player 1's deck (empty)
    Player owner1(1, "Player1");

    // Create the game
    Game game(decks);
    Player& player = game.players[0];

    Card* forest_card = decks[0].cards[0].get();
    Card* plains_card = decks[0].cards[1].get();
    Card* island_card = decks[0].cards[2].get();

    EXPECT_TRUE(game.zones.hand.contains(forest_card, player));
    EXPECT_TRUE(game.zones.hand.contains(plains_card, player));
    EXPECT_TRUE(game.zones.hand.contains(island_card, player));

    // Play the forest
    game.playLand(player, *forest_card);

    // Find the Permanent representing the Forest
    Permanent* forest_permanent = game.zones.battlefield.find(*forest_card);
    ASSERT_NE(forest_permanent, nullptr);

    // Ensure the permanent is untapped and can tap
    EXPECT_FALSE(forest_permanent->tapped);
    EXPECT_TRUE(forest_permanent->canTap());

    // Activate the mana ability
    forest_permanent->activateAbility(&(forest_card->mana_abilities[0]), game);

    // Check that the permanent is now tapped
    EXPECT_TRUE(forest_permanent->tapped);

    // Check that the player's mana pool has the correct mana
    Mana expected_mana;
    expected_mana.mana[Color::GREEN] = 1;
    EXPECT_EQ(game.mana_pools[player.id].mana, expected_mana.mana);
}

TEST(BasicLandsTest, CannotActivateWhenTapped) {
    // Initialize decks with smart pointers
    std::vector<Deck> decks;
    decks.push_back(Deck());
    decks.push_back(Deck());

    // Player 0's deck
    Player owner0(0, "Player0");
    decks[0].cards.push_back(basicIsland(owner0));
    Card* island_card = decks[0].cards[0].get();
    decks[0].cards.push_back(basicSwamp(owner0));

    // Create the game
    Game game(decks);
    Player& player = game.players[0];

    ASSERT_NE(island_card, nullptr);

    EXPECT_TRUE(game.zones.hand.contains(island_card, player));

    // Play the island
    game.playLand(player, *island_card);

    // Find the Permanent representing the Island
    Permanent* island_permanent = game.zones.battlefield.find(*island_card);
    ASSERT_NE(island_permanent, nullptr);

    // Tap the permanent manually
    island_permanent->tap();
    EXPECT_TRUE(island_permanent->tapped);

    // Try to activate the mana ability (should not be able to)
    EXPECT_FALSE(island_permanent->canTap());
    EXPECT_THROW(
        island_permanent->activateAbility(&(island_card->mana_abilities[0]), game),
        std::logic_error
    );
}

TEST(BasicLandsTest, SummoningSicknessDoesNotAffectLands) {
    // Initialize decks with smart pointers
    std::vector<Deck> decks;
    decks.push_back(Deck());
    decks.push_back(Deck());

    // Player 0's deck
    Player owner0(0, "Player0");
    decks[0].cards.push_back(basicSwamp(owner0));
    decks[0].cards.push_back(basicForest(owner0));

    // Create the game
    Game game(decks);
    Player& player = game.players[0];

    Card* swamp_card = decks[0].cards[0].get();

    EXPECT_TRUE(game.zones.hand.contains(swamp_card, player));

    // Play the swamp
    game.playLand(player, *swamp_card);

    // Find the Permanent representing the Swamp
    Permanent* swamp_permanent = game.zones.battlefield.find(*swamp_card);
    ASSERT_NE(swamp_permanent, nullptr);

    // Lands should not have summoning sickness
    EXPECT_FALSE(swamp_permanent->summoning_sick);

    // Activate the mana ability successfully
    EXPECT_NO_THROW(
        swamp_permanent->activateAbility(&(swamp_card->mana_abilities[0]), game)
    );

    // Check that the player's mana pool has the correct mana
    Mana expected_mana;
    expected_mana.mana[Color::BLACK] = 1;
    EXPECT_EQ(game.mana_pools[player.id].mana, expected_mana.mana);
}

TEST(BasicLandsTest, PlayLandInGame) {
    // Initialize decks with smart pointers
    std::vector<Deck> decks;
    decks.push_back(Deck());
    decks.push_back(Deck());

    // Player 0's deck
    Player owner0(0, "Player0");
    decks[0].cards.push_back(basicPlains(owner0));
    decks[0].cards.push_back(basicIsland(owner0));
    decks[0].cards.push_back(basicSwamp(owner0));

    // Create the game
    Game game(decks);
    Player& player = game.players[0];

    // After Game constructor, the hand should have up to 7 cards
    ASSERT_EQ(game.zones.hand.cards[player.id].size(), 3);

    // Find the Plains and Island in the player's hand
    Card* plains_card = decks[0].cards[0].get();
    Card* island_card = decks[0].cards[1].get();

    EXPECT_TRUE(game.zones.hand.contains(plains_card, player));
    EXPECT_TRUE(game.zones.hand.contains(island_card, player));

    // Play the Plains
    game.playLand(player, *plains_card);

    // After playing, the Plains should be on the battlefield
    Permanent* plains_permanent = game.zones.battlefield.find(*plains_card);
    ASSERT_NE(plains_permanent, nullptr);

    // The hand should now have 2 cards
    EXPECT_EQ(game.zones.hand.cards[player.id].size(), 2);

    // Attempt to play the Island (second land this turn)
    EXPECT_THROW(
        game.playLand(player, *island_card),
        std::logic_error
    );
}
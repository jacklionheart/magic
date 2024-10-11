// tests/rules/cards/test_basic_lands.cpp

#include <gtest/gtest.h>
#include "rules/cards/basic_lands.h"
#include "rules/engine/game.h"
#include "rules/engine/player.h"
#include "rules/engine/mana.h"
#include "rules/zones/battlefield/permanent.h"

class BasicLandsTest : public ::testing::Test {
protected:
    std::vector<Player> players;
    std::unique_ptr<Game> game;
    Player* owner;

    void SetUp() override {
        Deck deck1, deck2;
        players.emplace_back("Player1", deck1);
        players.emplace_back("Player2", deck2);

        // Add basic lands to the first player's deck
        players[0].deck.push_back(basicPlains(players[0].id));
        players[0].deck.push_back(basicIsland(players[0].id));
        players[0].deck.push_back(basicSwamp(players[0].id));
        players[0].deck.push_back(basicMountain(players[0].id));
        players[0].deck.push_back(basicForest(players[0].id));

        // Add some cards to the second player's deck to make the game valid
        players[1].deck.push_back(basicPlains(players[1].id));
        players[1].deck.push_back(basicIsland(players[1].id));
        
        game = std::make_unique<Game>(players);
        owner = &players[0];

        // Debug output
        std::cout << "Player 1 hand contents:" << std::endl;
        for (const auto& card : game->zones.hand.cards[owner->id]) {
            std::cout << "  " << card->name << std::endl;
        }
        std::cout << "Total cards in hand: " << game->zones.hand.cards[owner->id].size() << std::endl;

    }

    Card* findCardInHand(const std::string& cardName) {
        for (Card* card : game->zones.hand.cards[owner->id]) {
            if (card->name == cardName) {
                return card;
            }
        }
        return nullptr;
    }
};

TEST_F(BasicLandsTest, CreateBasicPlains) {
    Card* plains = findCardInHand("Plains");
    ASSERT_NE(plains, nullptr);

    EXPECT_EQ(plains->name, "Plains");
    EXPECT_TRUE(plains->types.types.count(CardType::LAND));
    EXPECT_EQ(plains->supertypes.size(), 1);
    EXPECT_EQ(plains->supertypes[0], "basic");
    EXPECT_EQ(plains->subtypes.size(), 1);
    EXPECT_EQ(plains->subtypes[0], "Plains");
    EXPECT_EQ(plains->text_box, "{T}: Add {W}.");
    EXPECT_EQ(plains->mana_abilities.size(), 1);

    ManaAbility* ability = &plains->mana_abilities[0];
    Mana expected_mana;
    expected_mana.mana[Color::WHITE] = 1;
    EXPECT_EQ(ability->mana.mana, expected_mana.mana);
}

TEST_F(BasicLandsTest, ManaAbilityActivation) {
    Card* forest = findCardInHand("Forest");
    ASSERT_NE(forest, nullptr);
    
    EXPECT_TRUE(game->zones.hand.contains(*forest, owner->id));

    game->playLand(owner->id, *forest);

    Permanent* forest_permanent = game->zones.battlefield.find(*forest);
    ASSERT_NE(forest_permanent, nullptr);

    EXPECT_FALSE(forest_permanent->tapped);
    EXPECT_TRUE(forest_permanent->canTap());

    forest_permanent->activateAbility(&(forest->mana_abilities[0]), *game);

    EXPECT_TRUE(forest_permanent->tapped);

    Mana expected_mana;
    expected_mana.mana[Color::GREEN] = 1;
    EXPECT_EQ(game->mana_pools[owner->id].mana, expected_mana.mana);
}

TEST_F(BasicLandsTest, CannotActivateWhenTapped) {
    Card* island = findCardInHand("Island");
    ASSERT_NE(island, nullptr);
    
    EXPECT_TRUE(game->zones.hand.contains(*island, owner->id));

    game->playLand(owner->id, *island);

    Permanent* island_permanent = game->zones.battlefield.find(*island);
    ASSERT_NE(island_permanent, nullptr);

    island_permanent->tap();
    EXPECT_TRUE(island_permanent->tapped);

    EXPECT_FALSE(island_permanent->canTap());
    EXPECT_THROW(
        island_permanent->activateAbility(&(island->mana_abilities[0]), *game),
        std::logic_error
    );
}

TEST_F(BasicLandsTest, SummoningSicknessDoesNotAffectLands) {
    Card* swamp = findCardInHand("Swamp");
    ASSERT_NE(swamp, nullptr);
    
    EXPECT_TRUE(game->zones.hand.contains(*swamp, owner->id));

    game->playLand(owner->id, *swamp);

    Permanent* swamp_permanent = game->zones.battlefield.find(*swamp);
    ASSERT_NE(swamp_permanent, nullptr);

    EXPECT_FALSE(swamp_permanent->summoning_sick);

    EXPECT_NO_THROW(
        swamp_permanent->activateAbility(&(swamp->mana_abilities[0]), *game)
    );

    Mana expected_mana;
    expected_mana.mana[Color::BLACK] = 1;
    EXPECT_EQ(game->mana_pools[owner->id].mana, expected_mana.mana);
}

TEST_F(BasicLandsTest, PlayLandInGame) {
    Card* plains = findCardInHand("Plains");
    Card* island = findCardInHand("Island");
    ASSERT_NE(plains, nullptr);
    ASSERT_NE(island, nullptr);
    
    EXPECT_EQ(game->zones.hand.cards[owner->id].size(), 5);  // All 5 basic lands should be in hand

    EXPECT_TRUE(game->zones.hand.contains(*plains, owner->id));
    EXPECT_TRUE(game->zones.hand.contains(*island, owner->id));

    game->playLand(owner->id, *plains);

    Permanent* plains_permanent = game->zones.battlefield.find(*plains);
    ASSERT_NE(plains_permanent, nullptr);

    EXPECT_EQ(game->zones.hand.cards[owner->id].size(), 4);

    EXPECT_THROW(
        game->playLand(owner->id, *island),
        std::logic_error
    );
}
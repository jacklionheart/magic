// tests/rules/zones/test_zone.cpp

#include <gtest/gtest.h>
#include "rules/zones/zone.h"
#include "rules/engine/game.h"
#include "rules/cards/card.h"
#include "rules/engine/player.h"

class ZoneTest : public ::testing::Test {
protected:
    std::vector<Player> players;
    std::unique_ptr<Game> game;
    std::unique_ptr<Zone> zone;

    void SetUp() override {
        players.emplace_back("Player1", Deck());
        players.emplace_back("Player2", Deck());
        game = std::make_unique<Game>(players);
        zone = std::make_unique<Zone>(*game);
    }
};

TEST_F(ZoneTest, ContainsCard) {
    // Create a test card
    Card test_card("Test Card", std::nullopt, CardTypes(), {}, {}, {}, "", std::nullopt, std::nullopt, players[0].id);
    
    // Initially, the zone should not contain the card
    EXPECT_FALSE(zone->contains(test_card, players[0].id));

    // Add the card to the zone
    zone->move(test_card);

    // Now the zone should contain the card
    EXPECT_TRUE(zone->contains(test_card, players[0].id));

    // The zone should not report containing the card for a different player
    EXPECT_FALSE(zone->contains(test_card, players[1].id));

    // Create another card with the same name but different ID
    Card another_card("Test Card", std::nullopt, CardTypes(), {}, {}, {}, "", std::nullopt, std::nullopt, players[0].id);

    // The zone should not report containing this new card
    EXPECT_FALSE(zone->contains(another_card, players[0].id));
}

TEST_F(ZoneTest, RemoveCard) {
    Card test_card("Test Card", std::nullopt, CardTypes(), {}, {}, {}, "", std::nullopt, std::nullopt, players[0].id);
    
    zone->move(test_card);
    EXPECT_TRUE(zone->contains(test_card, players[0].id));

    zone->remove(test_card);
    EXPECT_FALSE(zone->contains(test_card, players[0].id));
}
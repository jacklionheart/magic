// tests/test_stack.cpp
#include <gtest/gtest.h>
#include <memory>
#include "rules/zones/stack/stack.h"
#include "rules/zones/stack/spell.h"
#include "rules/cards/card.h"
#include "rules/engine/game.h"
#include "rules/engine/player.h"

TEST(StackTest, AddAndResolveSpell) {
    // Set up a simple game and stack
    std::vector<Cards> decks(2); // Empty decks
    auto game = std::make_shared<Game>(decks);

    auto card = std::make_shared<Card>(
        "Test Spell",
        nullptr, // No mana cost
        CardTypes({CardType::INSTANT}),
        std::vector<std::string>(),
        std::vector<std::string>(),
        std::vector<std::shared_ptr<ActivatedAbilitySchema>>(),
        "",
        std::nullopt,
        std::nullopt,
        game->players[0]
    );

    auto spell = std::make_shared<Spell>(card);
    game->add_to_stack(spell);

    EXPECT_EQ(game->zones.stack.count(), 1);

    game->zones.stack.resolve_top();

    EXPECT_EQ(game->zones.stack.count(), 0);
}
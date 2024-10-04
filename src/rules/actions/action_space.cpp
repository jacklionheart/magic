#include "rules/actions/action_space.h"
#include "rules/engine/game.h" 
#include "rules/actions/action.h"
#include "rules/cards/card.h"
#include <cassert>


ActionSpace::ActionSpace(Game& game) : game(game) {}

std::vector<std::unique_ptr<Action>> ActionSpace::getActions(Player& player) {
    std::vector<std::unique_ptr<Action>> actions;

    // Get cards in hand
    std::vector<Card*> hand_cards = game.cardsInHand(player);

    for (Card* card : hand_cards) {
        assert(card != NULL && "card should never be null");
        if (card->types.isLand() && game.canPlayLand(player)) {
            actions.push_back(std::make_unique<PlayLand>(player, *card));
        } else if (card->types.isCastable() && game.isActivePlayer(player)) {
            // Assuming we can only cast spells during our turn
            actions.push_back(std::make_unique<CastSpell>(player, *card));
        }
    }

    // Always allow passing priority
    actions.push_back(std::make_unique<PassPriority>(player));

    return actions;
}
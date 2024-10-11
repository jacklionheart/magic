// action.cpp
#include "rules/actions/action.h"
#include "rules/engine/game.h"
#include "rules/zones/stack/spell.h"

Action::Action(int player_id) : player_id(player_id) {}

PlayLand::PlayLand(int player_id, Card& card) : Action(player_id), card(card) {
    if (!card.types.isLand()) {
        throw std::invalid_argument("Card is not a land.");
    }
}

void PlayLand::execute(Game& game) {
    game.playLand(player_id, card);
}

CastSpell::CastSpell(int player_id, Card& card) : Action(player_id), card(card) {
    if (!card.types.isCastable()) {
        throw std::invalid_argument("Cannot cast a land card.");
    }
}

void CastSpell::execute(Game& game) {
    game.castSpell(player_id, card);
}

PassPriority::PassPriority(int player_id) : Action(player_id) {
    retainPriority = false;
}

void PassPriority::execute(Game& game) {
}

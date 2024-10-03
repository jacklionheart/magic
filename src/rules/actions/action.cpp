// action.cpp
#include "rules/actions/action.h"
#include "rules/engine/game.h"
#include "rules/zones/stack/spell.h"


PlayLand::PlayLand(Card& card) : card(card) {
    if (!card.types.isLand()) {
        throw std::invalid_argument("Card is not a land.");
    }
}

void PlayLand::execute(Game& game) {
    game.playLand(card);
}

CastSpell::CastSpell(Card& card) : card(card) {
    if (!card.types.isCastable()) {
        throw std::invalid_argument("Cannot cast a land card.");
    }
}

void CastSpell::execute(Game& game) {
    game.castSpell(card);
}

PassPriority::PassPriority() {
    retainPriority = false;
}

void PassPriority::execute(Game& /*game*/) {
    // Do nothing
}
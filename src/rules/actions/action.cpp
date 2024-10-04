// action.cpp
#include "rules/actions/action.h"
#include "rules/engine/game.h"
#include "rules/zones/stack/spell.h"

Action::Action(Player& player) : player(player) {}

PlayLand::PlayLand(Player& player, Card& card) : Action(player), card(card) {
    if (!card.types.isLand()) {
        throw std::invalid_argument("Card is not a land.");
    }
}

void PlayLand::execute(Game& game) {
    game.playLand(player, card);
}

CastSpell::CastSpell(Player& player, Card& card) : Action(player), card(card) {
    if (!card.types.isCastable()) {
        throw std::invalid_argument("Cannot cast a land card.");
    }
}

void CastSpell::execute(Game& game) {
    game.castSpell(player, card);
}

PassPriority::PassPriority(Player& player) : Action(player) {
    retainPriority = false;
}

void PassPriority::execute(Game& /*game*/) {
}
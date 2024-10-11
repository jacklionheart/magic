// spell.cpp
#include "spell.h"
#include "rules/engine/game.h"
#include "rules/cards/card.h"
#include <cassert>
#include <stdexcept>

int Spell::next_id = 0;

Spell::Spell(Card& card)
    : id(next_id++), card_id(card.id), controller_id(card.owner_id) {}

void Spell::resolve(Game& game) {
    Card& card = game.card(card_id);
    if (card.types.isPermanent()) {
        game.zones.battlefield.enter(card);
    } else {
        // Implement logic for instants and sorceries
        // For now, we simply log the event
    }
}
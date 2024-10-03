// spell.cpp
#include "spell.h"
#include "rules/engine/game.h"
#include "rules/zones/battlefield/permanent.h"

Spell::Spell(Card& card)
    : card(card), controller(card.owner) {}

void Spell::resolve(Game& game) {
    if (card.types.isPermanent()) {
        game.zones.battlefield.enter(card);
    } else {
        // Implement logic for instants and sorceries
        // For now, we simply log the event
    }
}
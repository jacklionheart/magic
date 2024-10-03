// zone.cpp
#include "rules/zones/zone.h"
#include "rules/engine/game.h"
#include "rules/cards/card.h"
#include <cassert>
#include <format>
Zone::Zone(Game& game) : game(game) {
    for (const Player& player : game.players) {
        cards[player.id] = std::vector<Card*>();
    }
}

void Zone::add(Card& card) {
    card.current_zone = this;
    cards[card.owner.id].push_back(&card);
}

void Zone::remove(Card& card) {
    if (card.current_zone == this) {
        card.current_zone = nullptr;
        std::vector<Card*> player_cards = cards[card.owner.id];
        player_cards.erase(std::remove(player_cards.begin(), player_cards.end(), &card), player_cards.end());
    } else {
        throw std::invalid_argument(std::format("Card {} is not in this zone {}.", card.toString(), std::string(typeid(*this).name())));
    }
}

size_t Zone::numCards(Player& player) const {
    std::vector<Card*> player_cards = cards.at(player.id);
    return player_cards.size();
}

Library::Library(Game& game) : Zone(game) {}
Graveyard::Graveyard(Game& game) : Zone(game) {}
Hand::Hand(Game& game) : Zone(game) {}
Exile::Exile(Game& game) : Zone(game) {}
Command::Command(Game& game) : Zone(game) {}
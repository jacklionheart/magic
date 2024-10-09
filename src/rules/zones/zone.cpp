// zone.cpp
#include "rules/zones/zone.h"
#include "rules/engine/game.h"
#include "rules/cards/card.h"
#include <cassert>
#include <algorithm>  // For std::shuffle
#include <random>     // For random number generators
#include <format>
Zone::Zone(Game& game) : game(game) {
    for (const Player& player : game.players) {
        cards[player.id] = std::vector<Card*>();
    }
}

void Zone::move(Card& card) {
    if (card.current_zone) {
        Zone* previous_zone = card.current_zone;
        if (previous_zone == this) {
            throw std::logic_error(std::format("Card {} is already in this zone {}", card.toString(), std::string(typeid(*this).name())));
        }
        previous_zone->remove(card);
        assert(!previous_zone->contains(&card, card.owner));
    }
    card.current_zone = this;
    cards[card.owner.id].push_back(&card);
    assert(contains(&card, card.owner));
}

void Zone::remove(Card& card) {
    if (card.current_zone == this) {
        card.current_zone = nullptr;
        std::vector<Card*> player_cards = cards[card.owner.id];
        player_cards.erase(std::remove(player_cards.begin(), player_cards.end(), &card), player_cards.end());
        assert(!contains(&card, card.owner));
    } else {
        throw std::invalid_argument(std::format("Card {} is not in this zone {}.", card.toString(), std::string(typeid(*this).name())));
    }
}

bool Zone::contains(Card* card, Player& player) const {
    return std::find(cards.at(player.id).begin(), cards.at(player.id).end(), card) != cards.at(player.id).end();
}   

void Library::shuffle(const Player& player) {
    std::vector<Card*> player_cards = cards[player.id];
    std::shuffle(player_cards.begin(), player_cards.end(), std::mt19937(std::random_device()()));
}

Card* Library::top(const Player& player) {
    std::vector<Card*> player_cards = cards[player.id];
    return player_cards.back();
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
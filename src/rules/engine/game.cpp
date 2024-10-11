// game.cpp

#include "game.h"
#include "rules/engine/player.h"
#include "rules/actions/action.h"
#include "rules/actions/action_space.h"
#include "rules/zones/stack/spell.h"
#include "rules/zones/battlefield/permanent.h"
#include "rules/zones/zone.h"
#include "rules/zones/stack/stack.h"
#include "rules/engine/turn.h"


#include <algorithm>
#include <stdexcept>
#include <cassert>

Zones::Zones(Game& game)
    : graveyard(game),
      hand(game),
      library(game),
      battlefield(game),
      stack(game),
      exile(game),
      command(game)
{}

Game::Game(std::vector<Player>& players) : players(players), zones(*this), action_space(*this) {
    if (this->players.size() != 2) {
        throw std::invalid_argument("Game must start with 2 players.");
    }

    // Initialize mana pools and turn counts
    for (const Player& player : this->players) {
        mana_pools[player.id] = Mana();
        player_turn_counts[player.id] = 0;
    }

    // Initialize cards map
    for (Player& player : this->players) {
        for (Card& card : player.deck) {
            cards[card.id] = &card;
        }
    }

    // Initialize libraries with the decks, then draw up to 7 cards
    for (Player& player : this->players) {
        Deck& deck = player.deck;
        for (Card& card : deck) {
            zones.library.move(card);
        }

        zones.library.shuffle(player);

        int starting_hand_size = std::min<int>(7, zones.library.numCards(player));
        for (int i = 0; i < starting_hand_size; ++i) {
            zones.hand.move(*zones.library.top(player));
        }
    }

    global_turn_count = 0;
    active_player_index = 0;
    lands_played = 0;
}

void Game::play() {
    while (!isGameOver()) {
        current_turn = std::make_unique<Turn>(activePlayer(), *this);
        player_turn_counts[active_player_index]++;
        global_turn_count++;
        current_turn->execute();

        // Move to the next player
        active_player_index = (active_player_index + 1) % players.size();
    }
}

bool Game::isGameOver() const {
    return global_turn_count > 10;
}

void Game::clearManaPools() {
    for (auto& [player, mana_pool] : mana_pools) {
        mana_pool.clear();
    }
}

void Game::grantPriority() {
    for (Player& player : players) {
        while (true) {
            // Logger::info(player->name + " receives priority.");
            std::unique_ptr<Action> action = player.receivePriority(*this);
            action->execute(*this);
            if (!action->retainPriority) {
                break;
            }
        }
    }
}

void Game::allowPlayerActions() {
    while (true) {
        grantPriority();
        if (zones.stack.size() > 0) {
            zones.stack.resolveTop();
        } else {
            break;
        }
    }
}


std::vector<Card*> Game::cardsInHand(int player_id) {
    return zones.hand.cards[player_id];
}

Player& Game::activePlayer() {
    return players.at(active_player_index);
}

Card& Game::card(int id) {
    return *cards.at(id);
}

bool Game::isActivePlayer(int player_id) const {
    return player_id == players.at(active_player_index).id;
}

bool Game::canPlayLand(int player_id) const {
    return isActivePlayer(player_id) && lands_played < 1;
}

// Game State Mutations

void Game::addMana(int player_id, const Mana& mana) {
    mana_pools[player_id].add(mana);
}

void Game::castSpell(int player_id, Card& card) {
    if (card.types.isLand()) {
        throw std::invalid_argument("Land cards cannot be cast.");
    }
    if (card.owner_id != player_id) {
        throw std::invalid_argument("Card does not belong to player.");
    }
    zones.stack.cast(card);   
}

void Game::playLand(int player_id, Card& card) {
    if (!card.types.isLand()) {
        throw std::invalid_argument("Only land cards can be played.");
    }
    if (!canPlayLand(player_id)) {
        throw std::logic_error("Cannot play land this turn.");
    }
    lands_played += 1;
    zones.battlefield.enter(card);
}
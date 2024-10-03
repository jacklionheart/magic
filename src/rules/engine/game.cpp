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

Game::Game(const []Card decks) : zones(*this), action_space(*this) {
    assert(decks.size() == 2);
    // Initialize players
    for (size_t i = 0; i < decks.size(); ++i) {
        players.push_back(Player(static_cast<int>(i), "Player " + std::to_string(i)));
    }

    // Initialize mana pools and turn counts
    for (const Player& player : players) {
        mana_pools[player.id] = Mana();
        player_turn_counts[player.id] = 0;
    }
    global_turn_count = 0;
    current_player_index = 0;
    lands_played = 0;
}

void Game::play() {
    while (!isGameOver()) {
        current_turn = std::make_unique<Turn>(players[current_player_index], *this);
        player_turn_counts[current_player_index]++;
        global_turn_count++;
        current_turn->execute();

        // Move to the next player
        current_player_index = (current_player_index + 1) % players.size();
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


std::vector<Card*> Game::cardsInHand(Player& player) {
    return zones.hand.cards[player.id];
}

bool Game::isActivePlayer(Player& player) const {
    return player == players[current_player_index];
}

bool Game::canPlayLand(Player& player) const {
    return isActivePlayer(player) && lands_played < 1;
}

// Game State Mutations

void Game::addMana(Player& player, const Mana& mana) {
    mana_pools[player.id].add(mana);
}

void Game::castSpell(Card& card) {
    if (card.types.isLand()) {
        throw std::invalid_argument("Land cards cannot be cast.");
    }
    zones.stack.cast(card);   
}

void Game::playLand(Card& card) {
    if (!card.types.isLand()) {
        throw std::invalid_argument("Only land cards can be played.");
    }
    if (!canPlayLand(players[current_player_index])) {
        throw std::logic_error("Cannot play land this turn.");
    }
    lands_played += 1;
    zones.battlefield.enter(card);
}
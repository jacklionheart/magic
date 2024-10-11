// player.cpp
#include "player.h"
#include "rules/engine/game.h"
#include "rules/actions/action_space.h"

int Player::next_id = 0;
Player::Player(const std::string& name, Deck deck)
    : id(next_id++), name(name), life(20), deck(deck) {}

bool Player::operator==(const Player& other) const {
    return id == other.id;
}

size_t Player::hash() const {
    return std::hash<int>()(id);
}

std::unique_ptr<Action> Player::receivePriority(Game& game) {
    std::vector<std::unique_ptr<Action>> actions = game.action_space.getActions(id);
    // For simplicity, return the first action
    return std::move(actions.front());
}

std::string Player::toString() const {
    return name + " (Player " + std::to_string(id) + " - Life: " + std::to_string(life) + ")";
}
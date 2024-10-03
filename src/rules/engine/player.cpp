// player.cpp
#include "player.h"
#include "rules/engine/game.h"
#include "rules/actions/action_space.h"

Player::Player(int id, const std::string& name)
    : id(id), name(name), life(20) {}

bool Player::operator==(const Player& other) const {
    return id == other.id;
}

size_t Player::hash() const {
    return std::hash<int>()(id);
}

std::unique_ptr<Action> Player::receivePriority(Game& game) {
    std::vector<std::unique_ptr<Action>> actions = game.action_space.getActions(*this);
    // For simplicity, return the first action
    return std::move(actions.front());
}

std::string Player::toString() const {
    return name + " (Player " + std::to_string(id) + " - Life: " + std::to_string(life) + ")";
}
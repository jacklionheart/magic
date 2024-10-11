// action_space.h
#pragma once 

#include <vector>
#include <memory>
#include "rules/actions/action.h"

// Forward declarations
class Game;
class Player;

class ActionSpace {
public:
    Game& game;

    ActionSpace(Game& game);

    std::vector<std::unique_ptr<Action>> getActions(int player_id);
};
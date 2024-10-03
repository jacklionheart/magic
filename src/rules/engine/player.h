#pragma once 

#include <string>
#include <memory>

class Game; // Forward Declaration
class Action;

class Player : public std::enable_shared_from_this<Player> {
public:
    int id;
    std::string name;
    int life;

    Player(int id, const std::string& name);

    bool operator==(const Player& other) const;
    size_t hash() const;

    std::unique_ptr<Action> receivePriority(Game& game);

    std::string toString() const;
};
#pragma once 

#include <string>
#include <memory>
#include "rules/cards/deck.h"

class Game; // Forward Declaration
class Action;


class Player {
public:
    static int next_id;
    int id;
    Deck deck;
    std::string name;
    int life;

    Player(const std::string& name, Deck deck);

    bool operator==(const Player& other) const;
    size_t hash() const;

    std::unique_ptr<Action> receivePriority(Game& game);

    std::string toString() const;
};
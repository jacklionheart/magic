// spell.h
#pragma once

#include <memory>
#include "rules/cards/card.h"
#include "rules/engine/player.h"

// Forward Declarations
class Game;
class Permanent;

class StackObject {
public:
    virtual void resolve(Game& game) = 0;
    virtual ~StackObject() = default;
};

class Spell : public StackObject {
public:
    Card& card;
    Player& controller;

    Spell(Card& card);

    void resolve(Game& game);
};
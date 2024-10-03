// action.h
#pragma once

#include <memory>

// Forward declarations
class Game;
class Card;

class Action {

public:
    bool retainPriority = true;

    virtual void execute(Game& game) = 0;
    virtual ~Action() = default;
};

class PlayLand : public Action {
public:
    Card& card;

    PlayLand(Card& card);

    void execute(Game& game) override;
};

class CastSpell : public Action {
public:
    Card& card;

    CastSpell(Card& card);

    void execute(Game& game) override;
};

class PassPriority : public Action {
public:
    PassPriority();

    void execute(Game& game) override;
};
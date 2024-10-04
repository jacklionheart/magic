// action.h
#pragma once

#include <memory>

// Forward declarations
class Game;
class Card;
class Player;
class Action {

public:
    Player& player;
    bool retainPriority = true;
    Action(Player& player);

    virtual void execute(Game& game) = 0;
    virtual ~Action() = default;
};

class PlayLand : public Action {
public:
    Card& card;

    PlayLand(Player& player, Card& card);

    void execute(Game& game) override;
};

class CastSpell : public Action {
public:
    Card& card;

    CastSpell(Player& player, Card& card);

    void execute(Game& game) override;
};

class PassPriority : public Action {
public:
    PassPriority(Player& player);

    void execute(Game& game) override;
};
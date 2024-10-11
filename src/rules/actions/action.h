// action.h
#pragma once

#include <memory>

// Forward declarations
class Game;
class Card;
class Player;
class Action {

public:
    int player_id;
    bool retainPriority = true;
    Action(int player_id);

    virtual void execute(Game& game) = 0;
    virtual ~Action() = default;
};

class PlayLand : public Action {
public:
    Card& card;

    PlayLand(int player_id, Card& card);

    void execute(Game& game) override;
};

class CastSpell : public Action {
public:
    Card& card;

    CastSpell(int player_id, Card& card);

    void execute(Game& game) override;
};

class PassPriority : public Action {
public:
    PassPriority(int player_id);

    void execute(Game& game) override;
};
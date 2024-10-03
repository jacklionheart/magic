#pragma once

#include "rules/engine/player.h"
#include <vector>
#include <memory>

class Game; // Forward declaration

class Step {
public:
    Game& game;
    Step(Game& game);

    virtual void execute();
    virtual ~Step() = default;
};

class Phase {
public:
    Game& game;
    Step* current_step;

    Phase(Game& game);

    virtual std::vector<std::unique_ptr<Step>> steps() = 0;
    virtual void execute();
    virtual ~Phase() = default;
};

class Turn {
public:
    Player& active_player;
    Phase* current_phase;
    Game& game;

    Turn(Player& player, Game& game);

    std::vector<std::unique_ptr<Phase>> phases();
    void execute();
};

// Define specific Steps and Phases

class BeginningOfCombat : public Step {
public:
    BeginningOfCombat(Game& game);
    void execute() override;
};

class DeclareAttackers : public Step {
public:
    DeclareAttackers(Game& game);
    void execute() override;
};

class DeclareBlockers : public Step {
public:
    DeclareBlockers(Game& game);
    void execute() override;
};

class CombatDamage : public Step {
public:
    CombatDamage(Game& game);
    void execute() override;
};

class EndOfCombat : public Step {
public:
    EndOfCombat(Game& game);
    void execute() override;
};

class CombatPhase : public Phase {
public:
    CombatPhase(Game& game);
    std::vector<std::unique_ptr<Step>> steps() override;
};
// turn.cpp
#include "rules/engine/turn.h"
#include "rules/engine/game.h"
#include "rules/zones/stack/spell.h"
#include "rules/engine/game.h"
#include "rules/zones/battlefield/permanent.h"
#include <spdlog/spdlog.h>

Step::Step(Game& game) : game(game) {}

void Step::execute() {
    game.allowPlayerActions();
    spdlog::info("Starting {}", std::string(typeid(*this).name()));
}

Phase::Phase(Game& game) : game(game) {}

void Phase::execute() {
    for (std::unique_ptr<Step>& step : steps()) {
        current_step = step.get();
        step->execute();
    }
}

Turn::Turn(Player& player, Game& game)
    : active_player(player), game(game) {}

std::vector<std::unique_ptr<Phase>> Turn::phases() {
    // Return the list of phases
    std::vector<std::unique_ptr<Phase>> phases;
    phases.push_back(std::make_unique<CombatPhase>(game));
    return phases;
}

void Turn::execute() {
    game.lands_played = 0;
    for (std::unique_ptr<Phase>& phase : phases()) {
        current_phase = phase.get();
        phase->execute();
    }
}

// Implementations of specific Steps

BeginningOfCombat::BeginningOfCombat(Game& game) : Step(game) {}

void BeginningOfCombat::execute() {
    Step::execute();
    // Additional logic for Beginning of Combat
}

DeclareAttackers::DeclareAttackers(Game& game) : Step(game) {}

void DeclareAttackers::execute() {
    Step::execute();
    // Logic for Declare Attackers
}

DeclareBlockers::DeclareBlockers(Game& game) : Step(game) {}

void DeclareBlockers::execute() {
    Step::execute();
    // Logic for Declare Blockers
}

CombatDamage::CombatDamage(Game& game) : Step(game) {}

void CombatDamage::execute() {
    Step::execute();
    // Logic for Combat Damage
}

EndOfCombat::EndOfCombat(Game& game) : Step(game) {}

void EndOfCombat::execute() {
    Step::execute();
    // Logic for End of Combat
}

CombatPhase::CombatPhase(Game& game) : Phase(game) {}

std::vector<std::unique_ptr<Step>> CombatPhase::steps() {
    std::vector<std::unique_ptr<Step>> steps;
    steps.push_back(std::make_unique<BeginningOfCombat>(game));
    steps.push_back(std::make_unique<DeclareAttackers>(game));
    steps.push_back(std::make_unique<DeclareBlockers>(game));
    steps.push_back(std::make_unique<CombatDamage>(game));
    steps.push_back(std::make_unique<EndOfCombat>(game));
    return steps;
}
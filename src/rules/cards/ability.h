#pragma once

#include <memory>
#include "rules/engine/mana.h"

// Forward Declarations
class Game;
class Permanent;
class Player;
class Card;

class ActivatedAbility {
public:
    Card& card;
    bool uses_stack;

    ActivatedAbility(Card& card);

    virtual void payCost(Permanent& permanent, Game& game) = 0;
    virtual bool canBeActivated(const Permanent& permanent, const Game& game) const = 0;
    virtual void resolve(Permanent& permanent, Game& game) = 0;
    virtual ~ActivatedAbility() = default;
};

class ManaAbility : public ActivatedAbility {
public:
    Mana mana;

    ManaAbility(const Mana& mana, Card& card);

    void payCost(Permanent& permanent, Game& game) override;
    bool canBeActivated(const Permanent& permanent, const Game& game) const override;
    void resolve(Permanent& permanent, Game& game) override;
};
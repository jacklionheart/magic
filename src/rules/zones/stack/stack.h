#pragma once

#include <vector>
#include <memory>
#include "rules/zones/zone.h"
#include "rules/zones/stack/spell.h"

class Game; // Forward declaration
class Card;

class Stack : public Zone {
public:
    std::vector<std::unique_ptr<Spell>> objects;

    Stack(Game& game);

    void cast(Card &);
    void resolveTop();

    virtual void add(Card& card) override;
    virtual void remove(Card& card) override;

    size_t size() const;
};

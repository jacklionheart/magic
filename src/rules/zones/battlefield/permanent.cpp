// permanent.cpp
#include "permanent.h"
#include "rules/engine/game.h"
#include <cassert>

Permanent::Permanent(Card& card) :
      controller(card.owner),
      card(card) {

    tapped = false;
    summoning_sick = card.types.isCreature();
    damage = 0;
}

bool Permanent::canTap() const {
    return !tapped && !(summoning_sick && card.types.isCreature());
}

void Permanent::untap() {
    tapped = false;
}

void Permanent::tap() {
    tapped = true;
}

void Permanent::receiveDamage(int dmg) {
    damage += dmg;
}

bool Permanent::hasLethalDamage() const {
    if (card.toughness.has_value()) {
        return damage >= card.toughness.value();
    }
    return false;
}

void Permanent::clearDamage() {
    damage = 0;
}

Mana Permanent::producableMana(Game& game) const {
    Mana totalMana;
    for (const ManaAbility& ability : card.mana_abilities) {
        if (ability.canBeActivated(*this, game)) {
            totalMana.add(ability.mana);
        }
    }
    return totalMana;
}

void Permanent::activateAllManaAbilities(Game& game) {
    for (ManaAbility& ability : card.mana_abilities) {
        if (ability.canBeActivated(*this, game)) {
            activateAbility(&ability, game);
        }
    }
}

void Permanent::activateAbility(ActivatedAbility* ability, Game& game) {
    assert(ability != nullptr);
    if (&ability->card != &card) {
        throw std::logic_error("Ability on a different card.");
    }
    if (!ability->canBeActivated(*this, game)) {
        throw std::logic_error("Ability cannot be activated.");
    }
    ability->payCost(*this, game);
    if (ability->uses_stack) {
        throw std::runtime_error("Implement me.");
        // TODO: Add to stack
        //game.addToStack(ability);
    } else {
        ability->resolve(*this, game);
    }
}
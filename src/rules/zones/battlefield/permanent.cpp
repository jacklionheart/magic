// permanent.cpp
#include "permanent.h"
#include "rules/engine/game.h"
#include <cassert>

int Permanent::next_id = 0;

Permanent::Permanent(Card& card) :
      controller_id(card.owner_id),
      id(next_id++),
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

bool Permanent::operator==(const Permanent& other) const {
    return this->id == other.id;
}

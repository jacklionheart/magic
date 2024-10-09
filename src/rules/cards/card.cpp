// card.cpp
#include "card.h"
#include "rules/zones/zone.h"
#include "util/uuid.h"
#include <format>

CardTypes::CardTypes(const std::set<CardType>& types) : types(types) {}

bool CardTypes::isPermanent() const {
    return types.count(CardType::CREATURE) ||
           types.count(CardType::LAND) ||
           types.count(CardType::ARTIFACT) ||
           types.count(CardType::ENCHANTMENT) ||
           types.count(CardType::PLANESWALKER) ||
           types.count(CardType::BATTLE);
}

bool CardTypes::isNonLandPermanent() const {
    return isPermanent() && !isLand();
}

bool CardTypes::isNonCreaturePermanent() const {
    return isPermanent() && !isCreature();
}

bool CardTypes::isCastable() const {
    return !isLand() && !types.empty();
}

bool CardTypes::isSpell() const {
    return types.contains(CardType::INSTANT) || types.contains(CardType::SORCERY);
}

bool CardTypes::isCreature() const {
    return types.contains(CardType::CREATURE);
}

bool CardTypes::isLand() const {
    return types.contains(CardType::LAND);
}

bool CardTypes::isPlaneswalker() const {
    return types.count(CardType::PLANESWALKER);
}

bool CardTypes::isEnchantment() const {
    return types.contains(CardType::ENCHANTMENT);
}

bool CardTypes::isArtifact() const {
    return types.contains(CardType::ARTIFACT);
}

bool CardTypes::isTribal() const {
    return types.contains(CardType::KINDRED);
}

bool CardTypes::isBattle() const {
    return types.contains(CardType::BATTLE);
}

Card::Card(const std::string& name,
           std::optional<ManaCost> mana_cost,
           const CardTypes& types,
           const std::vector<std::string>& supertypes,
           const std::vector<std::string>& subtypes,
           const std::vector<ManaAbility>& mana_abilities,
           const std::string& text_box,
           std::optional<int> power,
           std::optional<int> toughness,
           Player& owner)
    : name(name),
      mana_cost(mana_cost),
      types(types),
      supertypes(supertypes),
      subtypes(subtypes),
      mana_abilities(mana_abilities),
      text_box(text_box),
      power(power),
      toughness(toughness),
      owner(owner),
      current_zone(nullptr) {

    id = uuid::generate();

    if (mana_cost.has_value()) {
        colors = mana_cost->colors();
    } else {
        colors = Colors();
    }
}

void Card::removeFromCurrentZone() {
    if (current_zone) {
        current_zone->remove(*this);
    }
    current_zone = nullptr;
}

std::string Card::toString() const {
    return "{name: " + name + "}";
}


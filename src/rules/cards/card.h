#pragma once

#include <string>
#include <vector>
#include <set>
#include <memory>
#include <format>

#include "rules/engine/mana.h"
#include "rules/engine/player.h"
#include "rules/cards/ability.h"
#include "rules/cards/card.h"

class Zone; // Forward declaration
class ActivatedAbilitySchema;

enum class CardType {
    CREATURE,
    INSTANT,
    SORCERY,
    PLANESWALKER,
    LAND,
    ENCHANTMENT,
    ARTIFACT,
    KINDRED,
    BATTLE
};

class CardTypes {
public:
    std::set<CardType> types;

    CardTypes() = default;
    CardTypes(const std::set<CardType>& types);
    bool isCastable() const;
    bool isPermanent() const;
    bool isNonLandPermanent() const;
    bool isNonCreaturePermanent() const;
    bool isSpell() const;
    bool isCreature() const;
    bool isLand() const;
    bool isPlaneswalker() const;
    bool isEnchantment() const;
    bool isArtifact() const;
    bool isTribal() const;
    bool isBattle() const;
};

class Card : public std::enable_shared_from_this<Card> {
public:
    std::string name;
    std::optional<ManaCost> mana_cost;
    Colors colors;
    CardTypes types;
    std::vector<std::string> supertypes;
    std::vector<std::string> subtypes;
    std::vector<ManaAbility> mana_abilities;
    std::string text_box;
    std::optional<int> power;      // Use std::optional for optional values
    std::optional<int> toughness;
    Player& owner;
    Zone* current_zone;

    std::string toString() const;
    void removeFromCurrentZone();

    Card(const std::string& name,
         std::optional<ManaCost> mana_cost,
         const CardTypes& types,
         const std::vector<std::string>& supertypes,
         const std::vector<std::string>& subtypes,
         const std::vector<ManaAbility>& mana_abilities,
         const std::string& text_box,
         std::optional<int> power,
         std::optional<int> toughness,
         Player& owner);
};

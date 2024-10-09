// basic_lands.cpp
#include "basic_lands.h"

std::unique_ptr<Card> createBasicLandCard(const std::string& name, Color color, Player& owner) {

    // Create the ManaAbility for this basic land
    Mana mana;
    mana.mana[color] = 1;
    ManaAbility mana_ability(mana);


    // Create the card
    Card card(
        name,
        std::nullopt,     // No mana cost for basic lands
        CardTypes({CardType::LAND}),
        {"basic"},
        {name},
        {mana_ability},
        "{T}: Add {" + toString(color) + "}.",
        std::nullopt,     // No power
        std::nullopt,     // No toughness
        owner
    );

    return std::make_unique<Card>(card);
}

std::unique_ptr<Card> basicPlains(Player& owner) {
    return createBasicLandCard("Plains", Color::WHITE, owner);
}

std::unique_ptr<Card> basicIsland(Player& owner) {
    return createBasicLandCard("Island", Color::BLUE, owner);
}

std::unique_ptr<Card> basicMountain(Player& owner) {
    return createBasicLandCard("Mountain", Color::RED, owner);
}

std::unique_ptr<Card> basicForest(Player& owner) {
    return createBasicLandCard("Forest", Color::GREEN, owner);
}

std::unique_ptr<Card> basicSwamp(Player& owner) {
    return createBasicLandCard("Swamp", Color::BLACK, owner);
}
// basic_lands.cpp
#include "basic_lands.h"

Card createBasicLandCard(const std::string& name, Color color, int owner_id) {

    // Create the ManaAbility for this basic land
    Mana mana;
    mana.mana[color] = 1;
    ManaAbility mana_ability(mana);

    return Card(
        name,
        std::nullopt,     // No mana cost for basic lands
        CardTypes({CardType::LAND}),
        {"basic"},
        {name},
        {mana_ability},
        "{T}: Add {" + toString(color) + "}.",
        std::nullopt,     // No power
        std::nullopt,     // No toughness
        owner_id
    );
}
Card basicPlains(int owner_id) {
    return createBasicLandCard("Plains", Color::WHITE, owner_id);
}

Card basicIsland(int owner_id) {
    return createBasicLandCard("Island", Color::BLUE, owner_id);
}

Card basicMountain(int owner_id) {
    return createBasicLandCard("Mountain", Color::RED, owner_id);
}

Card basicForest(int owner_id) {
    return createBasicLandCard("Forest", Color::GREEN, owner_id);
}

Card basicSwamp(int owner_id) {
    return createBasicLandCard("Swamp", Color::BLACK, owner_id);
}
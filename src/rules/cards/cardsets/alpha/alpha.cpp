#include "rules/cards/cardsets/alpha/alpha.h"

Card llanowarElves(int owner_id) {
    return Card(
        "Llanowar Elves",
        ManaCost::parse("G"),
        CardTypes({CardType::CREATURE}),
        {"Elf", "Druid"},
        {m}
        "{T}: Add {G}.",
        1,     // Power
        1,     // No toughness
        owner_id
    );
}



    return Card(
        name,
        std::nullopt,     // No mana cost for basic lands
        CardTypes({CardType::LAND}),
        {"basic"},
        {name},
        {ManaAbility(Mana::single(color))},
        "{T}: Add {" + toString(color) + "}.",
        std::nullopt,     // No power
        std::nullopt,     // No toughness
        owner_id
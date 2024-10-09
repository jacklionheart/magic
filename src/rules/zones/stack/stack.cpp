// stack.cpp
#include "stack.h"
#include "rules/zones/stack/spell.h"

#include <format>

Stack::Stack(Game& game)
    : Zone(game) {}

void Stack::move(Card& card) {
    // simple alias for now. Maybe remove one day?
    cast(card);
}

void Stack::remove(Card& card) {
    Zone::remove(card);
    objects.erase(std::remove_if(objects.begin(), objects.end(),
        [&card](const std::unique_ptr<Spell>& spell) { return &spell->card == &card; }),
        objects.end()); 
}

void Stack::cast(Card& card) {
    if (card.current_zone != NULL && card.current_zone == this) {
        throw std::logic_error(std::format("Card {} already on the stack", card.toString()));
    }
    Zone::move(card);
    objects.push_back(std::make_unique<Spell>(card));
}

void Stack::resolveTop() {
    if (!objects.empty()) {
        std::unique_ptr<StackObject> object = std::move(objects.back());
        objects.pop_back();
        object->resolve(game);
    }
}

size_t Stack::size() const {
    return objects.size();
}
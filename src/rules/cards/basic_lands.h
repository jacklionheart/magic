// basic_lands.h
#pragma once

#include "rules/cards/card.h"
#include "rules/engine/player.h"
#include "rules/engine/mana.h"

#include <memory>
// Function declarations
std::unique_ptr<Card> createBasicLandCard(const std::string& name, Color color, Player& owner);

std::unique_ptr<Card> basicPlains(Player& owner);
std::unique_ptr<Card> basicIsland(Player& owner);
std::unique_ptr<Card> basicMountain(Player& owner);
std::unique_ptr<Card> basicForest(Player& owner);
std::unique_ptr<Card> basicSwamp(Player& owner);
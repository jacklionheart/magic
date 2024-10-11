// basic_lands.h
#pragma once

#include "rules/cards/card.h"
#include "rules/engine/player.h"
#include "rules/engine/mana.h"

#include <memory>
// Function declarations
Card createBasicLandCard(const std::string& name, Color color, int owner_id);

Card basicPlains(int owner_id);
Card basicIsland(int owner_id);
Card basicMountain(int owner_id);
Card basicForest(int owner_id);
Card basicSwamp(int owner_id);
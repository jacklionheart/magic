// src/main.cpp
#include <iostream>
#include <memory>
#include "rules/engine/game.h"
#include "rules/engine/player.h"
#include "rules/cards/card.h"  // Include this to use Card

int main() {
    // Create empty decks for two players
    std::vector<std::vector<Card>> decks(2);

    // Initialize the game
    Game game(decks);

    // Play the game
    game.play();

    std::cout << "Game has ended after " << game.global_turn_count << " turns." << std::endl;

    return 0;
}
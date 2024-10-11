// src/main.cpp
#include <iostream>
#include <memory>
#include "rules/engine/game.h"
#include "rules/engine/player.h"
#include "rules/cards/card.h"  // Include this to use Card

int main() {
    // Initialize the game
    std::vector<Player> players;
    players.emplace_back("Player1", Deck());
    players.emplace_back("Player2", Deck());
    Game game(players);

    // Play the game
    game.play();

    std::cout << "Game has ended after " << game.global_turn_count << " turns." << std::endl;

    return 0;
}
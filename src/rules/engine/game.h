// game.h
#pragma once

#include <vector>
#include <memory>
#include <map>

#include "rules/actions/action_space.h"
#include "rules/zones/zone.h"
#include "rules/zones/battlefield/battlefield.h"
#include "rules/zones/stack/stack.h"
#include "rules/cards/card.h"
#include "rules/engine/turn.h"

// Forward Declarations
class ActionSpace;
class Mana;
class StackObject;
class Permanent;

struct Zones {
public:
    Graveyard graveyard;
    Hand hand;
    Library library;
    Battlefield battlefield;
    Stack stack;
    Exile exile;
    Command command;

    Zones(Game& game);
};

struct Deck {
public:
    std::vector<std::unique_ptr<Card>> cards;
};

class Game {
public:
    std::vector<Player> players;
    ActionSpace action_space;
    Zones zones;
    std::unique_ptr<Turn> current_turn;
    int active_player_index;
    std::map<int, Mana> mana_pools;
    int lands_played;
    int global_turn_count;
    std::map<int, int> player_turn_counts;

    Game(const std::vector<Deck>& decks);

    void play();
    bool isGameOver() const;
    void clearManaPools();
    void grantPriority();
    void allowPlayerActions();

    // Lookups
    std::vector<Card*> cardsInHand(Player& player);
    Player& activePlayer();
    bool isActivePlayer(Player& player) const;
    bool canPlayLand(Player& player) const;

    // Game State Mutations
    void addMana(Player& player, const Mana& mana);
    void castSpell(Player& player, Card& card);
    void playLand(Player& player, Card& card);
};
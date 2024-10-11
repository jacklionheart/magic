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


class Game {
public:
    std::vector<Player>& players;
    std::map<int, Card*> cards;
    ActionSpace action_space;
    Zones zones;
    std::unique_ptr<Turn> current_turn;
    int active_player_index;
    std::map<int, Mana> mana_pools;
    int lands_played;
    int global_turn_count;
    std::map<int, int> player_turn_counts;

    Game(std::vector<Player>& players);

    void play();
    bool isGameOver() const;
    void clearManaPools();
    void grantPriority();
    void allowPlayerActions();

    // Lookups
    Card& card(int id);
    std::vector<Card*> cardsInHand(int player_id);
    Player& activePlayer();
    bool isActivePlayer(int player_id) const;
    bool canPlayLand(int player_id) const;

    // Game State Mutations
    void addMana(int player_id, const Mana& mana);
    void castSpell(int player_id, Card& card);
    void playLand(int player_id, Card& card);
};

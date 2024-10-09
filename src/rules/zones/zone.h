#pragma once

#include <vector>
#include <map>
#include <memory>

// Forward Declarations
class Card;
class Player;
class Game;

class Zone {
public:
    Game& game;
    virtual ~Zone() = default;

    Zone(Game& game);
    std::map<int, std::vector<Card*>> cards;

    virtual void move(Card& card);
    virtual void remove(Card& card);
    size_t numCards(Player& player) const;
    bool contains(Card* card, Player& player) const;
};

class Library : public Zone {
public:
    Library(Game& game);
    void shuffle(const Player& player);
    Card* top(const Player& player);
};

class Graveyard : public Zone {
public:
    Graveyard(Game& game);
};

class Hand : public Zone {
public:
    Hand(Game& game);
};

class Exile : public Zone {
public:
    Exile(Game& game);
};

class Command : public Zone {
public:
    Command(Game& game);
};


#pragma once

#include <string>
#include <map>
#include <set>

enum class Color {
    COLORLESS,
    WHITE,
    BLUE,
    BLACK,
    RED,
    GREEN
};

using Colors = std::set<Color>;

class ManaCost {
public:
    std::map<Color, int> cost;
    int generic;

    ManaCost();
    static ManaCost parse(const std::string& mana_cost_str);
    std::string toString() const;
    Colors colors() const;
    int manaValue() const;
};

class Mana {
public:
    std::map<Color, int> mana;

    Mana();
    void add(const Mana& other);
    int total() const;
    bool canPay(const ManaCost& mana_cost) const;
    void pay(const ManaCost& mana_cost);
    void clear();
    std::string toString() const;
};
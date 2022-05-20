#include "Character.h"

namespace mtm {
    Character::Character(Team team, units_t health, units_t ammo, units_t range, units_t power,
            units_t reload_value, units_t attack_cost, int max_movement_units, CharacterType type, char symbol) :
        team(team),
        health(health),
        ammo(ammo),
        range(range),
        power(power),
        reload_value(reload_value),
        attack_cost(attack_cost),
        max_movement_units(max_movement_units),
        type(type),
        symbol(symbol)
    {}

    Team Character::getTeam() const
    {
        return team;
    }

    CharacterType Character::getType() const
    {
        return type;
    }

    bool Character::isAlive()
    {
        return health > 0;
    }

    units_t Character::getAttackRange() const
    {
        return range;
    }

    int Character::getTravelDistance() const
    {
        return max_movement_units;
    }

    bool Character::exists(const Character& character)
    {
        return &character != nullptr;
    }

    void Character::addHealth(units_t value)
    {
        health += value;
    }

    void Character::reload()
    {
        ammo += reload_value;
    }

    bool Character::hasAmmoToAttack(const Character& other)
    {
        return ammo >= attack_cost;
    }

    bool Character::isInAttackRange2(const GridPoint& src, const GridPoint& dst)
    {
        return true;
    }

    char Character::convertToChar() const
    {
        return char(symbol + (team == CROSSFITTERS ? UPPER_TO_LOWER_DIFF : 0));
    }
}
#include "Soldier.h"

namespace mtm {

    Soldier::Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power) :
        Character(team, health, ammo, range, power, SOLDIER_RELOAD_VALUE,
                  SOLDIER_ATTACK_COST, SOLDIER_MAX_MOVEMENT_UNITS, SOLDIER, SOLDIER_SYMBOL)
    {}

    Character* Soldier::clone()
    {
        return new Soldier(*this);
    }

    bool Soldier::canAttackEmptyCell()
    {
        return true;
    }

    bool Soldier::isInAttackRange(const GridPoint& src, const GridPoint& dst)
    {
        return (GridPoint::distance(src, dst) <= range);
    }

    bool Soldier::isInAttackRange2(const GridPoint& src, const GridPoint& dst)
    {
        return (src.col == dst.col || src.row == dst.row);
    }

    bool Soldier::attack(Character& other)
    {
        if(Character::exists(other) && team != other.getTeam()) {
            other.addHealth(-power);
        }
        --ammo;
        return true;
    }

    void Soldier::attackNearbyCharacter(Character& other) const
    {
        if(team == other.getTeam()) {
            return;
        }

        other.addHealth(std::ceil(power * NEARBY_DAMAGE_FACTOR) * -1);
    }
}
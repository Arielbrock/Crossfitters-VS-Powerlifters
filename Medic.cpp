#include "Medic.h"

namespace mtm {

    Medic::Medic(Team team, units_t health, units_t ammo, units_t range, units_t power) :
        Character(team, health, ammo, range, power, MEDIC_RELOAD_VALUE,
                  MEDIC_ATTACK_COST, MEDIC_MAX_MOVEMENT_UNITS, MEDIC, MEDIC_SYMBOL)
    {}

    Character* Medic::clone()
    {
        return new Medic(*this);
    }

    bool Medic::canAttackEmptyCell()
    {
        return false;
    }

    bool Medic::isInAttackRange(const GridPoint& src, const GridPoint& dst)
    {
        return (GridPoint::distance(src, dst) <= range);
    }

    bool Medic::hasAmmoToAttack(const Character& other)
    {
        if (Character::exists(other)) {
            return (team == other.getTeam() || ammo >= attack_cost);
        }
        else {
            return ammo > 0;
        }
    }

    bool Medic::attack(Character& other)
    {
        if (!Character::exists(other) || this == &other)  {
            return false;
        }

        if (team == other.getTeam())  {
            other.addHealth(power);
        }
        else {
            other.addHealth(-power);
            --ammo; 
        }
        return true;
    }        
}

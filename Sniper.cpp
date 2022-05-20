#include "Sniper.h"

namespace mtm {

    Sniper::Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power) :
        Character(team, health, ammo, range, power, SNIPER_RELOAD_VALUE,
                  SNIPER_ATTACK_COST, SNIPER_MAX_MOVEMENT_UNITS, SNIPER, SNIPER_SYMBOL),
        number_of_attacks(1)
    {}

    Character* Sniper::clone()
    {
        return new Sniper(*this);
    }

    bool Sniper::canAttackEmptyCell()
    {
        return false;
    }

    bool Sniper::isInAttackRange(const GridPoint& src, const GridPoint& dst)
    {
        int distance = GridPoint::distance(src, dst);
        return (distance <= range && distance >= std::ceil(range * MINIMAL_RANGE_FACTOR));
    }

    bool Sniper::attack(Character& other)
    {
        if (!Character::exists(other) || team == other.getTeam()) {
            return false;
        }
        
        if (number_of_attacks == NUM_OF_ATTACKS_UNTIL_DOUBLE_DAMAGE) {
            other.addHealth(-power * INCREASED_ATTACK_FACTOR);
            number_of_attacks = 1;
        }
        else {
            other.addHealth(-power);
            ++number_of_attacks;
        }
        
        --ammo;
        return true;
    }
}
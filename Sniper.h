#ifndef SNIPER_H
#define SNIPER_H

#include "Character.h"

namespace mtm {

    class Sniper : public Character
    {
        static const char SNIPER_SYMBOL = 'N';
        static const units_t SNIPER_RELOAD_VALUE = 2;
        static const units_t SNIPER_ATTACK_COST = 1;
        static const int SNIPER_MAX_MOVEMENT_UNITS = 4; 
        static const int INCREASED_ATTACK_FACTOR = 2;
        static const int NUM_OF_ATTACKS_UNTIL_DOUBLE_DAMAGE = 3;
        static constexpr double MINIMAL_RANGE_FACTOR = 1.0 / 2; 

        int number_of_attacks;

        public: 
            Sniper() = delete;

            /**
            * Sniper constructor: creates a new Sniper.
            *
            * @param team   - the team of the sniper, crossfitters or powerlifters.
            * @param health - the amount of health units.
            * @param ammo   - the amount of ammo units.
            * @param range  - the attacking range of the sniper.
            * @param power  - the power of the sniper.
            * 
            * @return
            *     a new sniper object, with type 'SNIPER' and symbol 'N'.
            *     reload, attack_cost and max_movements_units value is defined as specified for sniper.
            */
            Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power);

            /**
            * clone: create a clone of the current sniper
            *
            * @return
            *        a pointer to the new created character.
            */
            Character* clone() override;
            
            /** 
            * attack: gets a reference to a slot on the board
            *         if the character is in a differend team, the character's health units will be decreased.
            *         once in every 3 successful attacks, double damage will be done to the attacked character.
            *
            * @param other - a reference to the character we want to attack.
            *
            * @return
            *         false if trying to attack the current sniper,character from the same team, or an empty cell, 
            *         true if the attack was successful.
            */
            bool attack(Character& other) override;

            /** 
            * canAttackEmptyCell: sniper can't attack an empty cell, therefore this method returns false.
            *
            * @return
            *       false
            */
            bool canAttackEmptyCell() override;

            /** 
            * isInAttackRange: checks if the attacked character is in the attacking range 
            *                  of the attacking sniper.
            * NOTE: overrides the "isInAttackRange" method of class 'character'.
            */
            bool isInAttackRange(const GridPoint& src, const GridPoint& dst) override;
    };
}

#endif  
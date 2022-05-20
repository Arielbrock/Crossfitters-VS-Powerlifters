#ifndef SOLDIER_H
#define SOLDIER_H

#include "Character.h"

namespace mtm {

    class Soldier : public Character
    {
        static const char SOLDIER_SYMBOL = 'S';
        static const units_t SOLDIER_RELOAD_VALUE = 3;
        static const units_t SOLDIER_ATTACK_COST = 1; 
        static const int SOLDIER_MAX_MOVEMENT_UNITS = 3;

        static constexpr double NEARBY_DAMAGE_FACTOR = 1.0 / 2;

        public:
            Soldier() = delete;

            /**
            * Soldier constructor: creates a new Soldier.
            *
            * @param team - the team of the soldier, crossfitters or powerlifters.
            * @param health - the amount of health units.
            * @param ammo - the amount of ammo units.
            * @param range - the attacking range of the soldier.
            * @param power - the power of the soldier.
            * 
            * @return
            *     a new soldier object, with type 'SOLDIER' and symbol 'S'.
            *     reload, attack_cost and max_movements_units value is defined as specified for soldier.
            */
            Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power);

            /**
            * clone: create a clone of the current soldier 
            *
            * @return
            *     a pointer to the new created character.
            */            
            Character* clone() override;

            /** 
            * attack: gets a reference to a slot on the board,
            *         if the character is in a differend team, the character's health units will be decreased.
            *         if the character is in the same team, no damage will be done to the character.
            *
            * @param other - a reference to the character we want to attack.
            *
            * @return
            *       true anyway. there is no reason for the attack to fail.
            */
            bool attack(Character& other) override;
            
            /** 
            * attackNearbyCharacter: attack all the enemy's characters that are nearby to attacked cell
            *                
            * @param other - a reference to the attacked cell.
            *
            */
            void attackNearbyCharacter(Character& other) const override;
            
            /** 
            * canAttackEmptyCell: soldier can attack an empty cell, therefore this method returns true.
            *
            * @return
            *       true
            */
            bool canAttackEmptyCell() override;

            /** 
            * isInAttackRange: checks if the attacked character is in the attacking range 
            *                  of the attacking soldier.
            * NOTE: overrides the "isInAttackRange" method of class 'character'.
            */
            bool isInAttackRange(const GridPoint& src, const GridPoint& dst) override;
            /**
             *The reason for an attack to fail in that case:
             *                          - a non-soldier character tries to attack a teammate.
             */


            /** 
            * isInAttackRange2: checks (again) if an attacked character is in the range of the soldier.
            *
            * @param src - a reference to the coordinates of the current (attacking) soldier.
            * @param dst - a reference to the coordinates of the attacked character
            *
            * @return
            *       true if the destination is in the row and/or the column of the soldier, false otherwise.
            */
            bool isInAttackRange2(const GridPoint& src, const GridPoint& dst) override;

            static constexpr double NEARBY_DISTANCE_FACTOR = 1.0 / 3;
    };
}

#endif  
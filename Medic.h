#ifndef MEDIC_H
#define MEDIC_H

#include "Character.h"

namespace mtm {

    class Medic : public Character
    {
        static const char MEDIC_SYMBOL = 'M';
        static const units_t MEDIC_RELOAD_VALUE = 5;
        static const units_t MEDIC_ATTACK_COST = 1; 
        static const int MEDIC_MAX_MOVEMENT_UNITS = 5;

        public: 
            Medic() = delete;

            /**
            * Medic constructor: creates a new Medic.
            *
            * @param team   - the team of the medic, crossfitters or powerlifters.
            * @param health - the amount of health units.
            * @param ammo   - the amount of ammo units.
            * @param range  - the attacking range of the medic.
            * @param power  - the power of the medic.
            * 
            * @return
            *     a new Medic object, with type 'MEDIC' and symbol 'M'.
            *     reload, attack_cost and max_movements_units value is defined as specified for medic.
            */
            Medic(Team team, units_t health, units_t ammo, units_t range, units_t power);

            /**
            * clone: create a clone of the current medic 
            *
            * @return
            *     a pointer to the new created character.
            */
            Character* clone() override;


            /** 
            * attack: gets a reference to a slot on the board,
            *         if the character in that slot is on the same team as the attacking medic, 
            *         the character's health units will be increased.
            *         if the character is in a differend team, the character's health units will be decreased.
            *
            * @param other - a reference to the character we want to attack.
            *
            * @return
            *         false if trying to attack the current medic or an empty cell, 
            *         true if the attack was successful.
            */
            bool attack(Character& other) override;
            
            /** 
            * canAttackEmptyCell: medic can't attack an empty cell, therefore this method returns false.
            *
            * @return
            *       false
            */
            bool canAttackEmptyCell() override;

            /** 
            * isInAttackRange: checks if the attacked character is in the attacking range 
            *                  of the attacking medic.
            * NOTE: overrides the "isInAttackRange" method of class 'character'.
            */
            bool isInAttackRange(const GridPoint& src, const GridPoint& dst) override;

            /** 
            * hasAmmoToAttack: checks if the current medic has enough ammo to attack
            *                  if the attacked character is from same team as current medic, no ammo is needed.
            *
            * NOTE: overrides the "hasAmmoToAttack" method of class 'character'.
            */
            bool hasAmmoToAttack(const Character& other) override;
    };
}

#endif  
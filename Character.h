#ifndef CHARACTER_H
#define CHARACTER_H

#include "Auxiliaries.h"

namespace mtm {

    class Character 
    {
        static const char UPPER_TO_LOWER_DIFF = 'a' - 'A';

        protected:
	        Team team;	
            units_t health, ammo, range, power;
            units_t reload_value, attack_cost;

            const int max_movement_units;
            const CharacterType type;
            const char symbol;
            
        public:
            /**
            * clone: create a clone of the current character
            *
            * @return
            *      a pointer to the new created character.
            */
            virtual Character* clone() = 0;

            /**
            * ~Character: delete current character.
            */
            ~Character() = default;

            /**
            * getTeam: checks which team the current character belongs to. 
            *
            * @return
            *     Team - the team of the character.
            */
            Team getTeam() const;

            /**
            * getType: checks what is the type of the current character (Medic, Soldier or Sniper)
            *
            * @return
            *     Type - the type of the character.
            */
            CharacterType getType() const;

            /**
            * getAttackRange: checks what is the attack range of the current character. 
            *
            * @return
            *     range - the range of the character.
            */
            units_t getAttackRange() const;

            /**
            * getTravelDistance: checks what is the maximum number of units 
            *                    that the current character can travel in one move. 
            *
            * @return
            *     an unit_t (int) representing the maximum allowed movment units.
            */
            int getTravelDistance() const;
            
            /**
            * isAlive- checks if the current character is still alive- 
            *          meaning- does the charater have more than 0 health units.
            *
            * @return
            *     a boolean expression- false if the character died, true if the character is still alive.
            */
            bool isAlive();

            /**
            * addHealth - add health units to the current character
            *
            * @param value - the amount of health units we want to add
            */
            void addHealth(units_t value);
            
            /**
            * reload - add ammo units to the current character, 
            *          amount of units is defined differently per each type of character.
            */
            void reload();

            /**
            * convertToChar - gets the symbol of the character, 'm'-medic, 's'- soldier, 'n'- sniper.
            *                 upper case letter if the character is in the "powerlifters" team,
            *                 lower case letter if the character is in the "crossfitters" team.
            *
            * @return    a char represtenting the relevant symbol as described above.          
            */
            char convertToChar() const;

            /** 
            * attack: gets a reference to a slot on the board (character) and attacks it
            *         according to the attack  rules of the relevant type of character.
            *
            * @param other - a reference to the character we want to attack.
            *
            * @return
            *       false if attack failed, 
            *       true if the attack was successful 
            */
            virtual bool attack(Character& other) = 0;
            
            /** 
            * canAttackEmptyCell - checks if the current character can attack an empty slot,
            *                      according to the type of the character.
            *
            * @return
            *       false if the character's type doesnt allow attacking an empty cell
            *       true the character's type allow attacking an empty cell
            */
            virtual bool canAttackEmptyCell() = 0;

            /** 
            * isInAttackRange: checks if an attacked character is in the attacking range 
            *                  of an attacking character.
            *
            * @param src - a reference to the coordinates of the attacking character
            * @param dst - a reference to the coordinates of the attacked character
            *
            * @return
            *       false if the destination of the attack is not in the attacker's range 
            *       true if the destination of the attack is in the attacker's range  
            */            
            virtual bool isInAttackRange(const GridPoint& src, const GridPoint& dst) = 0;

            /** 
            * attackNearbyCharacter: attack all the enemy's characters that are nearby to attacked cell
            *                        if the type of the attacking character is allowed to do so.
            *                  NOTE: only the type "soldier" is allowed to attack nearby charactes.  
            * 
            * @param other - a reference to the attacked cell.
            *
            */
            virtual void attackNearbyCharacter(Character& other) const {};

            /** 
            * hasAmmoToAttack: checks if the current character has enough ammo to attack
            *
            * @param other - a reference to the coordinates of the attacked character
            *
            * @return
            *       false if the current character doesn't have enough ammo, 
            *       true  if the current character does    have enough ammo.
            */
            virtual bool hasAmmoToAttack(const Character& other);

            /** 
            * isInAttackRange2: checks (again) if an attacked character is in the range of an attacking character.
            *
            * @param src - a reference to the coordinates of the attacking character
            * @param dst - a reference to the coordinates of the attacked character
            *
            * @return
            *       true if the attacker is not a soldier. if it is a soldier, return
            *       true if the destination is in the soldier's range, false otherwise.
            * 
            * NOTE: this function is overriden only by Soldier, And I'd like to debate about this implementation,
            *       because it is still better than throwing exceptions here.
            *       In my opinion Your logic is flawed, therefore I've added this flawed method as a silent protest :)
            */
            virtual bool isInAttackRange2(const GridPoint& src, const GridPoint& dst);

            /** 
            * exists: checks if the character exists.
            *
            * @param character - a reference to the character
            *
            * @return
            *       false if the character is null. else, returns true.
            * 
            * NOTE: the function is static because an object's method guarranties that the object isn't nullptr,
            *       therefore a non-static method won't be useful at all.
            */
            static bool exists(const Character& character);
        
        protected:

            /**
             * Character constructor: creates a new Character.
             *
             * @param team    - the team of the character, crossfitters or powerlifters.
             * @param health  - the amount of health units.
             * @param ammo    - the amount of ammo units.
             * @param range   - the attacking range of the character
             * @param power   - the power of the character.
             * @param reload_value       - how many ammo units added to the character's ammo when reloading
             * @param attack_cost        - how many ammo units are reduced when the character attacks.
             * @param max_movement_units - the max movement range of the character
             * @param type    - the type of the character: 'medic', 'sniper' or 'soldier'
             * @param symbol  - the relevant symbol according to the character's type: S-soldier, N- sniper, M-medic
             * 
             */
            Character(Team team, units_t health, units_t ammo, units_t range, units_t power,
                units_t reload_value, units_t attack_cost, int max_movement_units, CharacterType type, char symbol);
    };

}

#endif
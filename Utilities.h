#ifndef _UTILS_H
#define _UTILS_H

#include "Auxiliaries.h"
#include "Character.h"
#include "Soldier.h"
#include "Sniper.h"
#include "Medic.h"

#include <utility>
#include <memory>
#include <map>

#define BOARD_MAP std::map<GridPoint, std::shared_ptr<Character>, mtm::ComparePoints>
#define BOARD_TILE std::pair<const mtm::GridPoint, std::shared_ptr<mtm::Character>>
#define MAKE_TILE(coordinates, character) (std::make_pair(coordinates, character))
#define MAKE_CHARACTER(type) (std::shared_ptr<Character>(new type (team, health, ammo, range, power)))

namespace mtm
{
    /**
     * ComparePoints - a struct used in the game's board (which is std::map).
     * the struct is used as a function object in order to make the map ordered.
     * */
    struct ComparePoints
    {
        /**
         * operator(): activates the comparePoints function object.
         *
         * @param first  - a reference to a valid gridPoint. must be non-nullptr.
         * @param second - a reference to a valid gridPoint. must be non-nullptr.
         * 
         * @return
         *     true if the first gridPoint is above or (left and not below) the second gridPoint, false otherwise.
         */
        bool operator()(const GridPoint& first, const GridPoint& second);
    };

    /**
     * IsInSoldierAttackRange - a struct used in Game's method "attack".
     * the struct is used as a function object in order to be used in std::find_if.
     * */
    struct IsInSoldierAttackRange
    {
        const Character& soldier;
        const GridPoint& attack_coordinates; 

        /**
         * IsInSoldierAttackRange constructor: receives and saves a soldier and his attack coordinated as attributes,
         * in order to use them later in the activation operator.
         * 
         * @param soldier            - a reference to a valid soldier character.
         * @param attack_coordinated - a reference to a valid soldier's attack coordinates.
         */
        IsInSoldierAttackRange(const Character& soldier, const GridPoint& attack_coordinates);

        /**
         * operator(): activates the IsInSoldierAttackRange function object.
         *
         * @param dst - a valid pair of a soldier and his attack coordinates.
         * 
         * @return
         *     true if the coortinates are withing the soldier's nearby area effect range, false otherwise.
         */
        bool operator()(BOARD_TILE dst);
    };
}

#endif
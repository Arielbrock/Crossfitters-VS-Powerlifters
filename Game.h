/**
	+-------------------------------------------------------------+
	|                      Matam HW2 - Game                       |
	|                                                             |
    | @authors                                                    |
    |   - Yehonatan  Simian   206584021                           |
    |   - Ariel      Brock    318268265                           |
    |                                                             |
    | @date 21/06/2021 © authors                             ♥ ♥  |
    |                                                         <   |
    | Good luck for us ^^                                   \___/ |
	+-------------------------------------------------------------+
*/

#ifndef _GAME_H
#define _GAME_H

#include "Utilities.h" // also includes other utilities such as characters.

#include <iostream>

namespace mtm
{    
    class Game
    {
        int height;
        int width;
        BOARD_MAP board;
	    unsigned int crossfitters_count;
        unsigned int powerlifters_count;

        public:
            /**
             * deleted function - a game must have width and height in order to be created.
             */
            Game() = delete;

            /**
             * Game constructor: creates a new Game with a board of the given dimensions.
             *
             * @param width  - the width of the game board. must be positive.
             * @param height - the height of the game board. must be positive.
             * 
             * @throw
             *     IllegalArgument - if the width or height are non-positive.
             * 
             * @return
             *     a new Game object, with:
             *          - width and height as the given parameters.
             *          - crossfitters_count and powerlifters_count = 0.
             *          - an empty board (std::map).
             */
            Game(int height, int width);

            /**
             * Game copy constructor: creates a new game based on an existing one.
             *
             * @param other - the game whose data we want to copy.
             * 
             * @throw
             *     IllegalArgument - if the other game does not exists.
             * 
             * @return
             *     a new Game object with the copied data.
             */
            Game(const Game& other);

            /**
             * operator=: copies "other"'s game data to the current object.
             *
             * @param other - the game whose data we want to copy.
             * 
             * @throw
             *     IllegalArgument - if the other game does not exists.
             * 
             * @return
             *     a reference to the current Game object.
             * 
             * NOTE: the two Games remain independent after the operation.
             */
            Game& operator=(const Game& other);

            /**
             * Game destructor: deletes the current Game object and release all of its memory.
             */
            ~Game() = default;

            /**
             * addCharacter: add a new character to the game.
             * update the board and the crossfitters/powerlifters count accordingly.
             *
             * @param coordinates - the coordinates in which the character should be emplaced. Must be non-nullptr.
             * @param character - a shared pointer to the character that should be added to the game.
             * 
             * @throw
             *      IllegalArgument - if one of the arguments is nullptr.
             *      IllegalCell     - if "coordinates" is not within the board's range.
             *      CellOccupied    - if there's already another player in "coordinates".
             * 
             */
            void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);

            /**
             * move: moves a character from src_coordinates to dst_coordinates.
             *
             * @param src_coordinates - the coordinates of the character we want to move. Must be non-nullptr.
             * @param dst_coordinates - the coordinates of the character's destination  . Must be non-nullptr.
             * 
             * @throw
             *      IllegalArgument - if one of the arguments is nullptr.
             *      IllegalCell     - if one of the coordinates is not within the board's range.
             *      CellEmpty       - if there's no character in the source coordinates.
             *      MoveTooFar      - if the destination coordinates are beyond the character's travel distance.
             *      CellOccupied    - if there's already another player in "coordinates"
             * 
             */
            void move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);

            /**
             * attack: make a character in src_coordinates attack dst_coordinates.
             * if the attacker also affects nearby characters, attack them too.
             * if an attacked character(s) is not alive anymore - remove it from the board.
             *
             * @param src_coordinates - the coordinates of the attacker character.   Must be non-nullptr.
             * @param dst_coordinates - the coordinates of the attacked destination. Must be non-nullptr.
             * 
             * @throw
             *      IllegalArgument - if one of the arguments is nullptr.
             *      IllegalCell     - if one of the coordinates is not within the board's range.
             *      CellEmpty       - if there's no character in the source coordinates.
             *      OutOfRange      - if the destination coordinates are beyond the attacking character's attack range.
             *      OutOfAmmo       - if the attacking character has not enough ammo to attack
             *      IllegalTarget   - if the attack failed of any other reason (attacking character's constraints).
             * 
             */
            void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);

            /**
             * reload: make a character in coordinates reload ammo.
             *
             * @param coordinates - the coordinates of the character. Must be non-nullptr.
             * 
             * @throw
             *      IllegalArgument - if the argument is nullptr.
             *      IllegalCell     - if the coordinates are not within the board's range.
             *      CellEmpty       - if there's no character in the coordinates.
             * 
             */
            void reload(const GridPoint& coordinates);

            /**
             * isOver: checks if the game is over.
             *
             * @param winningTeam - a pointer to the result keeper (detailed in the next line).
             * 
             * @return
             *     - true if the game is over, false otherwise.
             *     - the function also returns the winning team indirectly, through the parameter winningTeam.
             *       if this parameter is NULL or nullptr, the winning team is not returned.
             * 
             * NOTE: a game is over if all of the characters on board are either CROSSFITTERS or POWERLIFTERS.
             * NOTE: the function does not throw any exceptions.
             */
            bool isOver(Team* winningTeam = NULL) const;


            /**
             * operator<< overloading: prints the game to an output stream.
             *
             * @param os   - a reference the output stream. must be non-nullptr.
             * @param game - a reference the game to print. must be non-nullptr.
             * 
             * @return
             *     - the output stream (os) after the print has been done.
             * 
             * NOTE: the game is printed in the format defined by Auxiliaries::printGameBoard.
             */
            friend std::ostream& operator<<(std::ostream& os, const Game& game);

            /**
             * makeCharacter: a static function that creates a new character.
             *
             * @param type   - the new character's type (Medic / Sniper / Soldier).
             * @param team   - the new character's team (POWERLIFTERS / CROSSFITTERS).
             * @param health - the new character's health.              must be positive.
             * @param ammo   - the new character's starting ammo value. must be non-negative.
             * @param range  - the new character's attack range.        must be non-negative.
             * @param power  - the new character's attack power.        must be non-negative.
             * 
             * @throw
             *     IllegalArgument - if one of the values is incorrect (according to the parameters' conditions).
             * 
             * @return
             *     a shared pointer to the newborn character. Mazal-Tov ^^
             */
            static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, units_t health,
                                                            units_t ammo, units_t range, units_t power);

        /** NOTE: private functions do not throw exceptions. */
        private:
            /**
             * copyBoard: copies another board's data.
             *
             * @param other - a reference to the board we want to copy.
             */
            void copyBoard(const BOARD_MAP& other);

            /**
             * isCellEmpty: checks if a cell empty.
             *
             * @param coordinates - a reference to a valid cell coordinates (withing the board's range).
             * 
             * @return
             *      true if the cell is not exists in the board, false otherwise.
             */
            bool isCellEmpty(const GridPoint& coordinates);

            /**
             * isOutOfBound: checks if a cell is within the board's range.
             *
             * @param coordinates - a reference to a cell coordinates. must be non-nullptr.
             * 
             * @return
             *      true if the cell's x and y coordinates are greater than 0
             *      and lesser than the board's width and height (respectively), false otherwise.
             */
            bool isOutOfBound(const GridPoint& coordinates);

            /**
             * attackNearbyCharacters: make a soldier character attack all nearby coordinates of a requested attack.
             * if an attacked characters is not alive anymore - remove it from the board.
             *
             * @param soldier         - a reference to the attacking character. must be an instance of a soldier.
             * @param dst_coordinates - a reference to the attacked cell coordinates.
             */
            void attackNearbyCharacters(const Character& soldier, const GridPoint& dst_coordinates);

            /**
             * kill: reduces the crossfitters_count or powerlifters_count when a character is killed.
             *
             * @param character - a reference to the killed character.
             */
            void kill(const Character& character);
    };
}

#endif

#include "Game.h"

#include "Utilities.h" // also includes other utilities such as characters.
#include "Exceptions.h"

#include <algorithm>

using std::shared_ptr;

namespace mtm 
{
    Game::Game(int height, int width) :
        height(height),
        width(width),
        board(BOARD_MAP()),
        crossfitters_count(0),
        powerlifters_count(0)
    {
        if (width < 1 || height < 1) {
            throw IllegalArgument();
        }
    }

    Game::Game(const Game& other) :
        height(other.height),
        width(other.width),
        crossfitters_count(other.crossfitters_count),
        powerlifters_count(other.powerlifters_count)
    {
        if (&other == nullptr) {
            throw IllegalArgument();
        }
        copyBoard(other.board);
    }

    Game& Game::operator=(const Game& other)
    {
        if (&other == nullptr) {
            throw IllegalArgument();
        }

        if (this == &other) {
            return *this;
        }

        height = other.height;
        width = other.width;
        copyBoard(other.board);
        crossfitters_count = other.crossfitters_count;
        powerlifters_count = other.powerlifters_count;

        return *this;
    }

    void Game::copyBoard(const BOARD_MAP& other)
    {
        board.clear();
        for (BOARD_MAP::const_iterator iterator = other.begin(); iterator != other.end(); ++iterator) {
            board.emplace(MAKE_TILE(GridPoint((*iterator).first),
                                    std::shared_ptr<Character>((*(*iterator).second).clone())));
        }
    }

    bool Game::isCellEmpty(const GridPoint& coordinates)
    {
        return board.find(coordinates) == board.end();
    }

    bool Game::isOutOfBound(const GridPoint& coordinates)
    {
        return (coordinates.col < 0 || coordinates.row < 0 || 
                coordinates.col >= width || coordinates.row >= height);
    }

    void Game::addCharacter(const GridPoint& coordinates, shared_ptr<Character> character)
    {
        if (&coordinates == nullptr || character == nullptr) {
            throw IllegalArgument();
        }
        if (isOutOfBound(coordinates)) {
            throw IllegalCell();
        }
        if (!isCellEmpty(coordinates)) {
            throw CellOccupied();
        }
        board.emplace(MAKE_TILE(coordinates, character));
        (*character).getTeam() == CROSSFITTERS ? ++crossfitters_count : ++powerlifters_count;
    }
    
    void Game::move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates)
    {
        if (&src_coordinates == nullptr || &dst_coordinates == nullptr) {
            throw IllegalArgument();
        }
        if (isOutOfBound(src_coordinates) || isOutOfBound(dst_coordinates)) {
            throw IllegalCell();
        }
        if (isCellEmpty(src_coordinates)) {
            throw CellEmpty();
        }

        shared_ptr<Character> character_ptr = board[src_coordinates];
        if (GridPoint::distance(src_coordinates, dst_coordinates) > (*character_ptr).getTravelDistance()) {
            throw MoveTooFar();
        }
        if (!isCellEmpty(dst_coordinates)) {
            throw CellOccupied();
        }

        board.erase(src_coordinates);
        board.emplace(MAKE_TILE(dst_coordinates, character_ptr));
    }
    
    void Game::attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates)
    {
        if (&src_coordinates == nullptr || &dst_coordinates == nullptr) {
            throw IllegalArgument();
        }
        if (isOutOfBound(src_coordinates) || isOutOfBound(dst_coordinates)) {
            throw IllegalCell();
        }
        if (isCellEmpty(src_coordinates)) {
            throw CellEmpty();
        }

        Character& attacking_character = *board[src_coordinates];
        if (!attacking_character.isInAttackRange(src_coordinates, dst_coordinates)) {
            throw OutOfRange();
        }

        Character& attacked_character = *board[dst_coordinates]; // handle with care, might need by a nullptr.
        if (!Character::exists(attacked_character)) {
            board.erase(dst_coordinates);
        }
        if (!attacking_character.hasAmmoToAttack(attacked_character)) {
            throw OutOfAmmo();
        }
        if (!attacking_character.isInAttackRange2(src_coordinates, dst_coordinates)
          ||!attacking_character.attack(attacked_character)) {
            throw IllegalTarget();
        }

        if (!Character::exists(attacked_character) || !attacked_character.isAlive()) {
            kill(attacked_character);
            board.erase(dst_coordinates);
        }
        if (attacking_character.getType() == SOLDIER) {
            attackNearbyCharacters(attacking_character, dst_coordinates);
        }
    }

    void Game::attackNearbyCharacters(const Character& soldier, const GridPoint& dst_coordinates)
    {
        IsInSoldierAttackRange predicate(soldier, dst_coordinates);

        for (BOARD_MAP::iterator iterator = std::find_if(board.begin(), board.end(), predicate);
            iterator != board.end();
            iterator = std::find_if(++iterator, board.end(), predicate))
        {
            BOARD_TILE other_attacked_pair = *iterator;
            Character& other_attacked_character = *other_attacked_pair.second;
            soldier.attackNearbyCharacter(other_attacked_character);
            if (!other_attacked_character.isAlive())
            {
                // nasty trinary operator to keep the iterator valid after delition.
                BOARD_MAP::iterator* new_iterator = (iterator != board.begin() ? &(--iterator) : nullptr); 

                // character's delition.
                kill(other_attacked_character);
                board.erase(other_attacked_pair.first);

                // keeping the iterator valid (board.begin() if we deleted the first element, otherwise --iterator).
                iterator = (new_iterator == nullptr) ? board.begin() : *new_iterator;
            }
        }
    }
    
    void Game::kill(const Character& character)
    {
        if (!Character::exists(character)) {
            return;
        }

        character.getTeam() == POWERLIFTERS ? --powerlifters_count : --crossfitters_count;
    }
    
    void Game::reload(const GridPoint& coordinates)
    {
        if (&coordinates == nullptr) {
            throw IllegalArgument();
        }
        if (isOutOfBound(coordinates)) {
            throw IllegalCell();
        }
        if (isCellEmpty(coordinates)) {
            throw CellEmpty();
        }

        (*board[coordinates]).reload();
    }

    bool Game::isOver(Team* winningTeam) const
    {
        if (crossfitters_count + powerlifters_count == 0) {
            return false;
        }

        if (crossfitters_count == 0) {
            if (winningTeam != NULL && winningTeam != nullptr) {
                *winningTeam = POWERLIFTERS;
            }
            return true;
        }

        if (powerlifters_count == 0) {
            if (winningTeam != NULL && winningTeam != nullptr) {
                *winningTeam = CROSSFITTERS;
            }
            return true;
        }

        return false;
    }

    std::ostream& operator<<(std::ostream& os, const Game& game)
    {
        if (&os == nullptr || &game == nullptr) {
            throw IllegalArgument();
        }

        int width = game.width;
        int height = game.height;
        int length = width * height;

        BOARD_MAP board = game.board;
        char* board_char = new char[length];

        BOARD_MAP::iterator iterator = board.begin();

        int i = 0;
        for (; i < length && iterator != board.end(); ++i)
        {
            const GridPoint board_point = (*iterator).first;
            if (board_point == GridPoint(i / width, i % width)) {
                Character& character = *(*iterator).second;
                board_char[i] = character.convertToChar();
                ++iterator;
            }
            else {
                board_char[i] = ' ';
            }
        }
        for (; i < length; board_char[i++] = ' ');

        printGameBoard(os, board_char, board_char + i, width);
        delete[] board_char;

        return os;
    }

    shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team,
                                            units_t health, units_t ammo, units_t range, units_t power)
    {
        if (health <= 0 || ammo < 0 || range < 0 || power < 0) {
            throw IllegalArgument();
        }

        switch (type)
        {
            case SOLDIER: return MAKE_CHARACTER(Soldier);
            case MEDIC:   return MAKE_CHARACTER(Medic); 
            case SNIPER:  return MAKE_CHARACTER(Sniper); 
            default: throw IllegalArgument();
        }
    } 
}

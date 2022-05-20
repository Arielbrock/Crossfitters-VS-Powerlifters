#include "Utilities.h"

namespace mtm 
{
    bool ComparePoints::operator()(const GridPoint& first, const GridPoint& second)
    {
        if (first.row == second.row) {
            return first.col < second.col;
        }
        return first.row < second.row;
    }

    bool IsInSoldierAttackRange::operator()(BOARD_TILE dst)
    {
        int distance = GridPoint::distance(attack_coordinates, dst.first);
        return (distance > 0 && 
                distance <= std::ceil(soldier.getAttackRange() * Soldier::NEARBY_DISTANCE_FACTOR));
    }

    IsInSoldierAttackRange::IsInSoldierAttackRange(const Character& soldier, const GridPoint& attack_coordinates) :
        soldier(soldier),
        attack_coordinates(attack_coordinates)
    {}
}
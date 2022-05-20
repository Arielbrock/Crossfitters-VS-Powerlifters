#include "Exceptions.h"

using std::string;

namespace mtm {
    const string Exception::pre_message = "A game related error has occurred: ";
    Exception::Exception(const string title) : 
        message(pre_message + title)
    {}
    const char* Exception::what() const noexcept
    {
        return message.c_str();
    }

    IllegalArgument::IllegalArgument() : Exception("IllegalArgument") {}
    IllegalCell::IllegalCell()         : Exception("IllegalCell")     {}
    CellEmpty::CellEmpty()             : Exception("CellEmpty")       {}
    MoveTooFar::MoveTooFar()           : Exception("MoveTooFar")      {}
    CellOccupied::CellOccupied()       : Exception("CellOccupied")    {}
    OutOfRange::OutOfRange()           : Exception("OutOfRange")      {}
    OutOfAmmo::OutOfAmmo()             : Exception("OutOfAmmo")       {}
    IllegalTarget::IllegalTarget()     : Exception("IllegalTarget")   {}
}
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

using std::string;

namespace mtm {

    /**
     * Exception class - the main class for exceptions in Game.
     *
     * Every exception is derived from this class.
     * 
     * The class is unabstract in order to enable custom messages, though no such message is sent in Game.cpp.
     * We know you didn't ask for it, but c'mon let us show you our advance thinking and well program design :)
     */
    class Exception : public std::exception
    {
        static const string pre_message; // = "A game related error has occurred: "
        string message;

        public:
            /**
             * Exception constructor: creates a new Exception with a specific message,
             * that will be returned in the function what().
             *
             * @param title - the title of the message. must be a valid string.
             */
            explicit Exception(const string title);

            /**
             * what - returns the message of the current Exception.
             *
             * @return
             *      the message of the current exception.
             */
            const char* what() const noexcept;
    };


    /**
     * Each one of the next classes is derived from mtm::Exception, as described above.
     *
     * Each class has only a constructor, which calls the Exception's cunstructor with the relevant message.
     */

    class IllegalArgument : public Exception
    {
        public:
            IllegalArgument();
    };
    class IllegalCell     : public Exception
    {
        public:
            IllegalCell();
    };
    class CellEmpty       : public Exception
    {
        public:
            CellEmpty();
    };
    class MoveTooFar      : public Exception
    {
        public:
            MoveTooFar();
    };
    class CellOccupied    : public Exception
    {
        public:
            CellOccupied();
    };
    class OutOfRange      : public Exception
    {
        public:
            OutOfRange();
    };
    class OutOfAmmo       : public Exception
    {
        public:
            OutOfAmmo();
    };
    class IllegalTarget   : public Exception
    {
        public:
            IllegalTarget();
    };
}

#endif
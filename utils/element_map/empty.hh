#ifndef EMPTY_HH
#define EMPTY_HH

#include "aObject.hh"

class Empty: public AObject
{
    public:
        Empty(int posX, int posY);
        ~Empty();

        std::string getDisplayer(void) const;
};

#endif
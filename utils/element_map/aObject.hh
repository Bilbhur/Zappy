#ifndef AOBJECT_HH
#define AOBJECT_HH

#include <stdbool.h>
#include <string>

class AObject
{
    private:
        bool _isWalkable;
        int _posX;
        int _posY;
        
        std::string _className;

    public:
        AObject(int posX, int posY, std::string className, bool isWalkable);
        virtual ~AObject() = 0;

        int getPosX(void) const;
        void setPosX(int posX);
        int getPosY(void) const;
        void setPosY(int posY);

        std::string getClassName(void) const;
        bool getWalkable(void) const;

        virtual std::string getDisplayer(void) const;
};

#endif
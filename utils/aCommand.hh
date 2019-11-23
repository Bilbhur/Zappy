#ifndef ACOMMAND_HH
#define ACOMMAND_HH

#include <mutex>

class ACommand
{
    public:
        ACommand();
        virtual ~ACommand() = 0;
        virtual void getCommands();
        virtual int sendCommands();
        void quit();
        bool getQuit() const;
    protected:
        std::mutex _mQuit;
    private:
        bool _quit;
};


#endif //COMMAND_HH
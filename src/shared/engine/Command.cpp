#include "Command.h"

namespace engine{
    Command::Command(){}
    Command::~Command(){}

    CommandTypeID Command::getCommandTypeID(){
        return _commandTypeID;
    }

    bool Command::process(state::State& state){}
}
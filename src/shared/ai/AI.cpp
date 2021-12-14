#include "AI.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "../engine.h"
#include "../state.h"

namespace ai
{
    void AI::run(engine::Engine &engine)
    {
        engine.processCommands();
    }
}

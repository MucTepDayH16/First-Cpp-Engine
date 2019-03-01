#ifndef EXECUTE_H
#define EXECUTE_H

#include "state.h"

class Execute {
protected:
    Uint16 exit;
    bool isRunning;
    void Exit(Uint16);

    State* state;
public:
    Execute(State*, Uint16, Uint16);
    Uint16 Run();
};

#endif
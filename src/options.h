#pragma once

#include "sorter.h"
#include "screen.h"

struct ProgramOptions {
    Algorithm algorithm;
    DiagramType diagram;
};

ProgramOptions ParseCommandLine(int argc, char* argv[]); 
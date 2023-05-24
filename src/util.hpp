#pragma once

#include <iostream>

#define TODO()                                                             \
    do {                                                                   \
        std::cerr << __FILE__ << ":" << __LINE__ << ": TODO Unimplemented" \
                  << std::endl;                                            \
        exit(42);                                                          \
    } while (0)

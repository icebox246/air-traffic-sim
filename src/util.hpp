#pragma once

#include <iostream>

#define TODO()                                                             \
    do {                                                                   \
        std::cerr << __FILE__ << ":" << __LINE__ << ": TODO Unimplemented" \
                  << std::endl;                                            \
        exit(42);                                                          \
    } while (0)

#define ASSERT(expression)                                          \
    do {                                                            \
        if (!(expression)) {                                        \
            std::cerr << __FILE__ << ":" << __LINE__                \
                      << ": TODO Assertion failed: " << #expression \
                      << std::endl;                                 \
            exit(43);                                               \
        }                                                           \
    } while (0)

#define ASSERT_EQ(expression, value)                                         \
    do {                                                                     \
        if ((expression) != (value)) {                                       \
            std::cerr << __FILE__ << ":" << __LINE__                         \
                      << ": TODO Assertion failed: " << #expression << " = " \
                      << (expression) << " != " << (value) << std::endl;     \
            exit(44);                                                        \
        }                                                                    \
    } while (0)

#define ASSERT_NEQ(expression, value)                                        \
    do {                                                                     \
        if ((expression) == (value)) {                                       \
            std::cerr << __FILE__ << ":" << __LINE__                         \
                      << ": TODO Assertion failed: " << #expression << " = " \
                      << (expression) << " == " << (value) << std::endl;     \
            exit(45);                                                        \
        }                                                                    \
    } while (0)

#ifndef UTILS_H
#define UTILS_H

#include <iostream>

namespace Utils {

inline void CHECK_ERRORS(bool boolean, std::string msg)
{
    if (boolean) { std::cerr << msg << std::endl; exit(1); }
}

}

#endif // UTILS_H

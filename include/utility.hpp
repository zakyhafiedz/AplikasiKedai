#ifndef UTILITY_HPP
#define UTILITY_HPP

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include <iostream>

using namespace std;

class utility {
    public:
        static void clearScreen();
        static void pauseForKey();
};

#endif
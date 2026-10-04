#pragma once

#include <string>
using namespace std;

inline class Logger {
    public:
        void log(string text);
        void error(string text);
        void fatal(string text);
} Logger;
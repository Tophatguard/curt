#include "logger.hpp"
#include <iostream>
using namespace std;

void Logger::log(string text) {
    cout << "INFO: LOGGER: " << text << endl;
}

void Logger::error(string text) {
    cout << "ERROR: LOGGER: " << text << endl;
}

void Logger::fatal(string text) {
    cout << "FATAL: LOGGER: " << text << endl;
    exit(1);
}
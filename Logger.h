//
// Created by me on 9/26/2022.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
using namespace std;

class Logger {

private:
    Logger() {} //make constructor
    Logger(Logger const &copy);

    Logger &operator=(Logger const &copy);

public:
    static Logger &getLog() {
        static Logger log;
        return log;
    }

    void log(const string &output) {
        cout << output << endl;
    }
};

#endif
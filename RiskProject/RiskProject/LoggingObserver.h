#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class ILoggable{
public:
    virtual string stringToLog() = 0;
};

class Observer {
public:
    //pure virtual
    virtual void update(ILoggable* iLoggable) = 0;
};

class LogObserver : Observer {
public:
    ofstream gameLog;
    LogObserver();
    void update(ILoggable* iLoggable);
    friend ostream& operator<<(ostream& os, const LogObserver& logObserver);
};

class Subject {
public:
    LogObserver* view;
    Subject();
    Subject(const Subject& subject);
    Subject& operator=(const Subject& subject);
    friend ostream& operator<<(ostream& os, const Subject& subject);
    void notify(ILoggable* iLoggable);
};

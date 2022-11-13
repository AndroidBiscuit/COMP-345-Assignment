#pragma once
#include <string>
#include <list>
using namespace std;


class ILoggable {
public:
    virtual string stringToLog() = 0;
};


class Observer {
public:
    //pure virtual
    virtual ~Observer();
    virtual void Update(ILoggable* iLoggable) = 0;
protected:
    Observer();
};

class Subject : public ILoggable {
public:
    Subject();
    Subject(const Subject& subject);
    virtual ~Subject();
    Subject& operator=(const Subject& subject);
    friend ostream& operator<<(ostream& os, const Subject& subject);

    virtual void Attach(Observer* observerView);
    virtual void Detach(Observer* observerView);
    virtual void Notify(ILoggable* iLoggable);

    virtual string stringToLog();
protected:
    list<Observer*>* _observers;
};


class LogObserver : public Observer {
protected:
    Subject* _subject;
public:
    LogObserver();
    LogObserver(Subject* subject);
    LogObserver(const LogObserver& logobs);
    virtual ~LogObserver();

    LogObserver& operator=(const LogObserver& logobs);
    friend ostream& operator<<(ostream& output, const LogObserver& order);

    //Notify() will call Update()
    virtual void Update(ILoggable* loggable);
};


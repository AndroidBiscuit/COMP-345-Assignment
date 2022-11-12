#include "LoggingObserver.h"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& os, const LogObserver& logObserver){
    os << "LogObserver" << endl;
    return os;
}

ostream& operator<<(ostream& os, const Subject& subject){
    os << "Subject" << endl;
    return os;
}

void LogObserver::update(ILoggable *iLoggable) {
    gameLog.open("gamelog.txt", ios_base::app);
    if(!gameLog.is_open()){
        cout<<"File was not able to open"<<endl;
        return;
    }
    gameLog<<iLoggable->stringToLog();
    gameLog.close();
}
LogObserver::LogObserver() {

}

Subject::Subject() {
    this->view = new LogObserver();
}
Subject::Subject(const Subject& subject){
    this->view = subject.view;
}

Subject& Subject::operator = (const Subject& subject){
    this->view = subject.view;
    return *this;
}

void Subject::notify(ILoggable *iLoggable) {
    view->update(iLoggable);
#include "GameEngine.h"
#include "GameEngineDriver.h"
#include "CommandProcessingDriver.h"
#include "LoggingObserverDriver.h"

int main(void) {

    bool round = true;
    while (round) {
        system("CLS");
        cout << "\n-------------------Test Menu-----------------------------" << endl;
        cout << "1. Start to test command processor.\n";
        cout << "2. Start to test start up phase.\n";
        cout << "3. Start to test main game loop..\n";
        cout << "4. Start to test order execution.\n";
        cout << "5. Start to test logging observer.\n";
        cout << "\nPlease input your choice: ";
        int opt;
        cin >> opt;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (opt) {
        case 1:
            testCommandProcessor();
            continue;
        case 2:
            testStartupPhase();
            continue;
        case 3:
           
       
            continue;
        case 4:
           
            continue;
        case 5:
            testLoggingObserver();
            round = false;

        default:
            round = false;
        }

    }
      
}
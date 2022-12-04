#include "GameEngine.h"
#include "GameEngineDriver.h"
#include "CommandProcessingDriver.h"
#include "LoggingObserverDriver.h"
#include "TournamentDriver.h"
#include "PlayerStrategiesDriver.h"

int main(void) {

    bool round = true;
    while (round) {
        system("CLS");        cout << "\n-------------------Test Menu-----------------------------" << endl;
        cout << "1. Start to test Player Strategies.\n";
        cout << "2. Start to test Tournament Mode.\n";
        cout << "\nPlease input your choice: ";
        int opt;
        cin >> opt;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (opt) {
        case 1:
            testPlayerStrategies();
            continue;
      
        case 2:
            testTournament();
            round = false;

        default:
            round = false;
        }

    }
      
}
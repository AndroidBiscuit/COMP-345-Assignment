#include "GameEngine.h"
#include "GameEngineDriver.h"
#include "CommandProcessingDriver.h"

int main(void) {
   
        cout << "1. Start to test command processor.\n";
        testCommandProcessor();
        cout << "2. Start to test start up phase.\n";
        testStartupPhase();
        cout << "3. Start to test main game loop.\n";
        cout << "4. Start to test order execution.\n";
        cout << "5. Start to test logging observer.\n";
    
      
}
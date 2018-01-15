// Made By: Rohit Kadhe
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stack>
#include "cal.h"

using namespace std;

int main(){
int quit = 0; string exp;
 displayHeader();
     while (!quit) {
        switch (menu()) {
        case 1:
             displayInstructions();
            pressEnter();
            break;
        case 2:
			enterExpression_DisplayResult(exp);
			cout<<"\n<<< Press Enter to Continue>>>>\n";
			break;
        case 3:
            cout << "\nProgram ended!\n\n";
            quit = 1;
			break;
        default:
        cout<<"\nUnknown error. Please try again!\n";

        break;
        }
     }
}



// Made By: Rohit Kadhe
#ifndef CAL_H
#define CAL_H
using namespace std;

int precedence(char op);
string parseExp(string input);
int evaulate(string s);
int calculate(char op, int b, int a );

bool checkSpace(string input);
bool checkExpression(string input);
bool isBracket(char input);
bool checkBalance(string input);
bool matchType(char a, char b);
bool isDigit(char input);
bool isOperator(char input);

void displayHeader();
void enterExpression_DisplayResult(string s);
void displayInstructions();
void pressEnter();
int menu();
#endif

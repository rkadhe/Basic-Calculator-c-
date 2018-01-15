// Made By: Rohit Kadhe

#include <iostream>
#include <stdlib.h>
#include <string>
#include <stack>
#include "cal.h"
#include <sstream>
#include <iomanip>


bool matchType(char a, char b)
{
    if (a == '\0' || b == '\0')
    {
        return false;
    }

    else if (a == '(' && b == ')')
    {
        return true;
    }

    else if (a == '{' && b == '}')
    {
        return true;
    }

    else if (a == '[' && b == ']')
    {
        return true;
    }

    return false;
}

bool checkBalance(string input)
{
    stack<char> paranthesis;
    int in_length = input.length();
    for (int i = 0; i < in_length; i++)
    {
        if (input[i] == '(' || input[i] == '{' || input[i] == '[' && input[i] != ' ')
        {
            paranthesis.push(input[i]);
        }
        else if (input[i] == ')' || input[i] == '}' || input[i] == ']')
        {
            if (paranthesis.empty() || !matchType(paranthesis.top(), input[i]))
                return false;
            else
                paranthesis.pop();
        }
    }
    return paranthesis.empty() ? true : false;
}

bool isDigit(char input)
{
    if (input >= '0' && input <= '9'|| input == '-') return true;

    return false;
}
bool isBracket(char input)
{
    if (input == '(' || input == '{' || input == '[' ||input == ')' || input == '}' || input == '}')
        return true;
    return false;
}
bool checkSpace(string input)
{
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == ' ')
            return true;
    }
    return false;
}
bool checkExpression(string input)
{
    int length = input.length();
    for(int i = 0; i<input.length(); i++)
    {
        if(isOperator(input[length-1]) && input[length]!=' ')
        {
            return false;
        }
        if(isDigit(input[i]) || isOperator(input[i]) || isBracket(input[i]))
        {
            return true;
        }
    }
    return false;
}
void displayHeader()
{
    cout<<"Program: Basic Calculator"<<endl
        <<"Version: 1.0\n"
        <<"Produced by: Rohit Kadhe\n";
    cout<<"\n<<< Press Enter to Continue>>>>\n";
}
void pressEnter()
{
    cout<<"\n<<< Press Enter to Continue>>>>\n";
    cin.get();
}

int menu()
{
    string choice;
    int flag = 0;

    cin.ignore();
    cout << "\nPlease select on the following operations"
         <<"\n1. Instructions on how to use calculator "
         <<"\n2. Enter an expression to calculate "
         <<"\n3. Quit"
         <<"\nEnter your choice (1, 2, 3):"<<endl;

    cin>>choice;
    if(choice.length()>1)
    {
        return 0;
    }
    if(choice[0] >'3' && choice[0]<'0')
    {
        return 0;
    }
    return choice[0]-'0';
}
void enterExpression_DisplayResult(string s)
{
    string postfix;
    int flag = 0;
    cout<<"Enter Expression \n";
    getline(cin.ignore(),s);
    if(!checkExpression(s))
    {
        cout<<"\nPlease input a valid expression";
        flag = 1;
    }
    else if(!checkBalance(s))
    {
        cout<<"\nExpression contains Unbalanced brackets"<<endl;
        flag = 1;
    }

    else if(!checkSpace(s))
    {
        cout<<"\nPlease have spaces between operator and operand"<<endl;
        flag = 1;
    }
    if((!checkSpace(s) || !checkBalance(s)||!checkExpression(s)) &&flag ==0)
    {
        cout<<"\nInvalid expression"<<endl;
        flag = 1;
    }
    else if(flag ==0)
    {
        {
            postfix = parseExp(s);
            //cout<<"Output = "<<postfix<<"\n";
            int result = evaulate(postfix);
            cout<<"The answer is: "<<result<<endl;
        }
    }
}
void displayInstructions()
{
    cout<<"\n----------------------------------------------------------------------------------------------------------------"<<endl
        <<"This calculator currently supports the following operations(+,-,/,*)."<<endl
        << "\nEnter an algebraic expression to solve and have a space between operator and operand when entering expression."<<endl
        <<"\nExample: (2 + 3) NOT (2+3)"<<endl
        <<"\n Additional features: Checks for unbalanced brackets\n"
        <<"------------------------------------------------------------------------------------------------------------------"<<endl;
}
bool isOperator(char input)
{
    if ((input == '+' || input == '-' || input == '/' || input == '*'))
        return true;
    return false;
}

int precedence(char op)
{
    int precedenceLevel;

    if (op == '+' || op == '-')
        precedenceLevel = 3;
    if (op == '*' || op == '/')
        precedenceLevel = 2;
    if (op == '^')
        precedenceLevel = 1;

    return precedenceLevel;
}
string parseExp(string input)
{
    stack<char> operators;
    string output;

    for (unsigned i = 0; i < input.length(); i++)
    {
        if (isOperator(input[i]) == true)
        {
            while (!operators.empty() && precedence(operators.top()) <= precedence(input[i]))
            {
                output+=operators.top();
                operators.pop();
            }
            operators.push(input[i]);
        }
        else if (input[i] == '(')
        {
            operators.push(input[i]);
        }
        else if (input[i] == ')')
        {
            while (operators.top() != '(')
            {
                output+=operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else
        {
            output+=input[i];
        }
    }

    while (!operators.empty())
    {
        output+= operators.top();
        operators.pop();
    }
    return output;
}

int calculate(char op, int operand1, int operand2)
{
    if (op == '+')
        return operand1 + operand2;
    else if (op == '-')
        return operand1 - operand2;
    else if (op == '*')
        return operand1 * operand2;
    else if (op == '/')
        return operand1 / operand2;
    return -1;
}

int evaulate(string input)
{
    stack<int> result;
    int flag = 0;
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == ' '){
            continue;
    }

        else if (isOperator(input[i]))
        {
            int operand1 = result.top();
            result.pop();
            int operand = result.top();
            result.pop();

            int answer = calculate(input[i], operand, operand1);
            result.push(answer);
        }
        else if (isDigit(input[i]))
        {
            int sum = 0;
            while (i < input.length() && isDigit(input[i]))
            {
                sum = (sum * 10) + (input[i] - '0');
                i++;
            }
            i--;
            result.push(sum);
       }
    }
    return result.top();
}

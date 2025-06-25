#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string input;
int pos = 0;

// Forward declarations
double expression();

void skipSpaces() {
    while (isspace(input[pos])) pos++;
}

double number() {
    skipSpaces();
    double result = 0;
    bool isDecimal = false;
    double decimalPlace = 0.1;

    while (isdigit(input[pos]) || input[pos] == '.') {
        if (input[pos] == '.') {
            isDecimal = true;
            pos++;
            continue;
        }

        if (!isDecimal) {
            result = result * 10 + (input[pos] - '0');
        } else {
            result += (input[pos] - '0') * decimalPlace;
            decimalPlace /= 10;
        }
        pos++;
    }
    return result;
}

// factor: number | '(' expression ')'
double factor() {
    skipSpaces();
    if (input[pos] == '(') {
        pos++;  // skip '('
        double result = expression();
        if (input[pos] == ')') pos++;  // skip ')'
        else {
            cout << "Error: Expected closing ')'\n";
            exit(1);
        }
        return result;
    } else {
        return number();
    }
}

// term: factor (('' | '/') factor)
double term() {
    double result = factor();
    while (true) {
        skipSpaces();
        if (input[pos] == '*') {
            pos++;
            result *= factor();
        } else if (input[pos] == '/') {
            pos++;
            double denom = factor();
            if (denom == 0) {
                cout << "Error: Division by zero\n";
                exit(1);
            }
            result /= denom;
        } else break;
    }
    return result;
}

// expression: term (('+' | '-') term)*
double expression() {
    double result = term();
    while (true) {
        skipSpaces();
        if (input[pos] == '+') {
            pos++;
            result += term();
        } else if (input[pos] == '-') {
            pos++;
            result -= term();
        } else break;
    }
    return result;
}

int main() {
    cout << "Simple Expression Evaluator (supports +, -, *, /, parentheses)\n";
    while (true) {
        cout << "\nEnter expression (or 'exit' to quit): ";
        getline(cin, input);
        if (input == "exit") break;

        pos = 0;
        double result = expression();
        cout << "Result: " << result << endl;
    }

    return 0;
}

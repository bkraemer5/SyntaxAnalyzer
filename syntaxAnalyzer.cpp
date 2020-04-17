#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

// prints string tokens & lexemes
void printStringToken(string key, string lex);

// prints string tokens & char lexemes
void printCharToken(string key, char lex);

// Reads string of tokens & implements FSM
// returns true if ending at final state, false otherwise
bool fsm(string s);

int main() {

        // set of keywords
        vector<string> keywords = {"int", "float", "bool", "true",
                "false", "if", "else", "then", "endif", "while", "whileend",
                "do", "doend", "for", "forend", "input", "output", "and",
                "or", "not"};

        // set of separators
        vector<char> separators = {'\'', '(' , ')', '{', '}', '[', ']',
                ',', '.', ':', ';', ' '};

        // set of operators
        vector<char> operators = {'+', '*', '-','/', '=', '>', '<', '%'};

        /* IMPLEMENTATION OF SYNTAX ANALYZER:
         * 0: S --> i = E
	 * 1: E --> TQ
         * 2: Q --> +TQ | -TQ | epsilon
	 * 3: T --> FR
	 * 4: R --> *FR | /FR | epsilon
	 * 5: F --> (E) | epsilon
         */

	// text result of syntax analyzer
        vector<string> syntaxResults = {
                "\t<Statement List> => <Statement> | <Statement> <Statement List>\n\t<Statement> => <Compound> | < Assign> | <If> | <Return> | <Print> | <Scan> | <While>\n\t<Assign> => Identifier = <Expression>;\n\n", 
		"\n\n", 
		"\t<Expression> => <Term> <ExpressionPrime>\n\t<TermPrime> => <Factor> <TermPrime>\n\t<Factor> => <Primary> | <Primary>\n\t<Primary> => <Identifier> | <Integer> | <Identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false\n\n", 
		"\t<Empty> => Epsilon\n\t<TermPrime> => * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty>\n\t<Empty> => Epsilon\n\t<ExpressionPrime> => + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | <Empty>\n\n", 
		"\t<TermPrime> => <Factor> <TermPrime>\n\t<Factor> => <Primary> | <Primary>\n\t<Primary> => <Identifier> | <Integer> | <Identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false\n\n", 
		"\t<Empty> => Epsilon\n\t<TermPrime> => * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty>\n\t<Empty> => Epsilon\n\t<ExpressionPrime> => <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | <Empty>\n\t <Empty> => Epsilon\n\n"};

        ifstream sourceCode;
        sourceCode.open("sourceCode.txt");
        string line;
        string identifier = "";
        string number = "";
        string type;
        string tokens = "";
	string begin = "";
	int currentSyntaxState = 0;

        // parse file for tokens/lexemes
        while (getline(sourceCode, line)) {

                // adds each line to string of tokens to create an argument for FSM
                tokens = tokens + line;

                for (string::iterator i = line.begin(); i != line.end(); i++) {

                        // checks if character is alphabetic
                        if (isalpha(*i)) {
                                identifier = identifier + *i;
                        }

                        // checks if character is a digit
                        else if (isdigit(*i)) {
                                if (identifier.compare("") == 0) {
                                        number += *i;
                                }
                                else {
                                        identifier = identifier + *i;
                                }
                        }
                        else if (*i == '!') {
                                i = line.end()-1;
                        }

                        // checks if character is a separator
                        // this ends up resetting the identifier
                        for (vector<char>::iterator s = separators.begin(); s != separators.end(); s++) {
                                if (*s == *i && *i != ' ') {

				

                                        // method to print identifier / keyword when separator is found
                                        if (identifier.compare("") != 0) {

                                                 type = "IDENTIFIER";

                                                 // search for keyword match
                                                 for (vector<string>::iterator k = keywords.begin(); k != keywords.end(); k++) {
                                                         if (identifier.compare(*k) == 0) {
                                                                 type = "KEYWORD\t";
                                                         }
                                                 }
						 if (currentSyntaxState == 3) {
							 currentSyntaxState++;
						 }
                                                 printStringToken(type, identifier);
						 cout << syntaxResults.at(currentSyntaxState);
                                                 identifier = "";
                                        }

                                        // method to print number when separator is found
                                        else if (number.compare("") != 0) {

                                                // checks for real vs integer number
                                                if (*i == '.') {
                                                        type = "REAL\t";
                                                        number = number + *i;
                                                }
                                                else {
                                                        if (type.compare("REAL\t") != 0) {
                                                                type = "INTEGER\t";
                                                        }
                                                        printStringToken(type, number);
							if (currentSyntaxState == 3) {
								currentSyntaxState++;
							}
							cout << syntaxResults.at(currentSyntaxState);
                                                        number = "";
                                                        type = "";
                                                }

                                        }

                                        // checks for spaces and if we are parsing a real number
                                        if (*i != ' ' && type.compare("REAL\t") != 0) {
                                                type = "SEPARATOR";
						if (*i == ';') {
							currentSyntaxState = 5;
						}
						else {
							currentSyntaxState = 1;
						}
						printCharToken(type, *i);
						cout << syntaxResults.at(currentSyntaxState);
						currentSyntaxState = 0;
                                        }
                                }
                        }

                        //checks if character is an operator
                        for (vector<char>::iterator o = operators.begin(); o != operators.end(); o++) {
                                if (*o == *i) {

					currentSyntaxState = 2;

                                        // method to print identifer / keyword when operator is found
                                        if (identifier.compare("") != 0) {

                                                 type = "IDENTIFIER";

                                                 // search for keyword match
                                                 for (vector<string>::iterator k = keywords.begin(); k != keywords.end(); k++) {
                                                         if (identifier.compare(*k) == 0) {
                                                                 type = "KEYWORD\t";
                                                         }
                                                 }
                                                 printStringToken(type, identifier);
						 if (*i == '=') {
							 currentSyntaxState = 0;
						 }
						 cout << syntaxResults.at(currentSyntaxState);
                                                 identifier = "";
                                        }

                                        // method to print number when separator is found
                                        else if (number.compare("") != 0) {

                                                type = "INTEGER\t";
                                                printStringToken(type, number);
						if (*i == '=') {
                                                         currentSyntaxState = 0;
                                                 }
						cout << syntaxResults.at(currentSyntaxState);
                                                number = "";

                                        }
					if (*i == '=') {
						currentSyntaxState = 1;
					}
					else {
						currentSyntaxState = 3;
					}
                                        type = "OPERATOR";
					if (*i == '%') {
						if (begin.compare("") == 0) {
							begin += *i;
						}
						else {
							begin += *i;
							printStringToken(type, begin);
							cout << syntaxResults.at(1);
							begin = "";
						}
					}
					else {
						printCharToken(type, *i);
						cout << syntaxResults.at(currentSyntaxState);
					}
                                }
                        }
                }
        }

        // Call for FSM:
        // cout << fsm(tokens);

        return 0;
}

void printStringToken(string key, string lex) {
        cout << "Token: " << key << "\t\t" << "Lexeme:\t " << lex << endl;
}

void printCharToken(string key, char lex) {
         cout << "Token: " << key << "\t\t" << "Lexeme:\t " << lex << endl;
}

bool fsm(string s) {

        // implementation of FSM table
        int fsmTable[14][12] = {2, 4, 6, 14, 8, 14, 10, 14, 12, 14, 1, 14,
                2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                5, 4, 5, 5, 5, 5, 5, 5, 5, 4, 5, 5,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                8, 8, 8, 8, 8, 9, 8, 8, 8, 8, 8, 8,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                10, 10, 10, 10, 10, 10, 10, 11, 10, 10, 10, 10,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                12, 12, 12, 12, 12, 12, 12, 12, 13, 12, 12, 12,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        int currentState = 1;

        // iterates through string
        for (string::iterator k = s.begin(); k != s.end(); k++) {
                if (isalpha(*k)) {
                        currentState = fsmTable[currentState-1][0];
                }
                else if (isdigit(*k)) {
                        currentState = fsmTable[currentState-1][1];
                }
                else if (*k == '(') {
                        currentState = fsmTable[currentState-1][2];
                }
		else if (*k == ')') {
                        currentState = fsmTable[currentState-1][3];
                }
                else if (*k == '{') {
                        currentState = fsmTable[currentState-1][4];
                }
                else if (*k == '}') {
                        currentState = fsmTable[currentState-1][5];
                }
                else if (*k == '[') {
                        currentState = fsmTable[currentState-1][6];
                }
                else if (*k == ']') {
                        currentState = fsmTable[currentState-1][7];
                }
                else if (*k == '!') {
                        currentState = fsmTable[currentState-1][8];
                }
                else if (*k == '.') {
                        currentState = fsmTable[currentState-1][9];
                }
                else if (*k == ' ') {
                        currentState = fsmTable[currentState-1][10];
                }
                else {
                        currentState = fsmTable[currentState-1][11];
                }

        }
        if (currentState == 3 || currentState == 5 || currentState == 7 || currentState == 9
                        || currentState == 11 || currentState == 13 || currentState == 14) {
                return true;
        }
        return false;
}

/* FINITE STATE MACHINE
 *
 * Sigma = {l, d, (, ), {, }, [, ], !, ., sp, p}
 * Q = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}
 * q0 = 1
 * F* =  {3, 5, 7, 9, 11, 13, 14}
 *
 * TABLE:
 *       l  d  (  )  {  }  [  ]  !  .  sp p
 * 1   | 2  4  6  14 8  14 10 14 12 14 1 14     STARTING STATE
 * 2   | 2  2  3  3  3  3  3  3  3  3  3  3     IN IDENTIFIER
 * 3*  | 1  1  1  1  1  1  1  1  1  1  1  1     END OF IDENTIFIER
 * 4   | 5  4  5  5  5  5  5  5  5  4  5  5     IN NUMBER
 * 5*  | 1  1  1  1  1  1  1  1  1  1  1  1     END NUMBER
 * 6   | 6  6  6  7  6  6  6  6  6  6  6  6     IN ()
 * 7*  | 1  1  1  1  1  1  1  1  1  1  1  1     END OF ()
 * 8   | 8  8  8  8  8  9  8  8  8  8  8  8     IN {}
 * 9*  | 1  1  1  1  1  1  1  1  1  1  1  1     END OF {}
 * 10  | 10 10 10 10 10 10 10 11 10 10 10 10    IN []
 * 11* | 1  1  1  1  1  1  1  1  1  1  1  1     END OF []
 * 12  | 12 12 12 12 12 12 12 12 13 12 12 12    IN ! COMMENT
 * 13* | 1  1  1  1  1  1  1  1  1  1  1  1     END ! COMMENT
 * 14* | 1  1  1  1  1  1  1  1  1  1  1  1     GENERAL PUNCTUATION
 *
 */

                                                                                                                                                                                                            

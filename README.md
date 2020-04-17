Problem Statement


The objective of this project is to build a syntax analyzer. This syntax analyzer will run through a series of production rules in order to check the syntax of the source code. This program implements the lexer() from assignment one to extract each individual keyword, identifier, operator, separator, integer, and real number and the proceeds to check if it is syntactically correct within the constraints of the production rules. Each token and lexeme will be printed to the screen along with the corresponding production rule underneath . The approach taken for this assignment is RDP, or recursive descent parser, in order to test the source code for syntax.


How to use program


Type ‘make’ into the command line to compile and run program


Design of program



	Functions:
void printStringToken(string key, string lex)
Prints out string token alongside its string lex value
void printCharToken(string key, char lex)
Prints out string token alongside its character lex value
bool fsm(string s)
Takes in string input and parses it using a FSM to determine if it ends on a final state
Returns true if in the final state, false otherwise.

	Data structures:
vector<string> keywords
A list of certain keywords such as ‘int’, ‘bool’, ‘if’, ‘else’, ‘for’, etc.
vector<char> separators
A list of certain separators such as (, ), {, }, :, ;, space, etc.
vector<char> operators
A list of certain operators such as +, -, *, >, <, etc.
vector<string> syntaxResults
A list of outputs to be printed out by the syntax analyzer

	Implementation:
In a while loop, the program will grab each line from a text file and parse through each individual element
For each element, the program will check whether the variable is a letter, digit, separator, or operator.
When a token is found, it will compare each one to a set of production rules to determine its state in the syntax analyzer
Once the production rule is determined, the program will continue to print the token, lexeme, and the production rules as long as the source code remains syntactically correct

	Production Rules:
Each rule is separated into individual “states”
The state will be indexed into the syntaxResults vector to print out the complete rule

RULES:
0: S → i  (i = E)
1: E → TQ
2: Q → +TQ | -TQ | epsilon
3: T → FR
4: R → *FR | /FR | epsilon
5: F → (E) | epsilon

	Finite State Machine:
Table Implementation:
int fsmTable[14][12]
Rows represent states (1 - 14),  Columns represent identifiers
DFSM = (Sigma, Q, q0, F, N):
Sigma = {1, d, ), (, }, {, [, ], !, ., sp, p}
Q = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}
q0 = 1
F = { 3, 5, 7, 9, 11, 13, 14}
N = 
l  d  (  )  {  }  [  ]  !  .  sp p
1  | 	2  4  6  14 8  14 10 14 12 14 1 14	STARTING STATE
2  |  2  2  3  3  3  3  3  3  3  3  3  3 	IN IDENTIFIER
3  |  1  1  1  1  1  1  1  1  1  1  1  1	END OF IDENTIFIER
4  |  5  4  5  5  5  5  5  5  5  4  5  5	IN NUMBER
5  |  1  1  1  1  1  1  1  1  1  1  1  1	END NUMBER
6  |  6  6  6  7  6  6  6  6  6  6  6  6	IN ()
7  |  1  1  1  1  1  1  1  1  1  1  1  1	END OF ()
8  |  8  8  8  8  8  9  8  8  8  8  8  8	IN {}
9  |  1  1  1  1  1  1  1  1  1  1  1  1	END OF {}
10 |  10 10 10 10 10 10 10 11 10 10 10 10	IN []
11 |  1  1  1  1  1  1  1  1  1  1  1  1	END OF []
12 |  12 12 12 12 12 12 12 12 13 12 12 12	IN ! COMMENT
13 |  1  1  1  1  1  1  1  1  1  1  1  1	END ! COMMENT
14 |  1  1  1  1  1  1  1  1  1  1  1  1	GENERAL PUNCTUATION

bool fsm(string s)
Defines fsmTable 2D array with values for state changes
Compares each character of string input with each column
Changes state where row = currentstate and column = index of token
Returns true when the end state is a final state, false otherwise

Limitation

	None

Shortcomings

	None

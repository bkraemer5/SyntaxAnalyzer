all: program1
	./syntaxAnalyzer

program1: syntaxAnalyzer.cpp
	g++ -o syntaxAnalyzer syntaxAnalyzer.cpp

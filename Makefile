pmatch:
	g++ -c parse/actions.cpp
	g++ -c parse/lexer.cpp
	g++ -c parse/parser.cpp
	g++ -c dfa.cpp
	g++ -c powerset.cpp
	g++ -c regex.cpp
	g++ *.o -o pmatch
	rm *.o
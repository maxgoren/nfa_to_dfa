pmatch:
	mgclex regex.mlex parse/lexer_matrix.h -c
	mgcpgen -l regex.mgrm parse/parse_table.hpp
	g++ -c -g parse/actions.cpp
	g++ -c -g parse/lexer.cpp
	g++ -c -g parse/parser.cpp
	g++ -c -g automata/dfa.cpp
	g++ -c -g automata/powerset.cpp
	g++ -c -g regex.cpp
	g++ -g *.o -o pmatch
	rm *.o
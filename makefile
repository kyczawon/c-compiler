CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

all : bin/c_compiler bin/eval_expr test/test

src/maths_parser.tab.cpp src/maths_parser.tab.hpp : src/maths_parser.y include/ast.hpp include/ast/ast_operators.hpp
	bison -v -d src/maths_parser.y -o src/maths_parser.tab.cpp

src/maths_lexer.yy.cpp : src/maths_lexer.l src/maths_parser.tab.hpp
	flex -o src/maths_lexer.yy.cpp  src/maths_lexer.l

bin/c_compiler : src/c_compiler.o src/maths_parser.tab.o src/maths_lexer.yy.o src/maths_parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/c_compiler $^
	
bin/eval_expr : src/eval_expr.o src/maths_parser.tab.o src/maths_lexer.yy.o src/maths_parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/eval_expr $^

test/test : test/test.cpp
	mkdir -p test
	g++ $(CPPFLAGS) -o test/test $^

clean :
	rm src/*.o
	rm bin/*
	rm src/*.tab.cpp
	rm src/*.yy.cpp

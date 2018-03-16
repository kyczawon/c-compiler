CPPFLAGS += -std=c++11 -g
CPPFLAGS += -I include

all : bin/c_compiler

src/compiler_parser.tab.cpp src/compiler_parser.tab.hpp : src/compiler_parser.y include/ast.hpp include/ast/ast_operators.hpp
	bison -v -d src/compiler_parser.y -o src/compiler_parser.tab.cpp

src/compiler_lexer.yy.cpp : src/compiler_lexer.l src/compiler_parser.tab.hpp
	flex -o src/compiler_lexer.yy.cpp  src/compiler_lexer.l

bin/c_compiler : src/c_compiler.o src/compiler_parser.tab.o src/compiler_lexer.yy.o src/compiler_parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/c_compiler $^

# test/test : test/test.cpp
# 	mkdir -p test
# 	g++ $(CPPFLAGS) -o test/test $^

clean :
	rm src/*.o
	rm bin/*
	rm src/*.tab.cpp
	rm src/*.yy.cpp

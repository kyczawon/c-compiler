#include "ast.hpp"
#include <fstream>
#include <string.h>
#include <cstddef>

void print_python(FILE* is, std::ostream &os);
void check_files_opened(FILE *source_file, std::ofstream &out_file, char *argv[]);

int main(int argc, char *argv[])
{
    //check for correct number of arguments
    if (argc != 5)
    {
        //debugging mode
        if (argc == 2 && strcmp(argv[1],"-d")==0) {
            Node *ast=parseAST();
            ast->translate(0, std::cout);
        } else {
            printf("%s","Wrong number of arguments.");
            exit(EXIT_FAILURE);
        }
    }

    if (strcmp(argv[1],"-S")==0 && strcmp(argv[3],"-o")==0) {
        FILE *source_file =fopen(argv[2], "r");
        std::ofstream out_file(argv[4]);
        check_files_opened(source_file, out_file, argv);

    }

    //translation
    if (strcmp(argv[1],"--translate")==0 && strcmp(argv[3],"-o")==0) {
        FILE *source_file =fopen(argv[2], "r");
        std::ofstream out_file(argv[4]);

        check_files_opened(source_file, out_file, argv);

        print_python(source_file, out_file);

    } else if (strcmp(argv[1],"-S")==0 && strcmp(argv[3],"-o")==0) {

    } 
    return 0;
}

void check_files_opened(FILE *source_file, std::ofstream &out_file, char *argv[]) {
    if (source_file == NULL)
        {
            std::string message = "source_file '" + std::string(argv[2]) + "' could not be opened.\n";
            printf("%s",message.c_str());
            exit(EXIT_FAILURE);
        }
    if (!out_file.is_open())
    {
        std::string message = "out_file `" + std::string(argv[4]) + "' could not be opened.\n";
            printf("%s",message.c_str());
        exit(EXIT_FAILURE);
    }
}

void print_code_gen(FILE* is, std::ostream &os) {
        yyin = is;
        Node *ast=parseAST();
        ast->code_gen(os);
}

void print_python(FILE* is, std::ostream &os) {
        yyin = is;
        Node *ast=parseAST();
        ast->translate(0, os);

        os << std::endl << "# Boilerplat" << std::endl
        << "if __name__ == \"__main__\":" << std::endl
        << "\t" << "import sys" << std::endl
        << "\t" << "ret=main()" << std::endl
        << "\t" << "sys.exit(ret)" << std::endl << std::endl;
}
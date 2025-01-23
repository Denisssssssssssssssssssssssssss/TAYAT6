#include <iomanip>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Scanner.h"
#include "Diagramm.h"
#include "Tree.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Scanner* scanner;
    Tree* tree = new Tree();
    FILE* file;
    errno_t err = fopen_s(&file, "input.txt", "r");
    scanner = new Scanner(file);
    Diagramm* diagramm = new Diagramm(scanner, tree);

    diagramm->Program();

    int type; TypeLex lex;
    type = scanner->Scan(lex);
    if (type == typeEnd)
        std::cout << "OK" << std::endl;
    else
        std::cout << "ERROR" << std::endl;
    tree->Print(0);

    return 0;
}


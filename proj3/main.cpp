#include <iostream>
#include <header.hpp>

int main(int argc, char *argv[])
{
    FileReader file("test.txt");
    file.ReadLines();
    file.PrintLines();
    GetAllProcess getallprocess(file.getLines());
    getallprocess.AnalyzeProcesses();
    getallprocess.printvectorprs();
    getallprocess.PrintPages();


    return 0;
}
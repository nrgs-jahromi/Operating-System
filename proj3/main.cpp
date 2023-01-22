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
    std::cout<< Search("A","var4")<<std::endl;
    //std::cout<<SetFrame()<<std::endl;
    //void SetFrame();

    return 0;
}
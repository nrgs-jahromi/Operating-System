#include <iostream>
#include <vector>


std::vector<std::string> lines;

void ReadFile(std::string filename){
    std::ifstream file(filename, std::ios::in);
    std::string temp = "";

    while (std::getline(file, temp))
        if (temp[0] != '\0')
            lines.push_back(temp);
}


int main(){


}
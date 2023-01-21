#ifndef HEADER_HPP
#define HEADER_HPP
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

struct Page{
    std::string pname;
    int pagenumber;
    std::vector<std::string> varAvailable;
};

struct Var {
    std::string process_name;
    std::string variable_name;
    int variable_size;
};

std::vector<Page *> Pageptr;
std::vector<Var *> prs;

class FileReader {
    private:
        std::vector<std::string> lines;
        std::string filename;
    public:
        FileReader(std::string filename);
        ~FileReader() = default;

        std::vector<std::string> getLines() const;

        void ReadLines();
        void PrintLines() const;
};


class GetAllProcess {
    private:
        std::vector<std::string> lines;
        std::string pname;
    public:
        GetAllProcess(std::vector<std::string> lines);
        ~GetAllProcess() = default;

        std::vector<std::string> LineSplitter(std::string &line);
        void AnalyzeProcesses();
        void printvectorprs();
        void PrintPages();
};


FileReader::FileReader(std::string filename) { this->filename = filename; }

std::vector<std::string> FileReader::getLines() const { return lines; }

void FileReader::ReadLines()
{
    std::ifstream file(filename, std::ios::in);
    std::string temp = "";

    while (std::getline(file, temp))
        if (temp[0] != '\0')
            lines.push_back(temp);
}

void FileReader::PrintLines() const
{
    std::for_each(lines.begin(), lines.end(), [](std::string item) { std::cout << item << '\n'; });
}

GetAllProcess::GetAllProcess(std::vector<std::string> lines) { this->lines = lines; }

std::vector<std::string> GetAllProcess::LineSplitter(std::string &line)
{
    std::vector<std::string> result;
    std::string tmp = "";
    std::stringstream ss(line);

    for (; ss >> tmp;) result.push_back(tmp);
    return result;
}

void GetAllProcess::AnalyzeProcesses(){
    bool flag = true;
    std::string tempname;
    Var* tempvar;
    Page* page;
    int pagenumber;
    std::vector<std::string> AvVari;
    int sum =0;
    std::vector<std::string> tempvector;
    for( std::string item : lines){
        if(item.substr(0,7) == "Process"){
            flag = false;
            tempname = item.substr(7);
            pagenumber = 0;
            sum = 0;
        }
        else if(flag == false){
            tempvector = LineSplitter(item);
            sum += stoi(tempvector[2]);
            std::cout<<"Sum: "<<sum<<std::endl;
            if(sum <= 400){
                std::cout<<"----------\n";
                std::cout<<"befor : "<<AvVari.size()<<std::endl;
                AvVari.push_back(tempvector[1]);
                std::cout<<"after : "<<AvVari.size()<<std::endl;
            }
            if(sum > 400){
                sum -= stoi(tempvector[2]);
                AvVari.pop_back();
                page = new Page{tempname,pagenumber,AvVari};
                Pageptr.push_back(page);
                pagenumber++;
                sum=0;
            }
            tempvar = new Var{tempname,tempvector[1],stoi(tempvector[2])};
            prs.push_back(tempvar);
           

        }
    }

}

void GetAllProcess::printvectorprs(){
    for(auto item : prs){
        std::cout<<item->process_name<<" "<<item->variable_name<<" "<<item->variable_size<<std::endl;
    }
}

void GetAllProcess::PrintPages(){
    for(auto item : Pageptr){
        std::cout<<item->pname<<" "<<item->pagenumber<<" ";
        for(auto itemone : item->varAvailable){
            std::cout<<itemone<<" ";
        }
    }
}   


#endif
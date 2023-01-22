#ifndef HEADER_HPP
#define HEADER_HPP
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>

struct Page
{
    std::string pname=0;
    int pagenumber=0;
    std::vector<std::string> varAvailable;
};

struct Var
{
    std::string process_name;
    std::string variable_name;
    int variable_size;
};

struct pagetable
{
    std::string pname;
    std::map <int, int> ptable;
};

struct frames
{
    std::string pname;
    Page ppage;
    bool isempty = true;
};
frames MemFrame[10];
std::vector<Page *> Pageptr;
std::vector<Var *> prs;

class FileReader
{
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

class GetAllProcess
{  
private:
    std::vector<std::string> lines;
    std::string pname;

public:
    GetAllProcess(std::vector<std::string> lines);
    ~GetAllProcess() = default;

    std::vector<std::string> LineSplitter(std::string &line);
    void pop_line() ;
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
    std::for_each(lines.begin(), lines.end(), [](std::string item)
                  { std::cout << item << '\n'; });
}

GetAllProcess::GetAllProcess(std::vector<std::string> lines) { this->lines = lines; }

std::vector<std::string> GetAllProcess::LineSplitter(std::string &line)
{
    std::vector<std::string> result;
    std::string tmp = "";
    std::stringstream ss(line);

    for (; ss >> tmp;)
        result.push_back(tmp);
    return result;
}

void GetAllProcess::pop_line()
{
    // string poptmp=this->lines.pop_back();
    // std::cout<<poptmp;
    std::cout<<"bafor : "<<this->lines.size()<<"\n";
    this->lines.pop_back();
    std::cout<<"after : "<<this->lines.size()<<"\n";
    //return poptmp;
}
void GetAllProcess::AnalyzeProcesses()
{
    bool flag = true;
    std::string tempname;
    Var *tempvar;
    Page *page;
    int pagenumber;
    std::vector<std::string> AvVari;
    int sum = 0;
    std::vector<std::string> tempvector;
    for (std::string item : lines)
    {
        if (item.substr(0, 7) == "Process")
        {
            if (sum < 400 && sum != 0)
            {
                
                page = new Page{tempname, pagenumber, AvVari};
                //std::cout<<"AvVari size : "<<AvVari.size()<<"\n";
                Pageptr.push_back(page);
                AvVari.clear();
                pagenumber++;
                sum = 0;
            }
            flag = false;
            tempname = item.substr(8);
            pagenumber = 0;
            sum = 0;
        }
        else if (flag == false)
        {
            tempvector = LineSplitter(item);
            //pop_line();
            sum += stoi(tempvector[2]);
            if (sum <= 400)
            {
                AvVari.push_back(tempvector[1]);
            }
            if (sum > 400)
            {
                sum -= stoi(tempvector[2]);
                
                page = new Page{tempname, pagenumber, AvVari};
              //  std::cout<<"AvVari size : "<<AvVari.size()<<"\n";
                Pageptr.push_back(page);
                AvVari.clear();
                pagenumber++;
                sum = 0;
                AvVari.push_back(tempvector[1]);
                sum += stoi(tempvector[2]);
            }
            tempvar = new Var{tempname, tempvector[1], stoi(tempvector[2])};
            prs.push_back(tempvar);
        }
    }
    if (sum < 400 && sum != 0)
    {
        
        page = new Page{tempname, pagenumber, AvVari};
        //std::cout<<"AvVari size : "<<AvVari.size()<<"\n";
        Pageptr.push_back(page);
        AvVari.clear();
        pagenumber++;
        sum = 0;
    }
}

void GetAllProcess::printvectorprs()
{
    for (auto item : prs)
    {
        std::cout << item->process_name << " " << item->variable_name << " " << item->variable_size << std::endl;
    }
}

void GetAllProcess::PrintPages()
{
    for (auto item : Pageptr)
    {
        std::cout << item->pname << " " << item->pagenumber << " ";
        for (auto itemone : item->varAvailable)
        {
            std::cout << itemone << " ";
        }
        std::cout << "\n";
    }
}

int Search(std::string pname, std::string variable)
{
    int page;
    for (auto item : Pageptr)
    {
        if (item->pname == pname)
        {
            page = item->pagenumber;
            for (auto itemone : item->varAvailable)
            {
                if (itemone == variable)
                {
                    return page;
                }
            }
        }
    }
    return -1;
}


void SetFrame()
{
    int i=0;
    for (auto item : Pageptr)
    {
        if(MemFrame[i].isempty==true)
        {
            MemFrame[i].pname=item->pname;
           // MemFrame[i].ppage=item;
            MemFrame[i].isempty=false;
            i++;
        }
    }
    std::cout<<i<<std::endl;

}

#endif
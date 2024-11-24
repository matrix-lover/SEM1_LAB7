#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

void saveInFile(const string& filename, const vector<Book>& catalog)
{
    ofstream out(filename);
    if(!out.is_open())
    {
        cerr << "Error" << endl;
        return;
    }
    
    for(Book book : catalog)
    {
        out << book.Author << "%" << book.title << "%"<< book.year << endl;
    }
    out.close();
}

void loadFromFile(const string filename, vector<Book>& catalog)
{
    string str;
    ifstream in(filename);
    
    if(!in.is_open())
    {
        cerr << "error" << endl;
    }
    string author;
    string title;
    string year;
    
    while(getline(in, str))
        {
            stringstream ss(str);
            
            getline(ss, author, '%');
            getline(ss, title, '%');
            getline(ss, year, '%');
            
            Book cur_book;
            cur_book.Author = author;
            cur_book.title = title;
            cur_book.year = stoi(year);
            catalog.push_back(cur_book);
        }
    in.close();
}

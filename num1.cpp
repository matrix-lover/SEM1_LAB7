#include <iostream>
#include <fstream>
#include <vector>

void saveInFile(const string& filename, const vector<string>& data)
{
    ofstream out(filename);
    if(!out.is_open())
    {
        cout << "error" << endl;
        return;
    }
    for(string str : data)
        out << str << endl;
    out.close();
}

 void loadFromFile(const string& filename, vector<string>& data)
{
     ifstream in(filename);
     string str;
     while(getline(in, str))
     {
         data.push_back(str);
     }
     in.close();
}

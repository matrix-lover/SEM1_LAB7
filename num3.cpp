

void saveInFile(const string& filename, const Groups& groups)
{
    ofstream out;
    out.open(filename);
    if(!out.is_open())
    {
        cerr << "error" << endl;
        return;
    }
    
    for(pair group : groups) // перечисление групп
    {
        out << group.first << "%"; // название группы
        for(Student student : group.second) // перечисление студентов группы
        {
            
            out << student.Name << "%" << student.year << "%"; // перечисление имени и года рождения студента
            for(pair score : student.RecordBook) // перечисление оценок студента
            {
                out << score.first << "%" << score.second << "%";
            }
            out << "|"; // отделяем студентов
        }
        out << endl;
    }
    out.close();
}

void loadFromFile(const string& filename, Groups& groups)
{
    string cur_line;
    
    ifstream in(filename);
    if(!in.is_open())
    {
        cerr << "error" << endl;
    }
    
    while(getline(in, cur_line)) // обрабатываем строку за строкой
    {
        string::iterator ch = cur_line.begin();
        vector<Student> stud;
        string gr_name;
        string cur_result;
        
        for(;;) // с помощью итератора обрабатываем строку до конца
        {
            if(*ch == '%') // условие оконяания цикла for: до разделителя считываем название группы
            {
                break; // и прекращаем цикл
            }
            cur_result += *ch; // если не разделитель, продолжаем считывать буквы
            ++ch;
        }
        gr_name = cur_result;
        cur_result.clear();
        ++ch; // обходим знак '%'
        
        while(ch != cur_line.end()) // с помощью итератора обрабатываем строку до конца
        {
            string st_name; // имя студента
            string year; // год рождения
            map<string, int> cur_rec_book; // при занесении данных перечисление Score имело значение, но при сохраненном файле оценки приобрели числовое значение
            
            while(*ch != '%') // имя
            {
                cur_result += *ch;
                ch++;
            }
            st_name = cur_result; // имя
            cur_result.clear();
            ++ch; // обходим знак '%'
            
            while(*ch != '%') // год
            {
                cur_result += *ch;
                ch++;
                
            }
            year = cur_result; // год
            cur_result.clear();
            ++ch; // обходим знак '%'
            
            while(*ch != '|' ) // журнал
            {
                while(*ch != '%') // название дисциплины
                {
                    cur_result += *ch;
                    ++ch;
                }
                ++ch; // обходим знак '%'
                
                cur_rec_book[cur_result] = *ch - 48; // оценка
                ++ch; // обходим оценку
                
                ++ch; // обходим знак '%'
                cur_result.clear();
            }
            ++ch; // обходим знак '|'
            
            Student student; // создаем объект Student
            student.Name = st_name;
            student.year = stoi(year);
            for(pair subj_score : cur_rec_book)
            {
                student.RecordBook[subj_score.first] = subj_score.second;
            }
            stud.push_back(student);
        }
        groups[gr_name] = stud;
    }
    in.close();
}

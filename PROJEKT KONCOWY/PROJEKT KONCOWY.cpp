#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class People
{
public:
    string name;
    string surname;
    int age;
};

bool checkData(string word1, string word2, string word3);

bool checkInt(string word);

bool checkInt(int age);

bool checkWord(string word);

int checkResponse(int range);

void reset(string& word1, string& word2, string& word3, vector <string> &words);

void change(vector <People> &person);

void add(vector <People>& person);

void remove(vector <People>& person);

void quit(vector <People>& person);

void print(vector <People> person);

int main()
{
    fstream file;
    do 
    {
        cout << "Enter a name of a file to open: " << endl;

        string fileName;
        getline(cin, fileName);
        file.open(fileName, ios::in);

        try
        {
            if (!file.good())
                throw 505;
        }
        catch(...)
        {
            cout << "You did not get access to the file." << endl << endl;
        }

    } while (!file.good());

    cout << "You got access to the file." << endl << endl;

    vector <string> words;
    vector <People> person;

    string word1 = "123";
    string word2 = "nothing";
    string word3 = "nothing2";

    int lineNumber = 1;
    char letter;
    string word;

    streampos position = 1;
    streampos positionEnd = 0;

    while (!file.eof() && position != positionEnd) 
    {
        int personCount = person.size();

        file.get(letter);

        position = file.tellg();
        file.seekg(1, ios::end);
        positionEnd = file.tellg();

        if (letter != '\n' && letter != ' ' && position != positionEnd)
            word += letter;

        else
        {
            string help = word3;

            word3 = word2;
            word2 = word1;
            word1 = word;

            int wordAge = 1;

            if (checkInt(word))
                wordAge = atoi(word.c_str());

            if (checkData(word1, word2, word3) && checkWord(word) && checkInt(wordAge))
            {
                words.push_back(word);

                if (words.size() % 3 == 0 && words.size() > 0)
                {
                    People newPerson;

                    newPerson.age = wordAge;
                    newPerson.surname = words[words.size() - 2];
                    newPerson.name = words[words.size() - 3];

                    person.push_back(newPerson);
                }
            }
            else
            {
                word1 = word2;
                word2 = word3;
                word3 = help;
            }
            word = "";
        }
        if (letter == '\n' || position == positionEnd)
        {
           try 
           {
                if (personCount == person.size())
                    throw 505;
           }
           catch(...)
           {
               cout << "Incorrect data. Line: " << lineNumber << endl;
           }

            reset(word1, word2, word3, words);
            lineNumber++;
        }

        file.seekg(position);
    }

    print(person);

    string response = "NULL";

    do
    {
        cout
            << endl
            << "1. Change values" << endl
            << "2. Add a person" << endl
            << "3. Remove a pereson" << endl << endl
            << "Quit and save. (q)" << endl << endl
            << "Choose option: ";

        int help;

        do {
            help = 0;
            getline(cin, response);

            if (response == "1" || response == "change")
            {
                try
                {
                    if (person.size() == 0)
                        throw 505;
                }
                catch (...)
                {
                    cout << "There is no person left. Choose \"add\" operation: ";
                    help = 1;
                }
                if (person.size() > 0)
                    change(person);
            }

            else if (response == "2" || response == "add")
                add(person);

            else if (response == "3" || response == "remove")
            {
                try
                {
                    if (person.size() == 0)
                        throw 505;
                }
                catch (...)
                {
                    cout << "There is no person left. Choose \"add\" operation: ";
                    help = 1;
                }
                if (person.size() > 0)
                    remove(person);
            }

            else if (response == "q")
                quit(person);

            else
            {
                try 
                {
                    throw 505;
                }
                catch(...)
                {
                    cout << "Wrong response. Try again: ";
                }
                help = 1;
            }

            if( response == "1" || response == "add" || 
                response == "2" || response == "change" ||
                response == "3" || response == "remove")

                print(person);

        } while (help);

    } while (response != "q");

    file.close();

    return 0;
}

bool checkData(string word1, string word2, string word3)
{
    if (checkInt(word1) xor checkInt(word2) xor checkInt(word3))
        return true;
    else
        return false;
}

bool checkInt(string word)
{
    for (size_t i = 0; i < word.length(); i++)
    {
        if (word[i] < 48 || word[i] > 57)
            return false;
    }
    return true;
}

bool checkInt(int age)
{
    if (age > 0 && age < 123)
        return true;

    return false;
}

bool checkWord(string word)
{
    for (size_t i = 0; i < word.length(); i++)
    {
        if (word[i] == 32)
            return false;
    }
    
    if (!checkInt(word))
    {
        if (word.length() < 1)
            return false;

        else if (word.length() >= 2)
        {
            for (size_t i = 0; i < word.length(); i++)
            {
                if (i > 2 && word[i] == word[i - 1] && word[i] == word[i - 2])
                    return false;

                if (word[i] >= 48 && word[i] <= 57)
                    return false;

                if (word[0] < 65 || word[0] > 90)
                    return false;

                if (i > 0 && word[i] >= 65 && word[i] <= 90)
                    return false;
            }
        }
    }


    return true;
}

int checkResponse(int range)
{
    string response;
    int intResponse;

    do
    {
        getline(cin, response);
        
        try
        {

            if (checkInt(response))
            {
                intResponse = atoi(response.c_str());

                if (intResponse > 0 && intResponse <= range)
                    return intResponse;

                else
                    throw 505;
            }
            else
                throw 505;
        }
        catch (...)
        {
            cout << "Wrong response. Try again: ";
        }

    } while (true);

}

void print(vector <People> person)
{
    cout << endl;

    for (size_t i = 0; i < person.size(); i++)
    {
        cout
            << i + 1 << ". "
            << person[i].name << ' '
            << person[i].surname << ' '
            << person[i].age << endl;
    }
}

void reset(string& word1, string& word2, string& word3, vector <string> &words)
{
    word1 = "123";
    word2 = "nothing";
    word3 = "nothing2";

    if (words.size() % 3 == 1)
        words.pop_back();

    if (words.size() % 3 == 2)
    {
        words.pop_back();
        words.pop_back();
    }
}

void change(vector <People> &person)
{
    print(person);

    string numberObject;
    int intObject;

    string numberField;
    int intField;

    cout << endl << "Choose person to change data: ";

    intObject = checkResponse(person.size());

    cout
        << endl
        << "1. Name" << endl
        << "2. Surname" << endl
        << "3. Age" << endl << endl
        << "Choose field you want to change: " ;

    intField = checkResponse(3);

    string name;
    string surname;
    string age;
    int intAge = 0;

    switch (intField)
    {
    case 1:
        cout << "Write a new name: ";

        do
        {
            getline(cin, name);

            try
            {
                if (checkWord(name) && !checkInt(name))
                    person[intObject - 1].name = name;

                else
                    throw 505;
            }
            catch (...)
            {
                cout << "Wrong response. Try again: ";
            }

        } while (!checkWord(name) || checkInt(name));

        break;

    case 2:
        cout << "Write a new surname: ";

        do
        {
            getline(cin, surname);

            try
            {
                if (checkWord(surname) && !checkInt(surname))
                    person[intObject - 1].surname = surname;

                else
                    throw 505;
            }
            catch (...)
            {
                cout << "Wrong response. Try again: ";
            }

        } while (!checkWord(surname) || checkInt(surname));

        break;

    case 3:
        cout << "Write a new age: ";
        
        do
        {
            getline(cin, age);

            try
            {
                if (checkInt(age))
                {
                    intAge = atoi(age.c_str());

                    if (checkInt(intAge))
                        person[intObject - 1].age = intAge;

                    else
                        throw 505;
                }
                else
                    throw 505;
            }
            catch (...)
            {
                cout << "Wrong response. Try again: ";
            }

        } while (!checkInt(intAge));

        break;
    }
}

void add(vector <People>& person)
{

    string name;
    string surname;
    string age;
    int intAge = 0;

    People newPerson;

    cout << "Write a name: ";

    do
    {
        getline(cin, name);

        try
        {
            if (checkWord(name) && !checkInt(name))
                newPerson.name = name;

            else
                throw 505;
        }
        catch (...) 
        {
            cout << "Wrong response (name). Try again: ";

        }

    } while (!checkWord(name) || checkInt(name));

    cout << "Write a surname: ";

    do
    {
        getline(cin, surname);

        try
        {
            if (checkWord(surname) && !checkInt(surname))
                newPerson.surname = surname;

            else
                throw 505;
        }
        catch (...)
        {
            cout << "Wrong response (name). Try again: ";

        }

    } while (!checkWord(surname) || checkInt(surname));

    cout << "Write an age: ";

    do
    {
        getline(cin, age);

        try
        {
            if (checkInt(age))
            {
                intAge = atoi(age.c_str());

                if (checkInt(intAge))
                    newPerson.age = intAge;

                else
                    throw 505;
            }
            else
                throw 505;
        }
        catch (...)
        {
            cout << "Wrong response (age). Try again: ";
        }

    } while (!checkInt(intAge));

    person.push_back(newPerson);
}

void remove(vector <People>& person)
{
    cout << "Which element do you want to remove: ";

    int number = checkResponse(person.size());
    auto it = person.begin() + number - 1;

    person.erase(it);
}

void quit(vector <People>& person)
{
    fstream file;
    string txt = "";
    string fileName;

    cout << endl << "Enter a name of a file to save: " << endl;

    do
    {
        txt = "";
        getline(cin, fileName);

        try
        {
            if (fileName.length() < 4)
                throw 505;

            else
            {
                for (size_t i = 0; i < 4; i++)
                {
                    txt += fileName[fileName.length() - 4 + i];
                }

                cout << endl;

                if (txt != ".txt")
                    throw 505;
            }
        }
        catch (...)
        {
            cout << "Wrong extension. Try again: " << endl;
        }

    } while (txt != ".txt");

    file.open(fileName, ios::out);

    cout << "You got access to the file." << endl;

    for (size_t i = 0; i < person.size(); i++)
    {
        file
            << person[i].name << ' '
            << person[i].surname << ' '
            << person[i].age << endl;
    }

    file.close();
}
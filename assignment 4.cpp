//  Ameha Teshome
// Assignment #4
// Xcode on Mac
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <cstdlib>

const int SIZE = 23907;

using namespace std;

void dictionary(const string& fileName, string* diction);
void spellingCheck(char* line, int numbOfLine, const string* diction);
void lowerCase(char* file);
void lowerCase(string& file);
void sort(string* dict);
bool binarysearch(const char* word, const string* diction);

int main()
{
    const string dictionaryWords = "unsorted_words.txt";
    const string haveAdream = "ihaveadream.txt";
    char buffer[100];
    string word;
    string* diction = new string[SIZE];
    dictionary(dictionaryWords, diction);
    sort(diction);
    int numbOfLine = 0;

    ifstream inFile(haveAdream.c_str());
    if (!inFile)
    {
        cerr << "could not opened " << haveAdream << endl;
        exit(1);
    }
    while (!inFile.eof())
    {
        numbOfLine++;
        inFile.getline(buffer, sizeof(buffer));
        if (inFile.eof()) break;
        lowerCase(buffer);
        spellingCheck(buffer, numbOfLine, diction);
    }
    delete[] diction;
}
void spellingCheck(char* line, int numbOfLine, const string* diction)
{
    char *ptr = line;
    ptr = strtok(line, " ,;:.!-\r\"");
    while (ptr != NULL)
    {
        if (!binarysearch(ptr, diction))
        {
            cout << "Misspelled word, " << ptr << " on line " << numbOfLine << endl;
        }
        ptr = strtok(NULL, " ,;:.!-\r\"");
    }
}
void dictionary(const string& fileName, string* diction)
{
    ifstream inFile(fileName.c_str());
    if (!inFile)
    {
        cerr << "could not read " << fileName << endl;
        exit(1);
    }
    for (int i = 0; i < SIZE; i++)
    {
        inFile >> diction[i];
        lowerCase(diction[i]);
    }
}
bool binarysearch(const char *size, const string* diction)
{
    int first, last, middle;
    string wordStr(size);
    first = 0;
    last = SIZE - 1;
    string middleWord;
    int compare;

    while (first <= last)
    {
        middle = (first + last) / 2;
        middleWord = diction[middle];
        compare = strcmp(size, middleWord.c_str());
        if (compare < 0)
        {
            last = middle - 1;
        }
        else if (compare > 0)
        {
            first = middle + 1;
        }
        else
        {
            return true;
        }
    }
    if (wordStr.substr(wordStr.size() - 1, 1) == "s")
    {
        if (binarysearch(wordStr.substr(0, wordStr.size() - 1).c_str(), diction))
            return true;
    }
    return false;
}
void lowerCase(char* file)
{
    for (size_t i = 0; i < strlen(file); i++)
        file[i] = tolower(file[i]);
}
void lowerCase(string& file)
{
    for (size_t i = 0; i < file.size(); i++)
        file[i] = tolower(file[i]);
}
void sort(string* dict)
{
    int a, j;
    string temp;
    bool ifFound;
    for (int i = 1; i < SIZE; i++)
    {
        ifFound = false;
        temp = dict[i];
        for (j = 0, a = i - 1; a >= 0 && !ifFound; j++)
        {
            if (temp < dict[a])
            {
                dict[a + 1] = dict[a];
                a--;
            }
            else
            {
                ifFound = true;
            }
        }
        dict[a + 1] = temp;
    }
}



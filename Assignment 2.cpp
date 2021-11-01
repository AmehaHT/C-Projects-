// Assignment 2
// Spring 2020

#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const int DictionarySize = 16000;
const int KeyWordsSize = 84;

void getFile(const string& filename,string*, int filesize);
bool find(const string& searchValue, const string dictionary[]);
void sort( string* list, int size);
void swap( string&,  string&);

int main()
{
    const string wordFile = "c:/temp/unsorted_dictionary.txt";
    const string keywordFile = "c:/temp/keywords.txt";
    const string outputFile = "c:/temp/ass2output.txt";

    int notfoundWords = 0;

    string dictionary[DictionarySize];
    string keywords[KeyWordsSize];

    getFile(wordFile, dictionary, DictionarySize);
    getFile(keywordFile, keywords, KeyWordsSize);

    cout << "Sorting Dictionary data ... ";
    sort(dictionary, DictionarySize);
    cout << "done" << endl;

    cout << "Sorting keyword data ... ";
    sort(keywords,KeyWordsSize);
    cout << "done" << endl << endl;

    ofstream fout(outputFile);
    fout << "keywords not in the dictionary" << endl;
    if (fout)
    {
        for (int i= 0; i < KeyWordsSize; i++)
        {
            if (!find(keywords[i],dictionary))
            {
                fout << keywords[i]<< endl;
                notfoundWords++;
            }
        }
        cout << "Number of keywords not found = " << notfoundWords << endl;
    }
    else
    {
        cerr << "Unable to open output file " << outputFile << endl;
    }
}

void getFile(const string& filename, string* array, int size)
{
    ifstream fin(filename.c_str());
    if (!fin)
    {
        cerr << "Unable to open word file " << filename << endl;
        exit(1);
    }

    cout << "Reading file: " << filename << endl;

    for (int i = 0; i < size; i++)
    {
        fin >> array[i];
    }
    fin.close();
}

bool find(const string& searchValue, const string dictionary[])
{
    int low, high, middle;
    low = 0;
    high = DictionarySize-1;

    while (low <= high)
    {
        middle = (low + high) / 2;
        if (searchValue < dictionary[middle])
        {
            high = middle - 1;
        }
        else if (searchValue > dictionary[middle])
        {
            low = middle + 1;
        }
        else
        {
            return true;
        }
    }

    return false;
}

void sort( string a[], int size)
{
    // minIndex is the position in the unsorted part containing the minimum
    int minIndex;
    for (int i = 0; i < size - 1; i++)
    {
                // find the position of the minimum in the unsorted part
        minIndex = i;
        for (int j = i+1; j < size; j++)
        {
            if (a[j] < a[minIndex])
            {
                minIndex = j;
            }
        }

        // swap the value of the minimum in the unsorted part with the next
        // value in the sorted part

        if(minIndex != i)    // don�t swap if the minimum is already in place
        {
            swap(a[i],a[minIndex]);
        }
    }
}

void swap( string& a,  string& b)
{
    string temp = a;
    a = b;
    b = temp;
}

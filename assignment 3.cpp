// Assignment 3 Solution - Spring 2020

#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

const string InputFile = "c:/temp/VFTAX.csv";
const string ModifiedFile = "c:/temp/VFTAXmodified.csv";
const int NumRows = 306;
const int NumCols = 2;

void sortArray(int data [][NumCols], int col, char order = 'a');
void swapRow(int a[], int b[]);
void swap(int& a, int& b);
void printDate(int date);
float movingAverage(int data [][NumCols], int numDays);
void getArrayData(int data [][NumCols]);
void printFirst5Rows(int data [][NumCols]);
void printFirst10RowsOfArray(int data [][NumCols]);

int main()
{
    float average;
    float latestClose;
    int array[NumRows][NumCols];
    int currentDate;

    cout << setprecision(2) << fixed;

    // get array data from file
    getArrayData(array);

    printFirst10RowsOfArray(array);

    // sort the array in descending order by date
    sortArray(array,0,'d');

    currentDate = array[0][0];

    cout << "Current Date: ";
    printDate(currentDate);
    cout << endl;
    latestClose = array[0][1] / 100.f;
    cout << "Current Close: $" << latestClose << endl << endl;

    cout << "The latest five closes are:" << endl;
    printFirst5Rows(array);

    // sort the array in ascending order by date
    sortArray(array,0);
    cout << "The oldest five closes are:" << endl;
    printFirst5Rows(array);

    // sort the array in descending order by close
    sortArray(array,1,'d');
    cout << "The five highest closes are:" << endl;
    printFirst5Rows(array);

    // sort the array in descending order by date
    sortArray(array,0,'d');

    // 50 day moving average
    cout << "50 Day Moving Average: $" << movingAverage(array,50) << endl;

    // 200 day moving average
    average =  movingAverage(array,200);
    cout << "200 Day Moving Average: $" << average << endl;

    // calculate the percent gain over the 200 day moving average
    float percentGain = (latestClose - average) / average * 100;
    cout << "Percent gain over 200 Day Moving Average: " << percentGain << "%" << endl;

    // Make buy/sell/hold recommendation
    string recommendation;
    if (percentGain < -5) recommendation = "Buy";
    else if (percentGain > 5) recommendation = "Sell";
    else recommendation = "Hold";
    cout << "Recommendation: " << recommendation << endl;
}

void sortArray(int data [][NumCols], int col, char order)
{
    int i, j;
    for (i = 0; i < NumRows - 1; i++)
    {
        for (j = i+1; j < NumRows; j++)
        {
            if (order == 'a')
            {
                if (data[i][col] > data[j][col]) swapRow(data[i],data[j]);
            }
            else
            {
                if (data[i][col] < data[j][col]) swapRow(data[i],data[j]);
            }
        }
    }
}


void    swapRow(int a[], int b[])
{
    for (int i = 0; i < NumCols; i++)
    {
        swap(a[i],b[i]);
    }
}


void swap(int& a, int& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void printDate(int date)
{
    cout << setfill('0');
    cout << setw(2) << date % 10000 / 100;
    cout << "/";
    cout << setw(2) << date % 100;
    cout << "/";
    cout << setw(2) << date / 10000 % 100;
    cout << setfill(' ');
}

float movingAverage(int data [][NumCols], int numDays)
{
    int average = 0;
    for (int i = 0; i < numDays; i++)
    {
        average += data[i][1];
    }
    return average / static_cast<float>(numDays) / 100;
}

void getArrayData(int data [][NumCols])
{
    string dummy;
    char ch;
    float tempFloat;
    ifstream fin(InputFile);
    if (!fin)
    {
        cerr << "Unable to open input file " << InputFile << endl;
        exit(1);
    }

    ofstream fout(ModifiedFile);
    if (!fout)
    {
        cerr << "Unable to open output file " << ModifiedFile << endl;
        exit(2);
    }

    // Read and ignore first line of input file
    getline(fin,dummy);

    while (!fin.eof())
    {
        ch = fin.get();

        if (ch == ',')
        {
            fout << ' ';
        }
        else fout << ch;
    }
    fin.close();
    fout.close();

    fin.open(ModifiedFile);
    if (!fin)
    {
        cerr << "Unable to open modified input file " << ModifiedFile << endl;
        exit(3);
    }
    string tempDate;
    for (int i = 0; i < NumRows; i++ )
    {
        fin >> dummy;
        tempDate = dummy.substr(0,4);
        tempDate += dummy.substr(5,2);
        tempDate += dummy.substr(8,2);
        data[i][0] = stoi(tempDate);
        fin >> dummy >> dummy >> dummy >> tempFloat >> dummy >> dummy;
        data[i][1] = static_cast<int>(100 * tempFloat + 0.5);
    }
}

void printFirst5Rows(int data [][NumCols])
{
    for (int i = 0; i < 5; i++)
    {
        printDate(data[i][0]);
        cout << "   $" << data[i][1] / 100.f << endl;
    }
    cout << endl;
}

void printFirst10RowsOfArray(int data [][NumCols])
{
    for (int i = 0; i < 10; i++)
    {
        cout << data[i][0] << setw(7) << data[i][1] << endl;
    }
    cout << endl;
}

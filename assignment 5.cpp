//  Ameha Teshome
// Assignment #4
// Xcode on Mac
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

const unsigned NumberOfStudents = 55;
const unsigned PointsPossible = 400;
const unsigned NumberOfAssignments = 10;
const unsigned NumberOfExercises = 10;
const string InputFilename = "ass5data.txt";
const string OutputFilename = "ass5output.txt";

struct Student
{
    int id;
    string name;
    int exercise[NumberOfExercises];
    int assignment[NumberOfAssignments];
    int midterm;
    int fin;
    int codelab;
    int exerciseTotal;
    int assignmentTotal;
    int totalPoints;
    int percent;
    string grade;
};
//function prototypes
void getStudentDataFromFile(struct Student students[],const string& InputFilename); //function to get data from from file
void printStudentDataToFile(struct Student students[],const string& OutputFilename); //function to print everything into output file
void determineGrades(struct Student students[]); //function to determine and count grates
void sort(struct Student students[]); //function to sort in descending order
void swap(int& a, int& b); //function to swap


int main()
{
    Student students[NumberOfStudents];
    getStudentDataFromFile(students,InputFilename); //calling function
    determineGrades(students); //calling function
    sort(students); //calling function
    printStudentDataToFile(students,OutputFilename); //calling function

}

//function definitions
void getStudentDataFromFile(struct Student students[], const string& InputFilename) //function to get data from from file
{
    ifstream inputFile;
    inputFile.open(InputFilename); //opening file
    if(!inputFile)
    {
        cout << InputFilename << " is not open !";
        exit(1);
    }
    else
    {
        string buffer, temp, temp2, temp3, temp4, temp5;
        getline(inputFile, buffer);
        for(int i = 0; i < NumberOfStudents; i++)
        {
            getline(inputFile, buffer);
            temp = buffer.substr(0,8);
            students[i].id = stoi(temp);
            temp2 = buffer.substr(9, 19);
            students[i].name = temp2;
            for(int j = 0; j < 10; j++)
            {
                students[i].exercise[j] = stoi(buffer.substr(29 + 2*j, 2));
            }
            for(int j = 0; j < 10; j++)
            {
                students[i].assignment[j] = stoi(buffer.substr(49 + 3*j, 3));
            }
            temp3 = buffer.substr(79,2);
            students[i].midterm = stoi(temp3);
            temp4 = buffer.substr(82,3);
            students[i].fin = stoi(temp4);
            temp5 = buffer.substr(86,2);
            students[i].codelab = stoi(temp5);
        }


    }
}

void printStudentDataToFile(struct Student students[],const string& OutputFilename) //function to print everything into output file
{
    ofstream outputFile;
    outputFile.open(OutputFilename);
    if(!outputFile)
    {
        cout << OutputFilename << " is not open !";
        exit(1);
    }
    else
    {
        outputFile << "Stud Id  Name                Ex Ass Mi Fin CL Tot Pct Gr\n";
        outputFile << "-------- ------------------- -- --- -- --- -- --- --- --\n";
        determineGrades(students);
        for(int i = 0; i < NumberOfStudents; i++)
        {
            outputFile << setfill('0') << setw(8) << students[i].id << " " << setfill(' ') << students[i].name << setw(3) << students[i].exerciseTotal << setw(4) << students[i].assignmentTotal;
            outputFile << setw(3) << students[i].midterm << setw(4) << students[i].fin << setw(3) << students[i].codelab << setw(4) << students[i].totalPoints << setw(4) << students[i].percent;
            outputFile << setw(3) << students[i].grade << endl;
        }
    }
}
void determineGrades(struct Student students[]) //function to determine and count grates
{
    for(int i=0; i < NumberOfStudents; i++)
    {
        students[i].exerciseTotal = 0;
        for(int j=0; j<NumberOfExercises; j++)
        {
            students[i].exerciseTotal += students[i].exercise[j];
        }
        students[i].assignmentTotal = 0;
        int min2 = 20;
        for(int j=0; j < NumberOfAssignments; j++)
        {
            students[i].assignmentTotal += students[i].assignment[j];
            if( min2 > students[i].assignment[j])
                min2 = students[i].assignment[j];
        }
        students[i].assignmentTotal -= min2;
        students[i].totalPoints = students[i].exerciseTotal + students[i].assignmentTotal + students[i].midterm + students[i].fin + students[i].codelab;
        double percents = 100 * static_cast<double>(students[i].totalPoints) / PointsPossible;
        students[i].percent = static_cast<int>(percents +.5);
        if (students[i].percent > 97 && students[i].percent <= 100)
        {
            students[i].grade = "A+";

        }
        else if (students[i].percent >= 93 && students[i].percent <= 97)
        {
            students[i].grade = "A ";

        }
        else if (students[i].percent >= 90 && students[i].percent < 93)
        {
            students[i].grade = "A-";

        }
        else if (students[i].percent > 87 && students[i].percent < 90)
        {
            students[i].grade = "B+";

        }
        else if (students[i].percent >= 83 && students[i].percent <= 87)
        {
            students[i].grade = "B ";

        }
        else if (students[i].percent >= 80 && students[i].percent < 83)
        {
            students[i].grade = "B-";

        }
        else if (students[i].percent > 77 && students[i].percent < 80)
        {
            students[i].grade = "C+";

        }
        else if (students[i].percent >= 73 && students[i].percent <= 77)
        {
            students[i].grade = "C ";

        }
        else if (students[i].percent >= 70 && students[i].percent < 73)
        {
            students[i].grade = "C-";

        }
        else if (students[i].percent > 67 && students[i].percent < 70)
        {
            students[i].grade = "D+";
        }
        else if (students[i].percent >= 63 && students[i].percent <= 67)
        {
            students[i].grade = "D ";

        }
        else if (students[i].percent >= 60 && students[i].percent < 63)
        {
            students[i].grade = "D-";

        }
        else if (students[i].percent >= 0 && students[i].percent < 60)
        {
            students[i].grade = "F ";
        }

    }
}
void sort(struct Student students[])  //function to sort in descending order
{
    int minIndex;
    for (int i = 0; i < NumberOfStudents - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < NumberOfStudents; j++)
        {
            if (students[j].totalPoints > students[minIndex].totalPoints)
            {
                minIndex= j;
            }
        }
        if (minIndex != i)
        {
            swap(students[i], students[minIndex]);
        }
    }
}

void swap(int& a, int& b) //function to swap
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

//  Ameha Teshome
// Assignment #4
// Xcode on Mac
#include <cstring>
#include <iostream>
using namespace std;

class String
{
    char* ptr;
    static int aCount;
public:
    String(const char* text = nullptr);
    String(const String&);
    ~String();
    String& operator=(const String& arg);
    const char* operator*() const;          // returns pointer to underlying char data
    int operator!() const;                  // return length of underlying char data
    String operator+(const String&) const;  // return catenated Strings
    String& operator+=(const String&);      // appends String argument
    char operator[](int index) const;       // returns the ith char of underlying char data
    bool operator<(const String&) const;    // returns true if String is less than argument String
    bool operator==(const String&) const;   // returns true if String is equal to argument String
    static int a_count();
};

// Static member initialization
int String::aCount = 0;

// Non-class member function prototypes
int count_a(const char* word);
ostream& operator<<(ostream& out, const String& arg);

int main()
{
    // Constructors
    String A("apple");
    String B("banana");
    String C("cantaloupe");
    String D(B);
    String E;

    // static member function
    cout << "Number of a's = " << String::a_count() << endl << endl;

    // Overloaded insertion operator
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "C = " << C << endl;
    cout << "D = " << D << endl;
    cout << "E = " << E << endl << endl;

    // Relational operators
    cout << boolalpha;
    cout << "A < B " << (A < B) << endl;
    cout << "B < A " << (B < A) << endl;
    cout << "A == B " << (A == B) << endl << endl;

    // Assignment operator
    A = B;
    cout << "A = " << A << endl;
    cout << "A == B " << (A == B) << endl << endl;

    // Size (bang) operator
    cout << "A size = " << !A << endl;
    cout << "E size = " << !E << endl << endl;

    // Unary * operator
    cout << "C text = " << *C << endl << endl;

    // Plus operator
    cout << "A + B = " << A + B << endl << endl;

    // Plus equal operator
    A += C;
    cout << "A = " << A << endl << endl;

    // Index operator
    cout << "A[3] = " << A[3] << endl << endl;

    // static member function
    cout << "Number of a's = " << String::a_count() << endl;
}

// String class constructors
String::String(const char* text)
    : ptr(text ? new char[strlen(text)+1] : nullptr)
{
    if (text)
    {
        strcpy(ptr,text);
        aCount += count_a(text);
    }
}

String::String(const String& arg)
    : ptr(new char[!arg+1])
{
    strcpy(ptr,arg.ptr);
    aCount += count_a(arg.ptr);
}

// String class destructors
String::~String()
{
    if (ptr)
    {
        aCount -= count_a(ptr);
        delete [] ptr;
        ptr = nullptr;
    }
}

int String::a_count()
{
    return aCount;
}

String& String::operator=(const String& arg)
{
    if (ptr)
    {
        aCount -= count_a(ptr);
        delete [] ptr;
    }
    if (!arg)
    {
        ptr = new char[!arg+1];
        strcpy(ptr,arg.ptr);
        aCount += count_a(ptr);
    }
    else ptr = nullptr;
    return *this;
}


const char* String::operator*() const
{
    return ptr;
}

int String::operator!() const
{
    return ptr ? strlen(ptr) : 0;
}

String& String::operator+=(const String& arg)
{
    *this = *this + arg;
    return *this;
}

String String::operator+(const String& arg) const
{
    char * tempPtr = new char[!*this + !arg + 1];
    strcpy(tempPtr,ptr);
    strcat(tempPtr,arg.ptr);
    String temp(tempPtr);
    delete [] tempPtr;
    return temp;
}

char String::operator[](int index) const
{
    if (index >= 0 && index < !*this)
        return ptr[index];
    return 0;
}

bool String::operator<(const String& arg) const
{
    return strcmp(ptr,arg.ptr) < 0;
}

bool String::operator==(const String& arg) const
{
    return strcmp(ptr,arg.ptr) == 0;
}

int count_a(const char* word)
{
    int count = 0;
    for (size_t i = 0; i < strlen(word); i++)
        if (word[i] == 'a') count++;
    return count;
}

ostream& operator<<(ostream& out, const String& arg)
{
    if (*arg) out << *arg;
    return out;
}

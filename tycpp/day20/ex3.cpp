#include <iostream>
using namespace std;

// Abstract exception data type
class Exception
{
    public:
        Exception(){}
        virtual ~Exception(){}
        virtual void PrintError() = 0;
};

// Derived class to handle memory problems.
// Note no allocation of memory in this class!
class OutOfMemory : public Exception
{
    public:
        OutOfMemory(){}
        ~OutOfMemory(){}
        virtual void PrintError();
    private:
};

void OutOfMemory::PrintError()
{
    cout << "Out of Memory!!" << endl;
}

// Derived class to handle bad numbers
class RangeError : public Exception
{
    public:
        RangeError(unsigned long number){badNumber = number;}
        ~RangeError(){}
        virtual void PrintError();
        virtual unsigned long GetNumber() { return badNumber; }
        virtual void SetNumber(unsigned long number) { badNumber = number; }
    private:
        unsigned long badNumber;
};

void RangeError::PrintError()
{
    cout << "Number out of range. You used " ;
    cout << GetNumber() << "!!" << endl;
}

void MyFunction();  // func. prototype

int main()
{
    try {
      MyFunction();
    }
    // Only one catch required, use virtual functions to do the
    // right thing.
    catch (Exception& theException) {
        theException.PrintError();
    }

    return 0;
}

void MyFunction()
{
    unsigned int *myInt = new unsigned int;
    long testNumber;

    if (myInt == 0)
        throw OutOfMemory();
    cout << "Enter an int: ";
    cin >> testNumber;

    // this weird test should be replaced by a series
    // of tests to complain about bad user input
    if (testNumber > 3768 || testNumber < 0)
        throw RangeError(testNumber);

    *myInt = testNumber;
    cout << "Ok. myInt: " << *myInt;
    delete myInt;
}

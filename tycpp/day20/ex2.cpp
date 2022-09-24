#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class OutOfMemory
{
    public:
        OutOfMemory(char *);
        char* GetString() { return itsString; }
    private:
        char* itsString;
};

OutOfMemory::OutOfMemory(char * theType)
{
    itsString = new char[80];
    char warning[] = "Out Of Memory! Can’t allocate room for: ";
    strncpy(itsString, warning, 60);
    strncat(itsString, theType, 19);
}

int main()
{
    try {
        int *myInt = new int;
        if (myInt == 0)
            throw OutOfMemory("int");
    } catch (OutOfMemory& theException) {
        cout << theException.GetString();
    }
    return 0;
}

#include <iostream>

class OutOfMemory {};

int main()
{
    try {
      int *myInt = new int;
      if (myInt == 0)
        throw OutOfMemory();
    } catch (OutOfMemory) {
        std::cout << "Unable to allocate memory!" << std::endl;
    }
    return 0;
}

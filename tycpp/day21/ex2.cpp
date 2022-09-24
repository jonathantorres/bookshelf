#include <iostream>

using namespace std;
#ifndef DEBUG
#define ASSERT(x)
#elif DEBUG == 1
#define ASSERT(x) \
if (!(x)) { \
    cout << "ERROR!! Assert " << #x << " failed" << endl; \
}
#elif DEBUG == 2
#define ASSERT(x) \
if (!(x)) { \
    cout << "ERROR!! Assert " << #x << " failed" << endl; \
    cout << " on line " << __LINE__  << endl; \
    cout << " in file " << __FILE__ << endl;  \
}
#endif

int main()
{
    return 0;
}

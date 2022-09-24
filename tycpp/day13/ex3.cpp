#include <iostream>
#include <string.h>

int main()
{
    char first_name[] = "Jorge";
    char initial[] = "L";
    char last_name[] = "Torres";
    char fullname[80];
    strcpy(fullname, first_name);
    strcpy(fullname + strlen(first_name), initial);
    strcpy(fullname + strlen(first_name) + strlen(initial), last_name);
    std::cout << fullname << std::endl;
    return 0;
}

// I don't think it will work, maybe the compiler will complain with a warning
// I think the way to fix it would be to set the maxlen variable
// to the std::string::size_type
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Student_info {
    std::string name;
    double midterm;
    double final;
    std::vector<double> homework;
};

int main(void)
{
    std::string::size_type maxlen;
    Student_info s;
    std::max(s.name.size(), maxlen);
    return 0;
}

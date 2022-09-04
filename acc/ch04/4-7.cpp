#include <iostream>
#include <iomanip>
#include <vector>

double average(const std::vector<double>& nums);

int main(void)
{
    std::vector<double> nums = {100.23,99.00,55.34,70.93,80.88};
    double avg = average(nums);

    std::cout << "Average is: " << std::setprecision(4) << avg << std::endl;

    return 0;
}

double average(const std::vector<double>& nums)
{
    double total = 0;

    if (nums.size() == 0) {
        return 0;
    }

    for (std::vector<double>::size_type i = 0; i < nums.size(); i++) {
        total += nums[i];
    }

    return total/nums.size();
}

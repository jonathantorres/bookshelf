#include <iostream>

class Employee
{
    public:
        Employee(int age, int years, int salary);
        ~Employee();
        void setAge(int age);
        int getAge();
        void setYearsOfService(int years);
        int getYearsOfService();
        void setSalary(int salary);
        int getSalary();
    private:
        int age;
        int years_of_service;
        int salary;
};

Employee::Employee(int age, int years, int salary)
{
    this->age = age;
    this->years_of_service = years;
    this->salary = salary;
}

Employee::~Employee() {}

void Employee::setAge(int age)
{
    this->age = age;
}

int Employee::getAge()
{
    return this->age;
}

void Employee::setSalary(int salary)
{
    this->salary = salary;
}

int Employee::getSalary()
{
    return this->salary;
}

int Employee::getYearsOfService()
{
    return this->years_of_service;
}

void Employee::setYearsOfService(int years)
{
    this->years_of_service = years;
}

int main()
{
    Employee *emp1 = new Employee(20, 4, 500);
    emp1->setAge(18);
    emp1->setSalary(200);
    emp1->setYearsOfService(3);
    std::cout << "emp1 age: " << emp1->getAge() << std::endl;
    std::cout << "emp1 salary: " << emp1->getSalary() << std::endl;
    std::cout << "emp1 years of service: " << emp1->getYearsOfService() << std::endl;
    delete emp1;
    emp1 = 0;
    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ios>
#include <exception>
#include <iomanip>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::streamsize;
using std::istream;
using std::max;
using std::setprecision;
using std::domain_error;

istream& read_hw(istream& in, vector<double>& hw);
double median(vector<double> vec);
double grade(double midterm, double final, const vector<double>& hw);
double grade(double midterm, double final, double homework);

class Student_info {
    public:
        Student_info();
        Student_info(istream& in);
        istream& read(istream& in);
        string name() const;
        double grade() const;
        bool valid() const;
    private:
        string n;
        double midterm;
        double final;
        vector<double> homework;
};

Student_info::Student_info()
{
    midterm = 0;
    final = 0;
}

Student_info::Student_info(istream& in)
{
    read(in);
}

istream &Student_info::read(istream& in)
{
    in >> n >> midterm >> final;
    read_hw(in, homework);

    return in;
}

string Student_info::name() const
{
    return n;
}

bool Student_info::valid() const
{
    return !homework.empty();
}

double Student_info::grade() const
{
    return ::grade(midterm, final, homework);
}

bool compare(const Student_info& x, const Student_info& y);

int main(void)
{
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;

    // read and store the data
    while (record.read(cin)) {
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }

    // alphabetize the student records
    sort(students.begin(), students.end(), compare);

    // write the names and grades
    for (vector<Student_info>::size_type i = 0; i != students.size(); ++i) {
        cout << students[i].name() << string(maxlen + 1 - students[i].name().size(), ' ');
        try {
            double final_grade = students[i].grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade << setprecision(prec) << endl;
        } catch (domain_error& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}

double grade(double midterm, double final, const vector<double>& hw)
{
    if (hw.size() == 0) {
        throw domain_error("student has done no homework");
    }
    return grade(midterm, final, median(hw));
}

double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double median(vector<double> vec)
{
    typedef vector<double>::size_type vec_sz;
    vec_sz size = vec.size();
    if (size == 0) {
        throw domain_error("median of an empty vector");
    }

    sort(vec.begin(), vec.end());
    vec_sz mid = size / 2;

    return size % 2 == 0 ? (vec[mid] + vec[mid-1]) / 2 : vec[mid];
}

// read homework grades from an input stream into a `vector'
istream& read_hw(istream& in, vector<double>& hw)
{
    if (in) {
        // get rid of previous contents
        hw.clear();

        // read homework grades
        double x;
        while (in >> x) {
            hw.push_back(x);
        }

        // clear the stream so that input will work for the next student
        in.clear();
    }
    return in;
}

bool compare(const Student_info& x, const Student_info& y)
{
    return x.name() < y.name();
}

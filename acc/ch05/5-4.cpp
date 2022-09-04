#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>

using std::cin;
using std::setprecision;
using std::cout;
using std::sort;
using std::domain_error;
using std::streamsize;
using std::istream;
using std::endl;
using std::string;
using std::max;
using std::vector;
using std::list;

struct Student_info {
    std::string name;
    double midterm;
    double final;
    std::vector<double> homework;
};

double median(vector<double> vec);
double grade(double midterm, double final, double homework);
double grade(double midterm, double final, const vector<double>& hw);
double grade(const Student_info& s);
bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);

int main(void)
{
    list<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0; // the length of the longest name

    // read and store all the students data.
    // Invariant: students contains all the student records read so far
    // maxlen contains the length of the longest name in students
    while (read(cin, record)) {
        // find length of longest name
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }

    // alphabetize the student records
    students.sort(compare);

    // write the names and grades
    for (list<Student_info>::const_iterator it = students.begin(); it != students.end(); it++) {
        // write the name, padded on the right to maxlen + 1 characters
        cout << it->name << string(maxlen + 1 - it->name.size(), ' ');

        // compute and write the grade
        try {
            double final_grade = grade(*it);
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade << setprecision(prec);
        } catch (domain_error &e) {
            cout << e.what();
        }
        cout << endl;
    }
    return 0;
}

bool compare(const Student_info& x, const Student_info& y)
{
    return x.name < y.name;
}

istream& read(istream& is, Student_info& s)
{
    // read and store the student's name and midterm and final exam grades
    is >> s.name >> s.midterm >> s.final;
    read_hw(is, s.homework); // read and store all the student's homework grades

    return is;
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

double grade(double midterm, double final, const vector<double>& hw)
{
    if (hw.size() == 0) {
        throw domain_error("student has done no homework");
    }
    return grade(midterm, final, median(hw));
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

double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(const Student_info& s)
{
    return grade(s.midterm, s.final, s.homework);
}

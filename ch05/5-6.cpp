#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<ios>
#include<stdexcept>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::max;
using std::istream;
using std::domain_error;

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
bool fgrade(const Student_info& s);
vector<Student_info> extract_fails(vector<Student_info>& students);
std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);

int main(void)
{
    vector<Student_info> students;
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

    vector<Student_info> fails = extract_fails(students);

    for (std::vector<Student_info>::const_iterator it = fails.begin(); it != fails.end(); it++) {
        // write the name, padded on the right to maxlen + 1 characters
        cout << it->name << string(maxlen + 1 - it->name.size(), ' ');
    }
    return 0;
}

vector<Student_info> extract_fails(vector<Student_info>& students)
{
    vector<Student_info> fail;
    vector<Student_info>::size_type i = 0;

    // invariant:elements [0, i) of students represent passing grades
    while (i != students.size()) {
        if (fgrade(students[i])) {
            fail.push_back(students[i]);
            students.erase(students.begin() + i);
        } else {
            ++i;
        }
    }
    return fail;
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

bool fgrade(const Student_info& s)
{
    return grade(s) < 60;
}

double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const vector<double>& hw)
{
    if (hw.size() == 0) {
        throw domain_error("student has done no homework");
    }
    return grade(midterm, final, median(hw));
}

double grade(const Student_info& s)
{
    return grade(s.midterm, s.final, s.homework);
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

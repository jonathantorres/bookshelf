#include<iostream>
#include<vector>
#include<string>

using std::vector;

struct Student_info {
    std::string name;
    double midterm;
    double final;
    std::vector<double> homework;
};

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

    for (std::vector<Student_info>::cons_iterator it = fails.begin(); it != fails.end(); it++) {
        // write the name, padded on the right to maxlen + 1 characters
        cout << it.name << string(maxlen + 1 - students[i].name.size(), ' ');
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
            fail.push_back(students[i]};
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

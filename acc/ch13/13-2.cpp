#include <iostream>
#include <algorithm>
#include <iomanip>
#include <ios>
#include <stdexcept>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::setprecision;
using std::setw;
using std::sort;
using std::streamsize;
using std::string;
using std::vector;
using std::min;
using std::domain_error;
using std::max;

std::istream& read_hw(std::istream& in, std::vector<double>& hw);
double grade(double, double, double);
double grade(double, double, const std::vector<double>&);
double median(vector<double> vec);

class Core {
public:
    Core(): midterm(0), final(0) { }
    Core(std::istream& is) { read(is); }

    std::string name() const;

    virtual std::istream& read(std::istream&);
    virtual double grade() const;
    virtual ~Core() { }

protected:
    // accessible to derived classes
    std::istream& read_common(std::istream&);
    double midterm, final;
    std::vector<double> homework;

    virtual Core* clone() const { return new Core(*this); }

private:
    // accessible only to `Core'
    std::string n;
};

class Grad: public Core {
public:
    Grad(): thesis(0) { }
    Grad(std::istream& is) { read(is); }

    double grade() const;
    std::istream& read(std::istream&);
private:
    double thesis;
    Grad* clone() const { return new Grad(*this); }
};

string Core::name() const { 
    std::cout << "Core::name()\n";
    return n;
}

double Core::grade() const
{
    std::cout << "Core::grade()\n";
    return 0;
    // return ::grade(midterm, final, homework);
}

istream& Core::read_common(istream& in)
{
    // read and store the student's name and exam grades
    in >> n >> midterm >> final;
    return in;
}

istream& Core::read(istream& in)
{
    read_common(in);
    read_hw(in, homework);
    return in;
}

istream& Grad::read(istream& in)
{
    read_common(in);
    in >> thesis;
    read_hw(in, homework);
    return in;
}

double Grad::grade() const
{
    std::cout << "Grad::grade()\n";
    return 0;
    // return min(Core::grade(), thesis);
}

// read homework grades from an input stream into a `vector<double>'
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

// compute a student's overall grade from midterm and final exam grades and homework grade
double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

// compute a student's overall grade from midterm and final exam grades
// and vector of homework grades.
// this function does not copy its argument, because `median' does so for us.
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

int main(void)
{
    Core* p1 = new Core;
    Core* p2 = new Grad;
    Core s1;
    Grad s2;

    p1->grade(); // calls Core::grade()
    p1->name(); // calls Core::name()

    p2->grade(); // calls Grad::grade()
    p2->name(); // calls Core::name()

    s1.grade(); // calls Core::grade()
    s1.name(); // calls Core::name()

    s2.name(); // calls Core::name()
    s2.grade(); // calls Grad::grade()

    return 0;
}

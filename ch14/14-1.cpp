#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ios>
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
    friend class Student_info;
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

bool compare(const Core&, const Core&);
bool compare_Core_ptrs(const Core* cp1, const Core* cp2);
double grade(double, double, double);
double grade(double, double, const std::vector<double>&);
double median(vector<double> vec);

class Student_info {
public:
    // constructors and copy control
    Student_info(): cp(0) { }
    Student_info(std::istream& is): cp(0) { read(is); }
    Student_info(const Student_info&);
    Student_info& operator=(const Student_info&);
    ~Student_info() { delete cp; }

    // operations
    std::istream& read(std::istream&);

    std::string name() const {
        if (cp) return cp->name();
        else throw std::runtime_error("uninitialized Student");
    }

    double grade() const {
        if (cp) return cp->grade();
        else throw std::runtime_error("uninitialized Student");
    }

    static bool compare(const Student_info& s1,
                        const Student_info& s2) {
        return s1.name() < s2.name();
    }
private:
    Core* cp;
};

string Core::name() const { return n; }

double Core::grade() const
{
    return ::grade(midterm, final, homework);
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
    return min(Core::grade(), thesis);
}

istream& Student_info::read(istream& is)
{
    delete cp;          // delete previous object, if any

    char ch;
    is >> ch;           // get record type

    if (ch == 'U') {
        cp = new Core(is);
    } else {
        cp = new Grad(is);
    }

    return is;
}

Student_info::Student_info(const Student_info& s): cp(0)
{
    if (s.cp) {
        cp = s.cp->clone();
    }
}

Student_info& Student_info::operator=(const Student_info& s)
{
    if (&s != this) {
        delete cp;
        if (s.cp) {
            cp = s.cp->clone();
        } else {
            cp = 0;
        }
    }
    return *this;
}

template <class T> class Ptr {
public:
    void make_unique() {
        if (*refptr != 1) {
            --*refptr;
            refptr = new size_t(1);
            p = p? clone(p): 0;
        }
    }

    // the rest of the class looks like `Ref_handle' except for its name
    Ptr(): p(0), refptr(new size_t(1)) { }
    Ptr(T* t): p(t), refptr(new size_t(1)) { }
    Ptr(const Ptr& h): p(h.p), refptr(h.refptr) { ++*refptr; }

    Ptr& operator=(const Ptr&);
    ~Ptr();
    operator bool() const { return p; }
    T& operator*() const;
    T* operator->() const;

private:
    T* p;
    std::size_t* refptr;
};

template <class T> T* clone(const T* tp)
{
    return tp->clone();
}

template<class T>
T& Ptr<T>::operator*() const { if (p) return *p; throw std::runtime_error("unbound Ptr"); }

template<class T>
T* Ptr<T>::operator->() const { if (p) return p; throw std::runtime_error("unbound Ptr"); }

template<class T>
Ptr<T>& Ptr<T>::operator=(const Ptr& rhs)
{
        ++*rhs.refptr;
        if (--*refptr == 0) {
                delete refptr;
                delete p;
        }

        refptr = rhs.refptr;
        p = rhs.p;
        return *this;
}

template<class T> Ptr<T>::~Ptr()
{
        if (--*refptr == 0) {
                delete refptr;
                delete p;
        }
}

bool compare(const Core& c1, const Core& c2)
{
    return c1.name() < c2.name();
}

bool compare_Core_ptrs(const Core* cp1, const Core* cp2)
{
    return compare(*cp1, *cp2);
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
        throw domain_error("median of an empty Vec");
    }

    sort(vec.begin(), vec.end());
    vec_sz mid = size / 2;

    return size % 2 == 0 ? (vec[mid] + vec[mid-1]) / 2 : vec[mid];
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

int main(void)
{
    Student_info record;
    record.read(cin);
    cout << record.name() << " ";

    try {
        double final_grade = record.grade();
        streamsize prec = cout.precision();
        cout << setprecision(3) << final_grade << setprecision(prec) << endl;
    } catch (domain_error &e) {
        cout << e.what() << endl;
    }

    return 0;
}

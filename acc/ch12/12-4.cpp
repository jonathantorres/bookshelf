#include <iostream>
#include <memory>
#include <string>
#include <ios>
#include <exception>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <algorithm>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::streamsize;
using std::max;
using std::sort;
using std::setprecision;
using std::domain_error;
using std::istream;
using std::ostream;

template <class T>
class Vec {
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    Vec() { create(); }
    explicit Vec(size_type n, const T& t = T()) { create(n, t); }
    Vec(const Vec& v) { create(v.begin(), v.end()); }
    Vec& operator=(const Vec&);
    ~Vec() { uncreate(); }
    T& operator[](size_type i) { return data[i]; }
    const T& operator[](size_type i) const { return data[i]; }
    void push_back(const T& t) {
        if (avail == limit) {
            grow();
        }
        unchecked_append(t);
    }
    void clear() { uncreate(); }
    bool empty() const { return data == avail; }
    size_type size() const { return avail - data; }
    iterator begin() { return data; }
    const_iterator begin() const { return data; }
    iterator end() { return avail; }
    const_iterator end() const { return avail; }
private:
    iterator data;
    iterator avail;
    iterator limit;
    std::allocator<T> alloc; // object to handle memory allocation

    // allocate and initialize the underlying array
    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    // destroy the elements in the array and free the memory
    void uncreate();

    // support functions for push_back
    void grow();
    void unchecked_append(const T&);
};

template <class T> void Vec<T>::create()
{
    data = avail = limit = 0;
}

template <class T> void Vec<T>::create(size_type n, const T& val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    std::uninitialized_fill(data, limit, val);
}

template <class T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j - i);
    limit = avail = std::uninitialized_copy(i, j, data);
}

template <class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
    // check for self-assignment
    if (&rhs != this) {
        // free the array in the left-hand side
        uncreate();

        // copy elements from the right-hand to the left-hand side
        create(rhs.begin(), rhs.end());
    }

    return *this;
}

template <class T>
void Vec<T>::uncreate()
{
    if (data) {
        // destroy (in reverse order) the elements that were constructed
        iterator it = avail;
        while (it != data) {
            alloc.destroy(--it);
        }

        // return all the space that was allocated
        alloc.deallocate(data, limit - data);
    }

    // reset pointers to indicate that the Vec is empty again
    data = limit = avail = 0;
}

template <class T> void Vec<T>::grow()
{
    // when growing, allocate twice as much space as currently in use
    size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));

    // allocate new space and copy existing elements to the new space
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    // return the old space
    uncreate();

    // reset pointers to point to the newly allocated space
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

// assumes avail points at allocated, but uninitialized space
template <class T> void Vec<T>::unchecked_append(const T& val)
{
    alloc.construct(avail++, val);
}

class Str {
    friend istream& operator>>(istream& is, Str& s);
    public:
        typedef Vec<char>::size_type size_type;

        // default constructor; create an empty Str
        Str() { }

        // create a Str containing n copies of c
        Str(size_type n, char c): data(n, c) { }

        // create a Str from a null-terminated array of char
        Str(const char* cp) {
            std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
        }

        // create a Str from the range denoted by iterators b and e
        template<class In>
        Str(In b, In e) {
            std::copy(b, e, std::back_inserter(data));
        }

        Str& operator+=(const Str& s) {
            std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
            return *this;
        }

        size_type size() const { return data.size(); }
        char& operator[](size_type i) { return data[i]; }
        const char& operator[](size_type i) const { return data[i]; }
    private:
        Vec<char> data;
};

Str operator+(const Str& s, const Str& t) {
    Str r = s;
    r += t;
    return r;
}

istream& operator>>(istream& is, Str& s)
{
    // obliterate existing value(s)
    s.data.clear();

    // read and discard leading whitespace
    char c;
    while (is.get(c) && std::isspace(c)) {
        // nothing to do, just get rid of the whitespace
    }

    // if still something to read, do so until next whitespace character
    if (is) {
        do {
            s.data.push_back(c); // compile error!, data is private
        } while (is.get(c) && !std::isspace(c));

        // if we read whitespace, then put it back on the stream
        if (is) {
            is.unget();
        }
    }
    return is;
}

ostream& operator<<(ostream& os, const Str& s)
{
    for (Str::size_type i = 0; i != s.size(); ++i) {
        os << s[i];
    }
    return os;
}

int main(void)
{
    Str s = "Hello, world";
    std::cout << s << std::endl;
    return 0;
}

#include <iostream>
#include <map>
#include <string>

using std::string;
using std::map;
using std::cout;
using std::cin;
using std::endl;

int main(void)
{
    string s;
    map<string, int> counters; // store each word and an associated counter

    // read the input, keeping track of each word and how often we see it
    while (cin >> s) {
        ++counters[s];
    }

    // write the words and associated counts
    while (!counters.empty()) {
        int max = counters.begin()->second;
        string w;

        for (map<string, int>::const_iterator it = counters.begin(); it != counters.end(); ++it) {
            if (it->second >= max) {
                max = it->second;
                w = it->first;
            }
        }

        counters.erase(w);
        cout << w << ": " << max << endl;
    }

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>

std::vector<std::string> get_words(std::istream &s);
std::vector<std::string>::size_type num_of_words(std::vector<std::string> words);
std::map<std::string, int> word_count(std::vector<std::string> words);

int main(void)
{
    std::cout << "Enter the words: ";
    std::vector<std::string> words = get_words(std::cin);

    if (words.size() == 0) {
        std::cout << std::endl << "No words were entered" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::vector<std::string>::size_type n = num_of_words(words);
    std::cout << "There are a total of " << n << " words." << std::endl;

    std::map<std::string, int> wc = word_count(words);
    for (const auto &n: wc) {
        std::cout << n.second << ": " << n.first << std::endl;
    }
    return 0;
}

std::vector<std::string> get_words(std::istream &s)
{
    std::vector<std::string> words;
    if (!s) {
        return words;
    }

    std::string word;
    while (s >> word) {
        words.push_back(word);
    }

    return words;
}

std::vector<std::string>::size_type num_of_words(std::vector<std::string> words)
{
    return words.size();
}

std::map<std::string, int> word_count(std::vector<std::string> words)
{
    std::map<std::string, int> m;

    for (std::vector<std::string>::size_type i = 0; i < words.size(); i++) {
        m[words[i]]++;
    }

    return m;
}

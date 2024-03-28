#ifndef __SORT_WORDS__
#define __SORT_WORDS__

#include <unordered_map>
#include <string>
#include <set>
#include <mutex>

class SortWords
{
public:
    SortWords(std::string f1, std::string f2, std::string f3);
    ~SortWords();

    void ThreadHandler(std::string f);
    void Print(std::string f);

private:
    std::set<std::string> m_words;
    std::unordered_map<std::string, size_t> m_occuarency;
    std::unordered_map<std::string, char> m_split;
    size_t max_num;
    std::string max_word;
    bool is_descending;
    std::mutex m_mutex;
};


#endif //__SORT_WORDS__



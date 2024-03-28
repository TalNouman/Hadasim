#include <thread>
#include <fstream>
#include <iostream>
#include <iterator>

#include "sort_words.hpp"

SortWords::SortWords(std::string f1, std::string f2, std::string f3) :
                            m_words(), m_occuarency(), m_split(),
                            max_num(0), max_word(""), is_descending(false)
{
    m_split["-s"] = ' ';
    m_split["-c"] = ',';
    m_split["-n"] = '\n';

    std::string sort;
    std::cout << "Enter your options:" << std::endl;
    std::cout << "sort[-a, -d]: ";
    std::cin >> sort;

    if(sort == "-d")
    {
        is_descending = true;
    }

    size_t num_threads = 3;
    std::thread readers[num_threads];

    readers[0] = std::thread(&SortWords::ThreadHandler, std::ref(*this), f1);
    readers[1] = std::thread(&SortWords::ThreadHandler, std::ref(*this), f2);
    readers[2] = std::thread(&SortWords::ThreadHandler, std::ref(*this), f3);


    for(size_t i = 0; i < num_threads; ++i)
    {
        readers[i].join();
    }
}

/* ----------------------------------------- */

void SortWords::ThreadHandler(std::string f)
{
    std::ifstream t_file(f);
    
    if(!t_file.is_open())
    {
        std::cout << "No such file" << std::endl;
        return;
    }

    std::string line;
    while(getline(t_file, line))
    {       
        std::string word = "";

        for(std::string::iterator runner = line.begin(); 
            runner != line.end(); ++runner)
        {
            *runner = tolower(*runner);

            if(*runner >= 'a' && *runner <= 'z') // find word
            {
                word.push_back(*runner);
            }
            else                                
            {
                m_mutex.lock();
                m_words.insert(word);

                if(m_occuarency.find(word) != m_occuarency.end())
                {
                    ++m_occuarency[word];
                }
                else
                {
                    m_occuarency[word] = 1;
                }

                if(m_occuarency[word] > max_num)
                {
                    max_num = m_occuarency[word];
                    max_word.clear();
                    max_word = word;
                }

                m_mutex.unlock();
                word.clear();
            }
        }
    }

    t_file.close();
}

/* ----------------------------------------- */

void SortWords::Print(std::string f)
{

    std::string split;
    std::cout << "split[-s, -c, -n]: ";
    std::cin >> split;
    
    std::ofstream res_file(f);
    if(!res_file.is_open())
    {
        std::cout << "No such file" << std::endl;
        return;
    }


    for(auto p_set = m_words.begin(); p_set != m_words.end(); ++p_set)
    {
        res_file << *p_set;
        if(std::next(p_set) != m_words.end())
        {
            res_file << m_split[split];
        }
    }

    res_file.close();

    std::cout << "The most frequent word in all files is: " << m_words.size() << ", count: " << max_num << std::endl;
}


/* ----------------------------------------- */

SortWords::~SortWords() {}
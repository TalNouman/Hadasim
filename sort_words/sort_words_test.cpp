#include <iostream>

#include "sort_words.hpp"

int main()
{
    SortWords mySort("f1.txt", "f2.txt", "f3.txt");

    mySort.Print("f4.txt");

    return 0;
}
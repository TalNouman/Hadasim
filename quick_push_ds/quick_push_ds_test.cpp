#include <iostream>

#include "quick_push_ds.hpp"

int main()
{
    DLList<int> dll;

    std::cout << "push should: 5 3 8 7 7 9" << std::endl;

    dll.Push(5);
    std::cout << dll.Peek() << std::endl;
    dll.Push(3);
    std::cout << dll.Peek() << std::endl;
    dll.Push(8);
    std::cout << dll.Peek() << std::endl;
    dll.Push(7);
    std::cout << dll.Peek() << std::endl;
    dll.Push(7);
    std::cout << dll.Peek() << std::endl;
    dll.Push(9);
    std::cout << dll.Peek() << std::endl;

    std::cout << '\n' << "size should: 6" << std::endl;
    std::cout << dll.GetSize() << std::endl;

    std::cout << '\n' << "pop should: 9 8 7 7 5" << std::endl;

    std::cout << dll.Pop() << std::endl;
    std::cout << dll.Pop() << std::endl;
    std::cout << dll.Pop() << std::endl;
    std::cout << dll.Pop() << std::endl;
    std::cout << dll.Pop() << std::endl;
    
    std::cout << '\n' << "size should: 1" << std::endl;
    std::cout << dll.GetSize() << std::endl;

    dll.Pop();

    std::cout << '\n' << "size should: 0" << std::endl;
    std::cout << dll.GetSize() << std::endl;

    //dll.Pop();

    return 0;
}
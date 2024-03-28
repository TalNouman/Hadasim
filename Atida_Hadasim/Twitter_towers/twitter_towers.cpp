#include <iostream>
#include <vector>

#include "twitter_towers.hpp"

TwitterTowers::TwitterTowers() : m_height(0.0), m_width(0.0) {}

/* ------------------------- */

TwitterTowers::~TwitterTowers() {}

/* ------------------------- */

void TwitterTowers::TowersChoice()
{
    int choice = 0;

    while(choice != 3)
    {
        std::cout << "Enter your choice: " << '\n' << "1. Rectangular tower"
                << '\n' << "2. Triangle tower" << '\n' << "3. Get out" << std::endl;
        std::cin >> choice;

        switch(choice)
        {
        case 1:
            RectangularTower();
            continue;
        case 2:
            TriangleTower();
            continue;
        case 3:
            break;
        }
    }
}

/* ------------------------- */

void TwitterTowers::RectangularTower()
{
    std::cout << "Enter the tower height" << std::endl;
    std::cin >> m_height;
    std::cout << "Enter the tower width" << std::endl;
    std::cin >> m_width;

    if(m_height == m_width || abs(m_height - m_width) > 5)
    {
        // area printer
        std::cout << "The area of the rectangle is: " << 
            (m_height * m_width) << std::endl; 
    }
    else
    {
        // prints scope
        std::cout << "The scope of the rectangle is: " << 
            ((m_height * 2) + (m_width * 2)) << std::endl;
    }

}

/* ------------------------- */

void TwitterTowers::TriangleTower()
{
    std::cout << "Enter the tower height" << std::endl;
    std::cin >> m_height;
    std::cout << "Enter the tower width" << std::endl;
    std::cin >> m_width;

    int choice = 0;
    std::cout << "Enter your chice: " << '\n' << 
        "1. Calculate and print the scope of the triangle" 
        << '\n' << "2. Print the triangle" << std::endl;
    std:: cin >> choice;

    switch(choice)
    {
    case 1:
        std::cout << "The scope of the triangle is: " << 
            ((m_height + m_width) * 2) << std::endl;
        break;
    case 2:
        if(m_width % 2 == 0 || m_width > (2 * m_height))
        {
            std::cout << "It's impossible to print the triangle" << std::endl;
        }
        else
        {
            PrintTriangle();
        }
        break;
    default:
        break;
    }
}

/* ------------------------- */

void TwitterTowers::PrintTriangle()
{
    std::vector<std::vector<char>> triangle(m_height, std::vector(m_width, ' '));

    int rest = (m_height - 2) % (m_width / 2 - 1);
    int same_lines_num = (m_height - 2) / (m_width / 2 - 1);
    
    // count the len of the asterisks that supposed to be in each line
    int asterisks_len = 1;
    // start and end holds the len of the asterisk's row
    size_t id_start = m_width / 2;
    size_t id_end = id_start + asterisks_len;

    for(size_t row = 0; row < triangle.size(); ++row)
    {
        if(row >= same_lines_num + rest + 1) // make sure to add the rest lines just to the first grup
        {
            rest = 0;
        }

        int repeat_lines_num = same_lines_num + rest;

        if(row == 0 || row == triangle.size() - 1) // first and last row should apper just once
        {
            repeat_lines_num = 1;
        }

        while(repeat_lines_num) //handle the same lines number
        {
            for(size_t col = id_start; col < id_end; ++col) 
            {
                triangle[row][col] = '*';
            }

            ++row;
            --repeat_lines_num;
        }

        // handle the new rows with new numbers
        asterisks_len += 2;
        --id_start;
        id_end = id_start + asterisks_len;
        --row;
    }

    // print the triangle
    for(size_t row = 0; row < triangle.size(); ++row)
    {
        for(size_t col = 0; col < triangle[0].size(); ++col)
        {
            std::cout << triangle[row][col];
        }

        std::cout << '\n';
    }
}


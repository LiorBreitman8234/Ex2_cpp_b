//
// Created by bravo8234 on 20/03/2022.
//

#ifndef EX2_CPP_QA_PAGE_HPP
#define EX2_CPP_QA_PAGE_HPP
#include <iostream>
#include <stdexcept>
#include <map>
#include <unordered_map>
#include <vector>
namespace ariel
{
    class Page
    {
        int id;
        std::map<std::pair< int, int>,char> tiles;

    public:
        explicit Page( int id)
        : tiles(std::map<std::pair< int, int>,char>())
        {
            this->id = id;
        };
        /**
         *
         * @param row the row number(key in our map)
         * @param column column number(index in the vector)
         * @param toWrite the char to write
         */
        void writeToPage( int row, int column, char toWrite);
        /**
         *
         * @param row row number to read from
         * @param column column number to read from
         * @return
         */
        char readFromPage( int row, int column);

        std::map<std::pair<int,int>,char>::iterator getTilesBegin();
        std::map<std::pair<int,int>,char>::iterator getTilesEnd();
    };
}
#endif //EX2_CPP_QA_PAGE_HPP

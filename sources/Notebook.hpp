//
// Created by bravo8234 on 20/03/2022.
//

#ifndef EX2_CPP_QA_NOTEBOOK_HPP
#define EX2_CPP_QA_NOTEBOOK_HPP

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include "Page.hpp"
#include "Direction.hpp"

#define ROW_LENGTH 100
#define CHAR_UP_LIMIT 126
#define CHAR_LOW_LIMIT 32
namespace ariel {
    class Notebook {
        std::map<int, Page> pages;
        std::map<int, Page> &pagesRef;

        static int checkInputWrite(int page, int row, int column, const std::string &toWrite, Direction direction);

        static int checkInputReadAndErase(int page, int row, int column, int length, Direction direction);

    public:
        Notebook()
        : pages(std::map<int, Page>()), pagesRef(pages) {};

        void write(int page, int row, int column, Direction direction, std::string toWrite);

        std::string read(int page, int row, int column, Direction direction, int length);

        void erase(int page, int row, int column, Direction direction, int length);

        void show(int page);
    };

}
#endif //EX2_CPP_QA_NOTEBOOK_HPP

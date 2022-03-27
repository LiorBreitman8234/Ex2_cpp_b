#include <iostream>
#include "sources/Notebook.hpp"
int main() {
    ariel::Notebook notebook;
    std::cout << "welcome to my notebook program!" << std::endl;
    int choice = -1;
    while(choice != 0 && !std::cin.fail())
    {
        std::cout << "Menu :" << std::endl;
        std::cout << "1.write to page "<< std::endl;
        std::cout << "2.read from page "<< std::endl;
        std::cout << "3.erase in page "<< std::endl;
        std::cout << "4.show page "<< std::endl;
        std::cout << "to exit, press 0 "<< std::endl;
        std::cout << "your choice : ";
        std::cin >> choice;
        if(choice == 1)
        {
            int page,row,col;
            std::string toWrite;
            int dir = 0;
            std::cout << "choose page to write in: ";
            std::cin >> page;
            std::cout << "choose row to start writing from: ";
            std::cin >> row;
            std::cout << "choose column to start writing from (column cant be over 100): ";
            std::cin >> col;
            while(dir != 1 && dir != 2)
            {
                std::cout << "choose direction to erase, 1 for horizontal or 2 for vertical: ";
                std::cin >> dir;
            }
            std::cout << "type the string to write into the notebook: ";
            std::cin >> toWrite;
            try {
                dir == 1 ? notebook.write(page,row,col,ariel::Direction::Horizontal,toWrite) :notebook.write(page,row,col,ariel::Direction::Vertical,toWrite);
            }
            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        else if(choice == 2)
        {
            int page,row,col,length;
            int dir = 0;
            std::cout << "choose page to read from: ";
            std::cin >> page;
            std::cout << "choose row to start reading from: ";
            std::cin >> row;
            std::cout << "choose column to start reading from (column cant be over 100): ";
            std::cin >> col;
            while(dir != 1 && dir != 2)
            {
                std::cout << "choose direction to read, 1 for horizontal or 2 for vertical: ";
                std::cin >> dir;
            }
            std::cout << "type the length to read from notebook: ";
            std::cin >> length;
            try {
                if(dir == 1)
                {
                    std::cout << notebook.read(page,row,col,ariel::Direction::Horizontal,length);
                }
                else
                {
                    std::cout << notebook.read(page,row,col,ariel::Direction::Vertical,length);
                }
                std::cout << std::endl;
            }
            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        else if(choice == 3)
        {
            {
                int page,row,col,length;
                int dir = 0;
                std::cout << "choose page to erase from: ";
                std::cin >> page;
                std::cout << "choose row to start erasing from: ";
                std::cin >> row;
                std::cout << "choose column to start erasing from (column cant be over 100): ";
                std::cin >> col;
                while(dir != 1 && dir != 2)
                {
                    std::cout << "choose direction to erase, 1 for horizontal or 2 for vertical: ";
                    std::cin >> dir;
                }
                std::cout << "type the length to erase from notebook: ";
                std::cin >> length;
                try {
                    dir == 1 ? notebook.erase(page,row,col,ariel::Direction::Horizontal,length) : notebook.erase(page,row,col,ariel::Direction::Vertical,length);

                }
                catch (std::exception& e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
        else if(choice == 4)
        {
            int page;
            std::cout << "choose page to show: ";
            std::cin >> page;
            try{
                notebook.show(page);
            }
            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    std::cout << "goodbye! ";
    return 0;
}

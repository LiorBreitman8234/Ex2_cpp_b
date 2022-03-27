//
// Created by bravo8234 on 20/03/2022.
//

#include "Notebook.hpp"
namespace ariel
{
    int Notebook::checkInputWrite(int page,int row,int column,const std::string& toWrite, Direction direction){
        if(row <0 || column <0 || page <0)
        {
            return 1;
        }
        if(column >= ROW_LENGTH || (direction == Direction::Horizontal && (unsigned long) column + toWrite.size() > ROW_LENGTH))
        {
            return 2;
        }
        for(char i : toWrite)
        {
            if(i > CHAR_UP_LIMIT ||i < CHAR_LOW_LIMIT || i == '~')
            {
                return 3;
            }
        }
        return 0;
    }
    int Notebook::checkInputReadAndErase(int page, int row, int column, int length, Direction direction) {
        if(row <0 || column <0 || page <0 || length < 0)
        {
            return 1;
        }
        if(column >= ROW_LENGTH || (direction == Direction::Horizontal && column + length > ROW_LENGTH))
        {
            return 2;
        }
        return 0;
    }
    void Notebook::write( int page, int row, int column, Direction direction, std::string toWrite)
    {
        switch (checkInputWrite(page, row, column, toWrite, direction)) {
            case 1:
                throw std::invalid_argument("page, row and col numbers must be >=0");
            case 2:
                throw std::out_of_range("trying to write to columns over 100");
            case 3:
                throw std::invalid_argument("trying to write illegal char");
            case 0:
                break;
        }
        if(pagesRef.find(page) != pagesRef.end())
        {
            //getting the page to write to
            Page& current = pagesRef.at(page);
            std::string toCheck;
            for( long i =0; i < toWrite.size();i++)
            {
                toCheck.push_back('_');
            }
            //here I use the read function to check if the space we want to write to is empty
            if(toCheck != read(page,row,column,direction,(int)toWrite.size()))
            {
                throw std::invalid_argument("trying to write on an occupied space");
            }
            for(int i =0; i < toWrite.size();i++)
            {
                if(direction == Direction::Vertical)
                {
                    current.writeToPage(row +i, column,toWrite.at((unsigned long) i));
                }
                else
                {
                    current.writeToPage(row,column+i,toWrite.at((unsigned long)i));
                }
            }
        }
        else
        {
            //creating a new page and adding it to our map
            Page toAdd = Page(page);
            // no need to check if the place is clear since this is a new page
            for(int i =0; i < toWrite.length();i++)
            {
                if(direction == Direction::Vertical)
                {
                    toAdd.writeToPage(row +i, column,toWrite.at((unsigned long) i));
                }
                else
                {
                    toAdd.writeToPage(row,column+i,toWrite.at((unsigned long)i));
                }
            }
            pagesRef.insert({page, toAdd});


        }
    }
    void Notebook::show(int page) {
        if(page < 0)
        {
            throw std::invalid_argument("page number cant be negative!");
        }
        auto it = this->pagesRef.find(page);
        if(it == this->pagesRef.end())
        {
            std::cout<< "page " << page << " is empty!" << std::endl;
        }
        else
        {
            std::cout <<"printing page :" << page << std::endl;
            Page& toRead = this->pagesRef.at(page);
            auto start = toRead.getTilesBegin();
            auto end = toRead.getTilesEnd();
            while(start != end)
            {
                int row = start->first.first;
                std::cout << row << ": " << read(page,row,0,Direction::Horizontal,ROW_LENGTH) << std::endl;
                start++;
            }
        }
    }
    std::string Notebook::read( int page, int row, int column, Direction direction, int length) {
        switch (checkInputReadAndErase(page,row,column,length, direction)) {
            case 1:
                throw std::invalid_argument("page, row and col numbers must be >=0");
            case 2:
                throw std::out_of_range("trying to read columns over 100");
            case 0:
                break;
        }
        std::string toRet;
        if(pagesRef.find(page) == pagesRef.end())
        {
            //the page doesn't exist, return default sign
            toRet.resize((unsigned long)length,'_');
            return toRet;
        }
        Page& readFrom = pagesRef.at(page);
        for( int i =0; i < length;i++)
        {
            if(direction == Direction::Vertical)
            {
                toRet.push_back(readFrom.readFromPage(row+i,column));
            }
            else
            {
                toRet.push_back(readFrom.readFromPage(row, column + i));
            }
        }
        return toRet;
    }
    void Notebook::erase( int page,  int row,  int column, Direction direction, int length) {
        switch (checkInputReadAndErase(page,row,column,length, direction)) {
            case 1:
                throw std::invalid_argument("page, row and col numbers must be >=0");
            case 2:
                throw std::out_of_range("trying to erase columns over 100");
            case 0:
                break;
        }
        if(pagesRef.empty() || pagesRef.find(page) == pagesRef.end())
        {
            Page toAdd = Page(page);
            for( int i =0; i < length;i++)
            {
                if(direction == Direction::Vertical)
                {
                    toAdd.writeToPage(row +i, column, '~');
                }
                else
                {
                    toAdd.writeToPage(row, column+i,'~');
                }
            }
            pagesRef.insert({page,toAdd});
        }
        else
        {
            Page& removeFrom = pagesRef.at(page);
            for( int i =0; i < length;i++)
            {
                if(direction == Direction::Vertical)
                {
                    removeFrom.writeToPage(row+i,column,'~');
                }
                else
                {
                    removeFrom.writeToPage(row, column +i, '~');
                }
            }
        }
    }
}



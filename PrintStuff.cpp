#include "PrintStuff.hpp"

#include <iostream>
#include <map>

PrintStuff::PrintStuff(){}

void PrintStuff::printRow(){
    for (int i = 0; i < maxColumns; i++){
        std::cout << "____";
    }
     std::cout << std::endl;
}

void PrintStuff::printInterRow(){
    for (int i = 0; i < maxColumns; i++){
        std::cout << "----";
    }
     std::cout << std::endl;
}

void PrintStuff::printBoxMap(Box box){
    for(const auto &x: box) {
        std::cout<< "Siamo nella riga " << x.first << " che ha come colonne " << x.second.columnOne<< " " << x.second.columnTwo<< " " << x.second.columnThree << std::endl;
    }
}

void PrintStuff::printCoordinates(Coordinates coordinates){
    for(Coordinates::iterator iter = coordinates.begin(); iter != coordinates.end(); ++iter){
        std::cout << "Le coordinate del numero sono " << iter->first << " " << iter->second << std::endl;
    }
}

void PrintStuff::printMultiArray(int multiArr[][maxRows]){
    printRow();
    for (int i = 0; i < maxColumns; i++){
        std::cout << "| ";
        for (int z = 0; z < maxRows; z++){
            std::cout << multiArr[i][z];
            std::cout << " | ";
        }
        std::cout << std::endl;

        if ((i+1)%3 == 0){
            printRow();
        } else{
            printInterRow();
        }        
    }
}

PrintStuff::~PrintStuff(){}
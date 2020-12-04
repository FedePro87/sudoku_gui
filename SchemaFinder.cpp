#include "SchemaFinder.hpp"  

SchemaFinder::SchemaFinder(){}

int SchemaFinder::findColumn(int row, int number){
    std::cout << "Sta cercando in riga " << row << " il numero " << number << std::endl;
    int column = -1;

    for (int i = 0; i < maxColumns; i++){
        if (cells[row][i] == number){
            column = i;
            break;
        }
    }
    
    return column;
}

Coordinates SchemaFinder::findRowColumn(int multiArray[][maxColumns], int number){
    Coordinates rowColumn;

    for (int i = 0; i < maxRows; i++){
        for (int z = 0; z < maxColumns; z++){
            if(multiArray[i][z] == number){
                rowColumn.insert({ i, z });
                return rowColumn;
            }
        }
    }

    rowColumn.insert({ -1, -1 });
    return rowColumn;
}

int SchemaFinder::findMoreOccurances(){
    for (int i = 0; i < maxRows; i++){
        for (int z = 0; z < maxColumns; z++){
            if(cells[i][z] == 0) continue;
            else{occurances[cells[i][z] - 1]++;}
        }
    }

    int moreOccurrances = 0;
    int moreNumberOccurrances = 0;

    for (int i = 0; i < maxNumber; i++){
        if(occurances[i] > moreOccurrances){
                moreOccurrances = occurances[i];
                moreNumberOccurrances = i + 1;
            }
    }

    return moreNumberOccurrances;    
}

int SchemaFinder::findRowOccurances(int row, int number){
    int occurances = 0;

    for (int i = 0; i < maxColumns; i++){
        if(cells[row][i] == number) occurances++;
    }

    return occurances;
}

int SchemaFinder::findColumnOccurances(int column, int number){
    int occurances = 0;

    for (int i = 0; i < maxRows; i++){
        if(cells[i][column] == number) occurances++;
    }

    return occurances;
}

//Trova la colonna dei numeri mancanti in una determinata riga.
std::vector<int> SchemaFinder::findRowColumnsVoids(int row){
    std::vector<int> rowColumnsVoids;

    for (int column = 0; column < maxColumns; column++){
        if(cells[row][column] == 0){
            rowColumnsVoids.push_back(column);
        }
    }

    return rowColumnsVoids;
}

//Trova la riga dei numeri mancanti in una determinata colonna.
std::vector<int> SchemaFinder::findColumnRowsVoids(int column){
    std::vector<int> columnRowsVoids;

    for (int row = 0; row < maxRows; row++){
        if(cells[row][column] == 0){
            columnRowsVoids.push_back(row);
        }
    }

    return columnRowsVoids;
}

std::vector<int> SchemaFinder::findRowMissingNumbers(int row){
    std::vector<int> rowMissingNumbers;

    for (int i = 1; i <= maxNumber; i++){
        if(SchemaFinder::findRowOccurances(row, i) < 1){
            rowMissingNumbers.push_back(i);
        }
    }

    return rowMissingNumbers;
}

std::vector<int> SchemaFinder::findColumnMissingNumbers(int column){
    std::vector<int> columnMissingNumbers;

    for (int i = 1; i <= maxNumber; i++){
        if(SchemaFinder::findColumnOccurances(column, i) < 1){
            columnMissingNumbers.push_back(i);
        }
    }

    return columnMissingNumbers;
}

SchemaFinder::~SchemaFinder(){}
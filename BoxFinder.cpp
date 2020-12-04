#include "BoxFinder.hpp"  

BoxFinder::BoxFinder(){}

int BoxFinder::findCurrentBoxIndex(int row, int column){
    int index = -1;

    //Trova il quadrato a cui appartiene la corrente posizione.
    for (int i = 0; i < maxBoxes; i++){
    //Cerca nell'attuale box l'esistenza della riga.
        if(boxes[i].find(row) != boxes[i].end()){
            //Ora deve trovare se nella struct è presente la colonna.
            BoxColumns findedBoxColumns = boxes[i].find(row)->second;

            //Cerca anche la colonna. Se la trova, ha trovato anche il box.
            if(column == findedBoxColumns.columnOne ||
            column == findedBoxColumns.columnTwo ||
            column == findedBoxColumns.columnThree) index = i;
        }
    //Se non la trova, passa alla prossima.
        else continue;
    }

    return index;
}

//Cerca number in un box. Se lo trova torna coord, altrimenti {-1,-1}.
Coordinates BoxFinder::findInsideBoxCoordinates(Box box, int number){
    for(Box::iterator iter = box.begin(); iter != box.end(); ++iter){
        Coordinates currentBoxCoordinates;
        int currentRow = iter->first;
        BoxColumns currentColumnsCheck = iter->second;

        if (number == cells[currentRow][currentColumnsCheck.columnOne]){
            currentBoxCoordinates.insert({ currentRow, currentColumnsCheck.columnOne });
            return currentBoxCoordinates;
        } else if (number == cells[currentRow][currentColumnsCheck.columnTwo]){
            currentBoxCoordinates.insert({ currentRow, currentColumnsCheck.columnTwo });
            return currentBoxCoordinates;
        } else if (number == cells[currentRow][currentColumnsCheck.columnThree]){
            currentBoxCoordinates.insert({ currentRow, currentColumnsCheck.columnThree });
            return currentBoxCoordinates;
        }
    }

    Coordinates currentBoxCoordinates;
    currentBoxCoordinates.insert({ -1, -1 });
    return currentBoxCoordinates;
}

int BoxFinder::findInsideBoxOccurances(Box box, int number){
    int numberFinded = 0;

    for(Box::iterator iter = box.begin(); iter != box.end(); ++iter){
        if(cells[iter->first][iter->second.columnOne] == number) numberFinded++;
        if(cells[iter->first][iter->second.columnTwo] == number) numberFinded++;
        if(cells[iter->first][iter->second.columnThree] == number) numberFinded++;
    }

    return numberFinded;
}

//Ritorna l'indice del box che non ha il numero. Se trova due box adiacenti senza, ritorna -1. Se tutti e tre lo hanno,
//ritorna -1.
int BoxFinder::findThreeBoxesIndex(int currentBoxIndex, int number, bool goingHorizontal){
    int emptyFounded = 0;
    int emptyIndex = -1;

    for (int i = 0; i < 3; i++){
        Box currentBox = boxes[currentBoxIndex];
        Coordinates currentBoxCoords = findInsideBoxCoordinates(currentBox, number);

        //if (number == 6){
        //    PrintStuff::printCoordinates(currentBoxCoords);
        //    std::cout << "Indice del box in cui cerca " << currentBoxIndex << std::endl;
        //}

        if(currentBoxCoords.begin()->first < 0){
            emptyIndex = currentBoxIndex;
            emptyFounded++;
        }

        if(emptyFounded > 1) emptyIndex = -1;

        if (goingHorizontal) currentBoxIndex = Utils::correctNextBoxIndexHorizontal(currentBoxIndex);
        else currentBoxIndex = Utils::correctNextBoxIndexVertical(currentBoxIndex);
    }

    return emptyIndex;
}

int BoxFinder::findMoreZeroesRow(int boxIndex){
    Box myBox = boxes[boxIndex];
    int rowToSearch = -1;
    int maxZeroFounded = 0;

    for(Box::iterator iter = myBox.begin(); iter != myBox.end(); ++iter){
        int zeroFounded = 0;
        if(cells[iter->first][iter->second.columnOne] == 0) zeroFounded++;
        if(cells[iter->first][iter->second.columnTwo] == 0) zeroFounded++;
        if(cells[iter->first][iter->second.columnThree] == 0) zeroFounded++;

        if(zeroFounded > maxZeroFounded){
            maxZeroFounded = zeroFounded;
            rowToSearch = iter->first;
        }
    }

    return rowToSearch;
}

int BoxFinder::findMoreZeroesColumn(int boxIndex){
    Box myVerticalBox = verticalBoxes[boxIndex];
    int columnToSearch = -1;
    int maxZeroFounded = 0;

    for(Box::iterator iter = myVerticalBox.begin(); iter != myVerticalBox.end(); ++iter){
        int zeroFounded = 0;
        if(cells[iter->second.columnOne][iter->first] == 0) zeroFounded++;
        if(cells[iter->second.columnTwo][iter->first] == 0) zeroFounded++;
        if(cells[iter->second.columnThree][iter->first] == 0) zeroFounded++;

        if(zeroFounded > maxZeroFounded){
            maxZeroFounded = zeroFounded;
            columnToSearch = iter->first;
        }
    }

    return columnToSearch;
}

//Assicurarsi che ci sia un solo zero all'interno del box che NON sia né in quella colonna né
//in quella riga.
int BoxFinder::findOtherZeroes(int boxIndex, int rowToSearch, int columnToSearch){
    Box myBox = boxes[boxIndex];

    int othersZeroes = 0;

    for(Box::iterator iter = myBox.begin(); iter != myBox.end(); ++iter){
        if(iter->first != rowToSearch && columnToSearch != iter->second.columnOne && cells[iter->first][iter->second.columnOne] == 0) othersZeroes++;
        if(iter->first != rowToSearch && columnToSearch != iter->second.columnTwo && cells[iter->first][iter->second.columnTwo] == 0) othersZeroes++;
        if(iter->first != rowToSearch && columnToSearch != iter->second.columnThree && cells[iter->first][iter->second.columnThree] == 0) othersZeroes++;
    }

    return othersZeroes;
}

//Assicurarsi che ci sia un solo zero all'interno del box che NON sia in quella riga.
int BoxFinder::findOtherZeroesRow(int boxIndex, int rowToSearch){
    Box myBox = boxes[boxIndex];

    int othersZeroes = 0;

    for(Box::iterator iter = myBox.begin(); iter != myBox.end(); ++iter){
        if(iter->first != rowToSearch && cells[iter->first][iter->second.columnOne] == 0) othersZeroes++;
        if(iter->first != rowToSearch && cells[iter->first][iter->second.columnTwo] == 0) othersZeroes++;
        if(iter->first != rowToSearch && cells[iter->first][iter->second.columnThree] == 0) othersZeroes++;
    }

    return othersZeroes;
}

int BoxFinder::findOtherZeroesColumn(int boxIndex, int columnToSearch){
    Box myBox = verticalBoxes[boxIndex];

    int othersZeroes = 0;

    for(Box::iterator iter = myBox.begin(); iter != myBox.end(); ++iter){
        if(iter->first != columnToSearch && cells[iter->second.columnOne][iter->first] == 0) othersZeroes++;
        if(iter->first != columnToSearch && cells[iter->second.columnTwo][iter->first] == 0) othersZeroes++;
        if(iter->first != columnToSearch && cells[iter->second.columnThree][iter->first] == 0) othersZeroes++;
    }

    return othersZeroes;
}

std::vector<Coordinates> BoxFinder::findZeroesCoordinates(Box myBox){
    std::vector<Coordinates> zeroesCoordinates;

    for(Box::iterator iter = myBox.begin(); iter != myBox.end(); ++iter){
        if(cells[iter->first][iter->second.columnOne] == 0){
            Coordinates coords;
            coords.insert({ iter->first, iter->second.columnOne });
            zeroesCoordinates.push_back(coords);
        }

        if(cells[iter->first][iter->second.columnTwo] == 0){
            Coordinates coords;
            coords.insert({ iter->first, iter->second.columnTwo });
            zeroesCoordinates.push_back(coords);
        }

        if(cells[iter->first][iter->second.columnThree] == 0){
            Coordinates coords;
            coords.insert({ iter->first, iter->second.columnThree });
            zeroesCoordinates.push_back(coords);
        }
    }

    return zeroesCoordinates;
}

BoxFinder::~BoxFinder(){}
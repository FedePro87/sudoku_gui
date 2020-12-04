#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <algorithm>

#include "SudokuJoints.hpp"
#include "sudoku_attr.cpp"
#include "Utils.cpp"
#include "PrintStuff.cpp"
#include "SchemaFinder.cpp"
#include "BoxFinder.cpp"
#include "SchemaCheck.cpp"
#include "SchemaInsert.cpp"

//Si tratta di un metodo di risoluzione in cui si prendono in considerazione via via tutti i numeri,
//partendo da quello che ha maggiori occorrenze nello schema. Per realizzarlo è però necessario che
//Almeno in 2 box della stessa linea siano presenti i numeri che si stanno cercando. Ogni numero in
//un box diventa come una sorta di corsia "offlimits", lasciando le possibilità d'inserimento nell
//ultimo box ridotte a pochissime caselle.
void SudokuJoints::boxesJoint(int numberToSearch, bool goingHorizontal){
    //Trova coordinate del primo numero con maggiori ricorrenze.
    Coordinates firstMoreOccurancesNumber = SchemaFinder::findRowColumn(cells, numberToSearch);
    //Trova l'indice del box a cui appartiene il numero.
    int currentBoxIndex = BoxFinder::findCurrentBoxIndex(firstMoreOccurancesNumber.begin()->first, firstMoreOccurancesNumber.begin()->second);

    //Ripete il procidemento per ogni row di boxes.
    for (int i = 0; i < 3; i++){
        //Qui deve cercare lo stesso numero nelle prossime due box e ritornare l'index del box senza
        //quel numero.
        int emptyBoxIndex = BoxFinder::findThreeBoxesIndex(currentBoxIndex, numberToSearch, goingHorizontal);

        if(emptyBoxIndex != -1){
            if (SchemaCheck::checkBoxesInsert(numberToSearch, emptyBoxIndex)){
                //Lo può inserire, cercare coordinate in cui può farlo.
                //std::cout << "Può inserire il numero " << numberToSearch << " nel box con index " << emptyBoxIndex << std::endl;
                SchemaInsert::insertBox(numberToSearch, emptyBoxIndex);
            }
        }

        if (goingHorizontal) currentBoxIndex = Utils::correctNextBoxesRowIndexHorizontal(currentBoxIndex);
        else currentBoxIndex = Utils::correctNextBoxesRowIndexVertical(currentBoxIndex);
    }
}

//Controlla ogni box. Il box deve contenere quante più corsie costituite da 0 possibile.
void SudokuJoints::boxLaneJoint(){
    for (int boxIndex = 0; boxIndex < maxBoxes; boxIndex++){
        int rowToSearch = BoxFinder::findMoreZeroesRow(boxIndex);
        int columnToSearch = BoxFinder::findMoreZeroesColumn(boxIndex);

        if (rowToSearch == -1 || columnToSearch == -1){
            continue;
        }

        int othersZeroes = BoxFinder::findOtherZeroes(boxIndex, rowToSearch, columnToSearch);
        
        if(othersZeroes > 1) {
            //std::cout << "Non si può fare con questo box" << std::endl;
            continue;
        }

        SchemaInsert::insertBoxLaneJoint(boxIndex, rowToSearch, columnToSearch);
    }
}

//Controlla ogni box. A differenza della precedente boxLaneJoint, qui deve solo accertarsi che vi sia un solo zero
//al di là di una singola riga o di una singola colonna.
void SudokuJoints::boxSingleLaneJoint(){
    for (int boxIndex = 0; boxIndex < maxBoxes; boxIndex++){
        int rowToSearch = BoxFinder::findMoreZeroesRow(boxIndex);
        int onlyOneZeroRow = BoxFinder::findOtherZeroesRow(boxIndex, rowToSearch);
        
        //Se è uno solo, prova a inserirlo in quell'unico spazio.
        if(onlyOneZeroRow < 2 && rowToSearch != -1){
            SchemaInsert::insertSingleLaneRow(boxIndex, rowToSearch);
        }

        int columnToSearch = BoxFinder::findMoreZeroesColumn(boxIndex);
        int onlyOneZeroColumn = BoxFinder::findOtherZeroesColumn(boxIndex, columnToSearch);

        //Se è uno solo, prova a inserirlo in quell'unico spazio.
        if(onlyOneZeroColumn < 2 && columnToSearch != -1){
            SchemaInsert::insertSingleLaneColumn(boxIndex, columnToSearch);
        }
    }
}

//Prende in considerazione via via ogni Box, effettuando degli incastri soltanto se gli zeri presenti
//in quel box sono massimo 2. Dopodiché basterà che può inserire un singolo numero in X posizione.
void SudokuJoints::twoZeroesBoxJoint(){
    for (int boxIndex = 0; boxIndex < maxBoxes; boxIndex++){
        int zeroes = BoxFinder::findInsideBoxOccurances(boxes[boxIndex], 0);

        if(zeroes <= 2){
            for(Box::iterator iter = boxes[0].begin(); iter != boxes[0].end(); ++iter){
                for (int i = 1; i <= maxNumber; i++){
                    if(cells[iter->first][iter->second.columnOne] == 0){
                        if(SchemaCheck::checkCanInsert(i, iter->first, iter->second.columnOne)){
                            cells[iter->first][iter->second.columnOne] = i;
                        }
                    }

                    if(cells[iter->first][iter->second.columnTwo] == 0){
                        if(SchemaCheck::checkCanInsert(i, iter->first, iter->second.columnTwo)){
                            cells[iter->first][iter->second.columnTwo] = i;
                        }
                    }

                     if(cells[iter->first][iter->second.columnThree] == 0){
                        if(SchemaCheck::checkCanInsert(i, iter->first, iter->second.columnThree)){
                            cells[iter->first][iter->second.columnThree] = i;
                        }
                    }
                }
            }
        }
    }
}

//Prende in considerazione via via ogni Box, effettuando degli incastri soltanto se gli zeri presenti
//in quel box sono massimo 3.
void SudokuJoints::threeZeroesBoxJoint(){
    for (int boxIndex = 0; boxIndex < maxBoxes; boxIndex++){
        int zeroes = BoxFinder::findInsideBoxOccurances(boxes[boxIndex], 0);

        if(zeroes <= 3){
            std::vector<int> voidNumbers;
            std::vector<Coordinates> boxZeroesCoordinates = BoxFinder::findZeroesCoordinates(boxes[boxIndex]);
            
            for (int i = 1; i <= maxNumber; i++){
                if(!SchemaCheck::checkAlreadyBoxByIndex(i, boxIndex)){
                    voidNumbers.push_back(i);
                }
            }

            for (int voidPosition=0; voidPosition < voidNumbers.size(); voidPosition++){
                for (int i = 0; i < voidNumbers.size(); i++){
                    int numberToProve = voidNumbers.at(i);
                    Coordinates voidCoordinates = boxZeroesCoordinates.at(voidPosition);
                
                    int next = i + 1;
                    if(next >= voidNumbers.size()) next = 0;
                    int secondNumberToProve = voidNumbers.at(next);

                    next = next + 1;
                    if(next >= voidNumbers.size()) next = 0;
                    int thirdNumberToProve = voidNumbers.at(next);

                    if (
                        (SchemaCheck::checkAlreadyColumn(secondNumberToProve, voidCoordinates.begin()->second)
                        && SchemaCheck::checkAlreadyColumn(thirdNumberToProve, voidCoordinates.begin()->second)) ||
                        (SchemaCheck::checkAlreadyRow(secondNumberToProve, voidCoordinates.begin()->first)
                        && SchemaCheck::checkAlreadyRow(thirdNumberToProve, voidCoordinates.begin()->first)) ||
                        (SchemaCheck::checkAlreadyColumn(secondNumberToProve, voidCoordinates.begin()->second)
                        && SchemaCheck::checkAlreadyRow(thirdNumberToProve, voidCoordinates.begin()->first)) ||
                        (SchemaCheck::checkAlreadyRow(secondNumberToProve, voidCoordinates.begin()->first)
                        && SchemaCheck::checkAlreadyColumn(thirdNumberToProve, voidCoordinates.begin()->second))
                    ){
                        cells[voidCoordinates.begin()->first][voidCoordinates.begin()->second] = numberToProve;
                        break;
                    }
                }
            }
        }
    }
}

void SudokuJoints::insertRowTries(int row, int rowZeroes, int insertedNumbers, int tries){
    tries++;
    std::vector<int> voidColumns = SchemaFinder::findRowColumnsVoids(row);
    std::vector<int> missingNumbers = SchemaFinder::findRowMissingNumbers(row);

    //Per ogni numero mancante deve controllare che ci siano tutte le condizioni per inserirne uno.
    //Itera dunque su tutte le colonne vuote.
    for (int voidColumn = 0; voidColumn < voidColumns.size(); voidColumn++){
        //In quella colonna sono presenti tutti i numeri mancanti tranne uno? Lo inserisce.
        int missingNumber = SchemaCheck::allExceptOneColumn(missingNumbers, voidColumns.at(voidColumn));
        if(missingNumber != -1){
            cells[row][voidColumns.at(voidColumn)] = missingNumber;
            //Break. Se è all'ultimo index e non ha ancora aggiunto tutti i numeri mancanti, continua a
            //cercare.
            insertedNumbers++;
            break;
        }
    }

    if(insertedNumbers > 0 && insertedNumbers < rowZeroes && tries <= rowZeroes){
        insertRowTries(row,rowZeroes, insertedNumbers, tries);
    }
}

//La logica di questi incroci deve prendere in considerazione i numeri che mancano in una determinata riga.
void SudokuJoints::rowsJoint(){
    for (int row = 0; row < maxRows; row++){
        int rowZeroes = SchemaFinder::findRowOccurances(row, 0);

        if(rowZeroes <= 4){
            insertRowTries(row, rowZeroes, 0, 1);
        }
    }
}

void SudokuJoints::insertColumnTries(int column, int rowZeroes, int insertedNumbers, int tries){
    tries++;
    std::vector<int> voidRows = SchemaFinder::findColumnRowsVoids(column);
    std::vector<int> missingNumbers = SchemaFinder::findColumnMissingNumbers(column);

    //Per ogni numero mancante deve controllare che ci siano tutte le condizioni per inserirne uno.
    //Itera dunque su tutte le righe vuote.
    for (int voidRow = 0; voidRow < voidRows.size(); voidRow++){
        int missingNumber = SchemaCheck::allExceptOneRow(missingNumbers, voidRows.at(voidRow));
        if(missingNumber != -1){
            cells[voidRows.at(voidRow)][column] = missingNumber;
            //Break. Se è all'ultimo index e non ha ancora aggiunto tutti i numeri mancanti, continua a
            //cercare.
            insertedNumbers++;
            break;
        }
    }

    if(insertedNumbers > 0 && insertedNumbers < rowZeroes && tries <= rowZeroes){
        insertColumnTries(column,rowZeroes, insertedNumbers, tries);
    }
}

void SudokuJoints::columnsJoint(){
    for (int column = 0; column < maxColumns; column++){
        int rowZeroes = SchemaFinder::findColumnOccurances(column, 0);

        if(rowZeroes <= 4){
            insertColumnTries(column, rowZeroes, 0, 1);
        }
    }
}

void SudokuJoints::solve(){
    int numberToSearch = SchemaFinder::findMoreOccurances();

    while (!Utils::checkVictory()){
        for (int i = 0; i < maxNumber; i++){
            if(numberToSearch >= maxNumber) numberToSearch = 0;
            SudokuJoints::boxesJoint(numberToSearch, true);
            SudokuJoints::boxesJoint(numberToSearch, false);
            numberToSearch++;
        }

        SudokuJoints::boxLaneJoint();

        SudokuJoints::boxSingleLaneJoint();

        SudokuJoints::twoZeroesBoxJoint();

        SudokuJoints::threeZeroesBoxJoint();

        SudokuJoints::rowsJoint();

        SudokuJoints::columnsJoint();
    }

    //PrintStuff::printMultiArray(cells);

    //return 0;
}

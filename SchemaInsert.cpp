#include "SchemaInsert.hpp"  

SchemaInsert::SchemaInsert(){}

void SchemaInsert::insertBox(int number, int index){
    Box insertBox = boxes[index];

    for(Box::iterator iter = insertBox.begin(); iter != insertBox.end(); ++iter){
        if(SchemaCheck::checkAlreadyRow(number, iter->first)) continue;

        if (!SchemaCheck::checkAlreadyColumn(number, iter->second.columnOne) && cells[iter->first][iter->second.columnOne] == 0){
            cells[iter->first][iter->second.columnOne] = number;
            break;
        }

        if (!SchemaCheck::checkAlreadyColumn(number, iter->second.columnTwo) && cells[iter->first][iter->second.columnTwo] == 0){
            cells[iter->first][iter->second.columnTwo] = number;
            break;
        }

        if (!SchemaCheck::checkAlreadyColumn(number, iter->second.columnThree) && cells[iter->first][iter->second.columnThree] == 0){
            cells[iter->first][iter->second.columnThree] = number;
            break;
        }
    }
}

//Cercare i numeri che stanno su quella riga ma non in quel box. Quindi per ogni numero
//della riga cerca nel box (solo se il numero è diverso da 0). Controlla quindi che il
//numero sia presente anche nella colonna. Già sappiamo per via della funzione precedente che
//di spazi vuoti ce n'è uno solo, quindi inseriamo il numero nel primo che capita.
void SchemaInsert::insertBoxLaneJoint(int index, int rowToSearch, int columnToSearch){
    Box insertBox = boxes[index];

    for (int i = 0; i < maxColumns; i++){
        int possibleNumber = cells[rowToSearch][i];
        if(possibleNumber != 0){
            if(!SchemaCheck::checkAlreadyBox(possibleNumber,rowToSearch,columnToSearch)){
                if(SchemaCheck::checkAlreadyColumn(possibleNumber, columnToSearch)){
                    for(Box::iterator iter = insertBox.begin(); iter != insertBox.end(); ++iter){
                        if (iter->first != rowToSearch){
                            if(columnToSearch != iter->second.columnOne && cells[iter->first][iter->second.columnOne] == 0) cells[iter->first][iter->second.columnOne] = possibleNumber;
                            if(columnToSearch != iter->second.columnTwo && cells[iter->first][iter->second.columnTwo] == 0) cells[iter->first][iter->second.columnTwo] = possibleNumber;
                            if(columnToSearch != iter->second.columnThree && cells[iter->first][iter->second.columnThree] == 0) cells[iter->first][iter->second.columnThree] = possibleNumber;
                        } else{
                            continue;
                        }
                    }
                }
            }
        }
    }
}

void SchemaInsert::insertSingleLaneRow(int boxIndex, int rowToSearch){
    for (int i = 0; i < maxColumns; i++){
        int possibleNumber = cells[rowToSearch][i];
        if(possibleNumber != 0){
            if(!SchemaCheck::checkAlreadyBoxByIndex(possibleNumber,boxIndex)){
                for(Box::iterator iter = boxes[boxIndex].begin(); iter != boxes[boxIndex].end(); ++iter){
                    if (iter->first != rowToSearch){
                        if (cells[iter->first][iter->second.columnOne] == 0){
                            cells[iter->first][iter->second.columnOne] = possibleNumber;
                            break;
                        }

                        if (cells[iter->first][iter->second.columnTwo] == 0){
                            cells[iter->first][iter->second.columnTwo] = possibleNumber;
                            break;
                        }

                        if (cells[iter->first][iter->second.columnThree] == 0){
                            cells[iter->first][iter->second.columnThree] = possibleNumber;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void SchemaInsert::insertSingleLaneColumn(int boxIndex, int columnToSearch){
    for (int i = 0; i < maxRows; i++){
        int possibleNumber = cells[i][columnToSearch];
        if(possibleNumber!=0){
            if(!SchemaCheck::checkAlreadyBoxByIndex(possibleNumber,boxIndex)){
                for(Box::iterator iter = verticalBoxes[boxIndex].begin(); iter != verticalBoxes[boxIndex].end(); ++iter){                    
                    if(iter->first == columnToSearch) continue;
                    if(cells[iter->second.columnOne][iter->first] == 0){
                        cells[iter->second.columnOne][iter->first] = possibleNumber;
                        break;
                    }

                    if(cells[iter->second.columnTwo][iter->first] == 0){
                        cells[iter->second.columnTwo][iter->first] = possibleNumber;
                        break;
                    }

                    if(cells[iter->second.columnThree][iter->first] == 0){
                        cells[iter->second.columnThree][iter->first] = possibleNumber;
                        break;
                    }
                }
            }
        }
    }
    
}

SchemaInsert::~SchemaInsert(){}
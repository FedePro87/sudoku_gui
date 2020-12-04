#include "SchemaCheck.hpp"  

SchemaCheck::SchemaCheck(){}

//Si occupa di vedere se sulla stessa riga già esiste il numero number
bool SchemaCheck::checkAlreadyRow(int number, int row){
    for (int i = 0; i < maxColumns; i++){
        if(cells[row][i] == number){
            return true;
        }
    }

    return false;
}

//Si occupa di vedere se sulla stessa colonna già esiste il numero number
bool SchemaCheck::checkAlreadyColumn(int number, int column){
    for (int i = 0; i < maxRows; i++){
        if(cells[i][column] == number){
            return true;
        }
    }

    return false;
}

bool SchemaCheck::checkAlreadyBox(int number, int row, int column){
    int currentBoxIndex = BoxFinder::findCurrentBoxIndex(row, column);
    Box currentBox = boxes[currentBoxIndex];
        
    for(Box::iterator iter = currentBox.begin(); iter != currentBox.end(); ++iter){
        //Itera sulle struct boxColumns. Cercare per ogni struct se il valore è uguale a number.
        int currentRow = iter->first;
        BoxColumns currentColumnsCheck =  iter->second;

        //Se una sola delle colonne contiene già il numero, è già nel quadrato.
        if (number == cells[currentRow][currentColumnsCheck.columnOne] ||
        number == cells[currentRow][currentColumnsCheck.columnTwo] ||
        number == cells[currentRow][currentColumnsCheck.columnThree]){
            return true;
        }
    }

    return false;
}

bool SchemaCheck::checkAlreadyBoxByIndex(int number, int boxIndex){
    Box myBox = boxes[boxIndex];
    bool alreadyBox = false;

    for(Box::iterator iter = myBox.begin(); iter != myBox.end(); ++iter){
        if(cells[iter->first][iter->second.columnOne] == number || cells[iter->first][iter->second.columnTwo] == number || cells[iter->first][iter->second.columnThree] == number) alreadyBox = true;
    }

    return alreadyBox;
}

bool SchemaCheck::checkBoxesInsert(int number, int boxIndex){
    bool canInsertBox = false;
    int cantPositionPlaces = 0;
    Box emptyBox = boxes[boxIndex];

    for(Box::iterator iter = emptyBox.begin(); iter != emptyBox.end(); ++iter){
        //è già nel quadrato.
        if(SchemaCheck::checkAlreadyBox(number, iter->first, iter->second.columnOne)){
            break;
        }

        //è già nella riga, passa alla prossima.
        if(SchemaCheck::checkAlreadyRow(number, iter->first)){
            //std::cout << "Il numero " << number << " è già nella riga " <<  iter->first << " del box con indice " << boxIndex << " .Passa alla prossima riga." << std::endl;
            cantPositionPlaces += 3;
            continue;
        }

        //Se non è nella riga, dovrebbe cercare tutte e tre le posizioni della colonna. Con la complicazione che
        //deve considerarle tutte e tre in quanto se almeno in un caso ci sono tutte le condizioni per inserirlo, lo
        //inserisce. Tradotto, deve vedere se c'è già un numero, quindi segnarsi il fatto che lì non lo può mettere.
        if (SchemaCheck::checkAlreadyColumn(number, iter->second.columnOne)){
            //std::cout << "Già presente il numero " << number << " nella colonna " << iter->second.columnOne << " mentre cerca nel box index " << boxIndex << " .Cerca prossima colonna." << std::endl;
            cantPositionPlaces++;
        } else {
            if(cells[iter->first][iter->second.columnOne] != 0) {
                //std::cout << "Già presente il numero " << cells[iter->first][iter->second.columnOne] << " nella posizione " << iter->first << " " <<iter->second.columnOne << " mentre cerca nel box index " << boxIndex << " .Cerca prossima colonna." << std::endl;
                cantPositionPlaces++;
            }
        }

        if (SchemaCheck::checkAlreadyColumn(number, iter->second.columnTwo)){
            //std::cout << "Già presente il numero " << number << " nella colonna " << iter->second.columnTwo << " mentre cerca nel box index " << boxIndex << " .Cerca prossima colonna." << std::endl;
            cantPositionPlaces++;
        } else {
            if(cells[iter->first][iter->second.columnTwo] != 0) {
                //std::cout << "Già presente il numero " << cells[iter->first][iter->second.columnTwo] << " nella posizione " << iter->first << " " << iter->second.columnTwo << " mentre cerca nel box index " << boxIndex << " .Cerca prossima colonna." << std::endl;
                cantPositionPlaces++;
            }
        }

        if (SchemaCheck::checkAlreadyColumn(number, iter->second.columnThree)){
            //std::cout << "Già presente il numero " << number << " nella colonna " << iter->second.columnThree << " mentre cerca nel box index " << boxIndex << " .Cerca prossima colonna." << std::endl;
            cantPositionPlaces++;
        } else {
            if(cells[iter->first][iter->second.columnThree] != 0) {
                //std::cout << "Già presente il numero " << cells[iter->first][iter->second.columnThree] << " nella posizione " << iter->first << " " << iter->second.columnThree << " mentre cerca nel box index " << boxIndex << " .Cerca prossima colonna." << std::endl;
                cantPositionPlaces++;
            }
        }
    }

    if(cantPositionPlaces >= 8) {
        canInsertBox = true;
    }

    return canInsertBox;
}

bool SchemaCheck::checkCanInsert(int number, int row, int column){
    if(checkAlreadyRow(number, row)){return false;}
    
    if(checkAlreadyColumn(number, column)){return false;}

    if(checkAlreadyBox(number, row, column)){return false;}

    return true;
}

//Dato un vettore di numeri mancanti, checka se nella colonna siano presenti tutti i numeri tranne 1 e
//ritorna tale numero, altrimenti -1.
int SchemaCheck::allExceptOneColumn(std::vector<int> missingNumbers, int column){
    //Il numero di volte in cui deve trovare gli altri numeri deve essere di 1 inferiore alla grandezza
    //del vettore.
    int checker = missingNumbers.size() - 1;
    int timesNumberFinded = 0;
    int exceptNumber = -1;

    for (int missingNumber = 0; missingNumber < missingNumbers.size(); missingNumber++){
        if(SchemaCheck::checkAlreadyColumn(missingNumbers.at(missingNumber),column)) timesNumberFinded++;
        else exceptNumber = missingNumbers.at(missingNumber);
    }

    //Deve aver trovato tutti i numeri mancanti tranne 1. Se non è così, ritorna -1.
    if(timesNumberFinded != checker){
        exceptNumber = -1;
    }

    return exceptNumber;    
}

//Dato un vettore di numeri mancanti, checka se nella riga siano presenti tutti i numeri tranne 1 e
//ritorna tale numero, altrimenti -1.
int SchemaCheck::allExceptOneRow(std::vector<int> missingNumbers, int row){
    //Il numero di volte in cui deve trovare gli altri numeri deve essere di 1 inferiore alla grandezza
    //del vettore.
    int checker = missingNumbers.size() - 1;
    int timesNumberFinded = 0;
    int exceptNumber = -1;

    for (int missingNumber = 0; missingNumber < missingNumbers.size(); missingNumber++){
        if(SchemaCheck::checkAlreadyRow(missingNumbers.at(missingNumber),row)) timesNumberFinded++;
        else exceptNumber = missingNumbers.at(missingNumber);
    }

    //Deve aver trovato tutti i numeri mancanti tranne 1. Se non è così, ritorna -1.
    if(timesNumberFinded != checker){
        exceptNumber = -1;
    }

    return exceptNumber;    
}

SchemaCheck::~SchemaCheck(){}
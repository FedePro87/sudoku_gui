#include "Utils.hpp"  

Utils::Utils(){}

//Trova il box adiacente a quello attuale. Se l'indice è compreso tra 0 e 2 non deve essere maggiore di 2 e se lo è
//diventa 0, se è compreso tra 3 e 5 non deve essere maggiore di 5 e se lo è diventa 3, se è compreso tra 6 e 8 non
//deve essere maggiore di 8 e se lo è diventa 6.
int Utils::correctNextBoxIndexHorizontal(int index){
    int nextBoxIndex;

    if (index >= 0 && index <= 2){
        if(index + 1 > 2) nextBoxIndex = 0;
        else nextBoxIndex = index +1;
    } else if (index >= 3 && index <= 5){
        if(index + 1 > 5) nextBoxIndex = 3;
        else nextBoxIndex = index + 1;
    } else if (index >= 6 && index <= 8){
        if(index + 1 > 8) nextBoxIndex = 6;
        else nextBoxIndex = index + 1;
    } else nextBoxIndex = index + 1;
    
    return nextBoxIndex;
}

//Deve passare da 0 a 3 a 6, da 1 a 4 a 7, da 2 a 5 a 8. 
int Utils::correctNextBoxIndexVertical(int index){
    int nextBoxIndex;

    if(index == 6){
        nextBoxIndex = 0;
    } else if(index == 7){
        nextBoxIndex = 1;
    } else if(index == 8){
        nextBoxIndex = 2;
    } else {
        nextBoxIndex = index + 3;
    }

    return nextBoxIndex;
}

int Utils::correctNextBoxesRowIndexHorizontal(int currentIndex){
    int nextBoxIndexIndex;

    if (currentIndex >= 0 && currentIndex <= 2) nextBoxIndexIndex = 3;
    else if (currentIndex >= 3 && currentIndex <= 5) nextBoxIndexIndex = 6;
    else nextBoxIndexIndex = 0;

    return nextBoxIndexIndex;
}

//Se sta tra 0 3 e 6 va a 1, se tra 1 4 e 7 va a 2, se 2 5 e 8 va a 0
int Utils::correctNextBoxesRowIndexVertical(int currentIndex){
    int nextBoxIndexIndex;
    
    if(currentIndex == 0 || currentIndex == 3 || currentIndex == 6){
        nextBoxIndexIndex = 1;
    } else if(currentIndex == 1 || currentIndex == 4 || currentIndex == 7){
        nextBoxIndexIndex = 2;
    } else {
        nextBoxIndexIndex = 0;
    }

    return nextBoxIndexIndex;
}

bool Utils::checkVictory(){
    bool schemaCompleted = true;

    for (int i = 0; i < maxRows; i++){
        for (int z = 0; z < maxColumns; z++){
            if(cells[i][z] == 0){
                schemaCompleted = false;
                break;
            }
        }
    }

    return schemaCompleted;    
}

int Utils::getVectorElementIndex(std::vector<int> myVector, int element){
    int index = -1;
    std::vector<int>::iterator it = std::find(myVector.begin(), myVector.end(), element);
 
    if (it != myVector.end()) {     
        index = it - myVector.begin();
    }

    return index;
}

Utils::~Utils(){}
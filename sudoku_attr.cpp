const int maxColumns = 9, maxRows = 9, maxBoxes = 9, maxNumber = 9;
int cells[maxRows][maxColumns];
int occurances[maxNumber];

struct BoxColumns{
    int columnOne;
    int columnTwo;
    int columnThree;
};

typedef std::map<int, BoxColumns> Box;
typedef std::map<int, int> Coordinates;

//Array che rappresenta i quadrati del sudoku. Hanno come chiave la riga e una struct che rappresenta le tre colonne.
Box boxes[maxBoxes]{
    { {0, {0,1,2}} , {1, {0,1,2}} , {2, {0,1,2}} },
    { {0, {3,4,5}} , {1, {3,4,5}} , {2, {3,4,5}} },
    { {0, {6,7,8}} , {1, {6,7,8}} , {2, {6,7,8}} },
    { {3, {0,1,2}} , {4, {0,1,2}} , {5, {0,1,2}} },
    { {3, {3,4,5}} , {4, {3,4,5}} , {5, {3,4,5}} },
    { {3, {6,7,8}} , {4, {6,7,8}} , {5, {6,7,8}} },
    { {6, {0,1,2}} , {7, {0,1,2}} , {8, {0,1,2}} },
    { {6, {3,4,5}} , {7, {3,4,5}} , {8, {3,4,5}} },
    { {6, {6,7,8}} , {7, {6,7,8}} , {8, {6,7,8}} }
};

Box verticalBoxes[maxBoxes]{
    { {0, {0,1,2}} , {1, {0,1,2}} , {2, {0,1,2}} },
    { {3, {0,1,2}} , {4, {0,1,2}} , {5, {0,1,2}} },
    { {6, {0,1,2}} , {7, {0,1,2}} , {8, {0,1,2}} },
    { {0, {3,4,5}} , {1, {3,4,5}} , {2, {3,4,5}} },
    { {3, {3,4,5}} , {4, {3,4,5}} , {5, {3,4,5}} },
    { {6, {3,4,5}} , {7, {3,4,5}} , {8, {3,4,5}} },
    { {0, {6,7,8}} , {1, {6,7,8}} , {2, {6,7,8}} },
    { {3, {6,7,8}} , {4, {6,7,8}} , {5, {6,7,8}} },
    { {6, {6,7,8}} , {7, {6,7,8}} , {8, {6,7,8}} }
};
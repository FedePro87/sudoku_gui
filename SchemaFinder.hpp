#pragma once

class SchemaFinder  
{
	private:

	public:

		SchemaFinder();

		static int findColumn(int row, int number);

		static Coordinates findRowColumn(int multiArray[][maxColumns], int number);

		static int findMoreOccurances();

		static int findRowOccurances(int row, int number);

		static int findColumnOccurances(int column, int number);

		static std::vector<int> findRowColumnsVoids(int row);
		
		static std::vector<int> findColumnRowsVoids(int column);

		static std::vector<int> findRowMissingNumbers(int row);

		static std::vector<int> findColumnMissingNumbers(int column);

		~SchemaFinder();

};
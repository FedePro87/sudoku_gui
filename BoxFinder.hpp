#pragma once

class BoxFinder  
{
	private:

	public:

		BoxFinder();

		static int findCurrentBoxIndex(int row, int column);

		static Coordinates findInsideBoxCoordinates(Box box, int number);

		static int findInsideBoxOccurances(Box box, int number);

		static int findThreeBoxesIndex(int currentBoxIndex, int number, bool goingHorizontal);

		static int findMoreZeroesRow(int boxIndex);

		static int findMoreZeroesColumn(int boxIndex);

		static int findOtherZeroes(int boxIndex, int rowToSearch, int columnToSearch);

		static int findOtherZeroesRow(int boxIndex, int rowToSearch);

		static int findOtherZeroesColumn(int boxIndex, int columnToSearch);

		static std::vector<Coordinates> findZeroesCoordinates(Box myBox);

		~BoxFinder();

};
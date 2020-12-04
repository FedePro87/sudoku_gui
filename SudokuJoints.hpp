#pragma once

class SudokuJoints  
{
	private:

	public:

		SudokuJoints();

		static void boxesJoint(int numberToSearch, bool goingHorizontal);

        static void boxLaneJoint();

        static void boxSingleLaneJoint();

        static void twoZeroesBoxJoint();

        static void threeZeroesBoxJoint();

        static void insertRowTries(int row, int rowZeroes, int insertedNumbers, int tries);

        static void rowsJoint();

        static void insertColumnTries(int column, int rowZeroes, int insertedNumbers, int tries);

        static void columnsJoint();

        static void solve();

		~SudokuJoints();

};
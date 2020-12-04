#pragma once

class SchemaCheck  
{
	private:

	public:

		SchemaCheck();

		static bool checkAlreadyRow(int number, int row);

		static bool checkAlreadyColumn(int number, int column);

		static bool checkAlreadyBox(int number, int row, int column);

		static bool checkAlreadyBoxByIndex(int number, int boxIndex);

		static bool checkBoxesInsert(int number, int boxIndex);

		static bool checkCanInsert(int number, int row, int column);

		static int allExceptOneColumn(std::vector<int> missingNumbers, int column);

		static int allExceptOneRow(std::vector<int> missingNumbers, int row);

		~SchemaCheck();

};

#pragma once

class SchemaInsert  
{
	private:

	public:

		SchemaInsert();

		static void insertBox(int number, int index);

		static void insertBoxLaneJoint(int index, int rowToSearch, int columnToSearch);

		static void insertSingleLaneRow(int boxIndex, int rowToSearch);

		static void insertSingleLaneColumn(int boxIndex, int columnToSearch);

		~SchemaInsert();

};
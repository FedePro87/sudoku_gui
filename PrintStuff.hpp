#pragma once

class PrintStuff  
{
	private:

	public:

		PrintStuff();

		static void printRow();

		static void printInterRow();

		static void printBoxMap(Box box);

		static void printCoordinates(Coordinates coordinates);

		static void printMultiArray(int multiArr[][maxRows]);

		~PrintStuff();

};
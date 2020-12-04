#ifndef UTILS_HPP
#define UTILS_HPP

class Utils{
	private:

	public:

		Utils();

		static int correctNextBoxIndexHorizontal(int index);

		static int correctNextBoxIndexVertical(int index);

		static int correctNextBoxesRowIndexHorizontal(int currentIndex);

		static int correctNextBoxesRowIndexVertical(int currentIndex);

		static bool checkVictory();

		static int getVectorElementIndex(std::vector<int> vector, int element);

		~Utils();

};

#endif
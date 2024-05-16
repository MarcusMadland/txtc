#include "gibberish.h"

#include <cstdlib>
#include <ctime>

GibberishGenerator::GibberishGenerator()
{
	std::srand(std::time(nullptr));
}

GibberishGenerator::~GibberishGenerator()
{
	// Destructor
}

void GibberishGenerator::generateGibberish(int length)
{
	for (int i = 0; i < length; ++i) {
		std::cout << generateRandomWord() << " ";
	}
	std::cout << std::endl;
}

std::string GibberishGenerator::generateRandomWord()
{
	int wordLength = getRandomNumber(3, 10);
	std::string word;
	for (int i = 0; i < wordLength; ++i) {
		word += generateRandomChar();
	}
	return word;
}

char GibberishGenerator::generateRandomChar()
{
	return static_cast<char>('a' + (std::rand() % 26));
}

int GibberishGenerator::getRandomNumber(int min, int max)
{
	return min + (std::rand() % (max - min + 1));
}

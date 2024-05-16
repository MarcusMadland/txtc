#ifndef GIBBERISH_H
#define GIBBERISH_H

#include <iostream>
#include <string>

class GibberishGenerator {
public:
	GibberishGenerator();
	~GibberishGenerator();

	void generateGibberish(int length);

private:
	std::string generateRandomWord();
	char generateRandomChar();

	int getRandomNumber(int min, int max);
};

#endif // GIBBERISH_H

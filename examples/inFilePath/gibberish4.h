#ifndef GIBBERISH_H
#define GIBBERISH_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <random>

class GibberishGenerator {
public:
	GibberishGenerator();
	~GibberishGenerator();

	void generateGibberish(int length);
	void generateGibberishSentence(int sentenceLength, int wordsPerSentence);

	void setSeed(unsigned int seed);
	void setWordLengthRange(int minLength, int maxLength);
	void enableMixedCase(bool enable);
	void enableNumbers(bool enable);
	void enableSpecialChars(bool enable);
	void addCustomWord(const std::string& word);
	void printCustomWords() const;

private:
	std::string generateRandomWord();
	char generateRandomChar();
	char generateRandomSpecialChar();
	int getRandomNumber(int min, int max);
	std::string generateRandomSentence(int wordCount);

	bool mixedCase;
	bool includeNumbers;
	bool includeSpecialChars;
	int minWordLength;
	int maxWordLength;
	unsigned int seed;
	std::vector<std::string> customWords;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;
};

#endif // GIBBERISH_H

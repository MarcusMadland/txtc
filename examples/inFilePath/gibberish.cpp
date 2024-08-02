#include "gibberish.h"

#include <cstdlib>
#include <ctime>

GibberishGenerator::GibberishGenerator()
	: mixedCase(false), includeNumbers(false), includeSpecialChars(false),
	minWordLength(3), maxWordLength(10), seed(static_cast<unsigned int>(std::time(nullptr))),
	distribution(0, 25)
{
	generator.seed(seed);
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

void GibberishGenerator::generateGibberishSentence(int sentenceLength, int wordsPerSentence)
{
	for (int i = 0; i < sentenceLength; ++i) {
		std::cout << generateRandomSentence(wordsPerSentence) << ". ";
	}
	std::cout << std::endl;
}

void GibberishGenerator::setSeed(unsigned int newSeed)
{
	seed = newSeed;
	generator.seed(seed);
}

void GibberishGenerator::setWordLengthRange(int minLength, int maxLength)
{
	minWordLength = minLength;
	maxWordLength = maxLength;
}

void GibberishGenerator::enableMixedCase(bool enable)
{
	mixedCase = enable;
}

void GibberishGenerator::enableNumbers(bool enable)
{
	includeNumbers = enable;
}

void GibberishGenerator::enableSpecialChars(bool enable)
{
	includeSpecialChars = enable;
}

void GibberishGenerator::addCustomWord(const std::string& word)
{
	customWords.push_back(word);
}

void GibberishGenerator::printCustomWords() const
{
	std::cout << "Custom Words:" << std::endl;
	for (const auto& word : customWords) {
		std::cout << word << std::endl;
	}
}

std::string GibberishGenerator::generateRandomWord()
{
	int wordLength = getRandomNumber(minWordLength, maxWordLength);
	std::string word;
	for (int i = 0; i < wordLength; ++i) {
		if (includeSpecialChars && getRandomNumber(0, 5) == 0) {
			word += generateRandomSpecialChar();
		}
		else {
			word += generateRandomChar();
		}
	}
	return word;
}

char GibberishGenerator::generateRandomChar()
{
	if (includeNumbers && getRandomNumber(0, 1) == 0) {
		return static_cast<char>('0' + getRandomNumber(0, 9));
	}

	char base = mixedCase && getRandomNumber(0, 1) == 0 ? 'A' : 'a';
	return static_cast<char>(base + getRandomNumber(0, 25));
}

char GibberishGenerator::generateRandomSpecialChar()
{
	// Generates random special characters
	const std::string specialChars = "!@#$%^&*()_+[]{}|;:',.<>?/";
	return specialChars[getRandomNumber(0, specialChars.length() - 1)];
}

int GibberishGenerator::getRandomNumber(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(generator);
}

std::string GibberishGenerator::generateRandomSentence(int wordCount)
{
	std::string sentence;
	for (int i = 0; i < wordCount; ++i) {
		sentence += generateRandomWord() + " ";
	}
	return sentence;
}

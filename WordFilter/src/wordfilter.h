#pragma once

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using std::ifstream;
using std::map;
using std::multimap;
using std::ofstream;
using std::string;


bool isLetter_(const char& chr)
{
	if (chr >= 'a' && chr <= 'z')
		return true;
	return false;
}

bool isBadSymbol_(const char& chr)
{
	if (chr > 32 && chr < 127)
		return true;
	return false;
}


class Text
{
private:
	//CLASSES

	//class is used to store unique words, count of them etc.
	class Word	
	{
	private:
		typedef unsigned int uint;	//rename unsigned int into uint

		struct Place { uint paragraph, sentence; };	//structure contains place of the word in text

		//VARIABLES

		string word_;
		uint count_;
		std::vector<Place> place_;
		

	public:
		Word() : word_(), count_(0) {}
		Word(const string& str) : word_(str), count_(1) { }

		//SETTER FUNCTIONS

		void setWord(const string& str) { word_ = str; count_++; }
		void setPlace(const uint& paragraph, const uint& sentence) { Place temp{ paragraph, sentence }; place_.push_back(temp); }

		//GETTER FUNCTIONS

		string word() const { return word_; }
		uint count() const { return count_; }

		uint sentence(const uint& index) const 
		{ 
			if (index >= place_.size()) 
				throw std::out_of_range{ "Word::sentence: vector out of range" }; 
			return place_[index].sentence; 
		}

		uint paragraph(const uint& index) const 
		{ 
			if (index >= place_.size())
				throw std::out_of_range("Word::paragraph: vector out of range");
			return place_[index].paragraph; 
		}

		//OPERATORS

		inline Word operator++(int a) { count_++; return *this; }
		inline Word& operator++() { count_++; return *this; }
		inline Word operator--(int a) { count_++; return *this; }
		inline Word& operator--() { count_++; return *this; }

		friend std::ostream& operator<<(std::ostream& out, const Word& word) 
		{ 
			out << word.word_ << "\nCount: " << word.count_ << '\n';
			out << "Found in [Paragraph:Sentence] : ";
			for (const auto& it : word.place_)
				out << '[' << it.paragraph << ':' << it.sentence << "], ";
			return out;
		}
	};

	//VARIABLES

	string text_;
	multimap<char, Word> word_container_;
	multimap<char, Word> url_container_;
	multimap<unsigned int, Word> sorted_word_container;	//sorted by count



	//PRIVATE FUNCTIONS

	inline void toLower_(string& str) { std::transform(text_.begin(), text_.end(), text_.begin(), ::tolower); }

	string& readFromFile_(ifstream& inp)
	{
		if (inp.is_open())	//check if open
		{
			while (!inp.eof())
			{
				string temp_str;
				std::getline(inp, temp_str);	//readline
				
				text_ += " " + temp_str + " \n";				//append
			}
		}
		else
			throw std::ios_base::failure{ "Cannot open or read file." };
		return text_;
	}

	//function returns a substring of single word
	int getUntilWhitespace_(const string str)
	{	
		int index = 0;					//index of file_str to point to characters
		while (str[index] != ' ')		//search for whitespace
		{
			index++;					//increment by one
			if (index >= str.length())	//check if array access violations are not broken
				break;
		}
		return index;
	}


	int checkForCharacter_(string::iterator begin, const string::iterator& end, const char& chr)
	{
		while (begin != end)
		{
			if (*begin == chr)
				return 1;
			begin++;
		}
		return 0;
	}

	//check if 'http://', 'https://', 'www.'
	bool checkIfUrl(const string& str)
	{
		if (str[0] == 'h')
			if (str[1] == 't' && str[2] == 't' && str[3] == 'p')
			{
				if (str[4] == 's' && str[5] == ':' && str[6] == '/' && str[7] == '/')
					return true;
				if (str[4] == ':' && str[5] == '/' && str[6] == '/')
					return true;
			}

		if (str[0] == 'w')
			if (str[1] == 'w' && str[2] == 'w' && str[3] == '.')
				return true;
		return false;
	}

	void insertToMultimapContainer(multimap<char, Word>& container, const string& temp_word, const unsigned int& current_paragraph,
		const unsigned int& current_sentence)
	{
		auto multi_it = container.equal_range(temp_word[0]);

		bool found = false;
		for (auto i = multi_it.first; i != multi_it.second; i++)
			if (i->second.word() == temp_word)
			{
				i->second++;
				found = true;
				break;
			}
		if (found == false)	//else add the word
			container.insert({ temp_word[0], temp_word });

		//save the location of the word
		multi_it = container.equal_range(temp_word[0]);
		for (auto i = multi_it.first; i != multi_it.second; i++)
			if (i->second.word() == temp_word)
				i->second.setPlace(current_paragraph, current_sentence);
	}

	//function extracts words from text and counts them
	void countWords_()
	{
		string temp_text = text_;
		unsigned int current_sentence = 1, current_paragraph = 1;

		if (text_.empty())
			throw std::invalid_argument{ "Text string is empty.\n" };

		while (!temp_text.empty() || temp_text != "")
		{
			//removes unwanted symbols from the beginning
			bool newline_test = false;
			while (temp_text[0] < 'a' || temp_text[0] > 'z')
			{
				if (temp_text.empty())
					return;
				if (temp_text[0] == '\n' && newline_test == false)
				{
					current_paragraph++;
					current_sentence = 1;
					newline_test = true;
				}
				temp_text.erase(0, 0 + 1);
			}

			//extract a single first word, then remove from temporary string and repeat
			int length_index = getUntilWhitespace_(temp_text);

			string temp_word;
			temp_word.append(temp_text, 0, length_index);

			bool if_url = checkIfUrl(temp_word);
			
			//sort good characters at the begining of string, bad characters - at the end.
			string::iterator it;
			if (!if_url)
				it = std::stable_partition(temp_word.begin(), temp_word.end(), isLetter_);
			if (if_url)
				it = std::stable_partition(temp_word.begin(), temp_word.end(), isBadSymbol_);

			string temp_word2(it, temp_word.end());

			//erase bad characters
			temp_word.erase(it, temp_word.end());
			temp_word.shrink_to_fit();

			//check if word is already in the map and increase the count

			if (!if_url)
				insertToMultimapContainer(word_container_, temp_word, current_paragraph, current_sentence);
			else
				insertToMultimapContainer(url_container_, temp_word, current_paragraph, current_sentence);

			//check if sentences or paragraphs changed
			if (checkForCharacter_(temp_word2.begin(), temp_word2.end(), '\n'))
			{
				current_sentence = 1;
				current_paragraph++;
			}
			else
				if (!if_url)
					current_sentence += checkForCharacter_(temp_word2.begin(), temp_word2.end(), '.');
			

			temp_text.erase(0, length_index + 1);	//delete name from temporary file_str string
		}
		
	}

	std::ostream& printWords_(multimap<char, Word> container, std::ostream& out)
	{
		if (out.fail())
			throw std::ios_base::failure{ "ostream fail." };
		for (const auto& it : container)
			out << it.second << "\n\n";

		return out;
	}

	void sortByCount_()
	{
		sorted_word_container.clear();
		for (const auto& it : word_container_)
			sorted_word_container.insert({ it.second.count(), it.second });
	}

	std::ostream& printWordsSortedByCount_(std::ostream& out)
	{
		if (out.fail())
			throw std::ios_base::failure{ "ostream fail." };
		for (auto it = sorted_word_container.rbegin(); it != sorted_word_container.rend(); it++)
			if (it->second.count() > 1)
				out << it->second << "\n\n";
		return out;
	}

public:
	//CONSTRUCTORS

	Text() : text_("") {}	//default
	Text(const string& text) : text_(text) { toLower_(text_); }

	//GETTER FUNCTIONS

	inline string text() const { return text_; }
	//string count() const { return text_; }


	//OTHER TYPE OF FUNCTIONS

	//function reads input from text file
	inline void readFromFile(ifstream& inp) 
	{ 
		try { text_ = readFromFile_(inp); toLower_(text_); }
		catch (std::exception& ex)	{ std::cerr << "Text::readFromFile_ Error: " << ex.what(); } 
	}

	inline void countWords()
	{
		try { countWords_(); }
		catch (std::exception& ex) { std::cerr << "Text::countWords_ Error: " << ex.what(); }
	}

	inline std::ostream& printWords(std::ostream& out)
	{
		try { return printWords_(word_container_, out); }
		catch (std::exception& ex) { std::cerr << "Text::printWords_ Error: " << ex.what(); }
	}

	inline std::ostream& printURLs(std::ostream& out)
	{
		try { return printWords_(url_container_, out); }
		catch (std::exception& ex) { std::cerr << "Text::printWords_ Error: " << ex.what(); }
	}

	inline void sortByCount()
	{
		try { sortByCount_(); }
		catch (std::exception& ex) { std::cerr << "Text::sortByCount_ Error: " << ex.what(); }
	}

	inline std::ostream& printWordsSortedByCount(std::ostream& out)
	{
		try { return printWordsSortedByCount_(out); }
		catch (std::exception& ex) { std::cerr << "Text::printWordsSortedByCount_ Error: " << ex.what(); }
	}


	~Text() { }
};
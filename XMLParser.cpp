// by JJeong

/** XML parsing class implementation.
@file XMLParser.cpp */
#include <algorithm>  
#include <string>
#include <assert.h>
#include "XMLParser.hpp"

#include <locale> 
#include<sstream>

/*
Class: ECE 2574 Data Structure and Algorithms
Programmer: Joseph Jeong
Date: October 10th, 2017

Honor Code: I have neither given nor received any unauthorized assistance with this program.

*/

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
	tokenizedInputVector = {};
	elementNameBag = new Bag<std::string>();
	parseStack = new Stack <std::string>();

}  // end default constructor

   // TODO: Implement the destructor here
XMLParser::~XMLParser()
{
	delete elementNameBag;
	elementNameBag = nullptr;
	delete parseStack;
	parseStack = nullptr;
}  // end destructor

   // TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	string test = inputString;

	//To test if XML file starts with a left bracket.
	int lb, rb;
	lb = test.find('<') + 1;
	rb = test.find('>') + 1;
	if (rb < lb)
		return false;

	//To test if XML file is nested correctly.
	int firstlb, secondlb, firstrb;
	string temp1;
	firstlb = test.find('<') + 1;
	temp1 = test.substr(firstlb, test.length());

	secondlb = temp1.find('<') + 1;
	firstrb = temp1.find('>') + 1;
	if (secondlb < firstrb)
		return false;

	int testlength = test.length();
	for (int i = 0; i < testlength; i++) //Replacing new lines to white space.
	{
		if (test[i] == '\n')
		{
			test[i] = ' ';
		}
	}

	vector<string> chopped_strings; //This will contain split strings by delimter '>'.
	string token; //These are the potential tokens that will be tested.

	int first_bracket = test.find('<') + 1;
	test = test.substr(first_bracket, test.length()); //We will star our categorization process after stripping off the first '<'.

	string test_content = "";
	istringstream ss(test);

	while (getline(ss, token, '<')) //Insert all possible tokens into vector.
	{
		chopped_strings.push_back(token);
	}

	int second_bracket = 0;
	int choppedsize = chopped_strings.size();
	for (int i = 0; i < choppedsize; i++)
	{
		string test_token = chopped_strings[i];
		second_bracket = token.find('>');

		//Case1: Start Tag.
		if (second_bracket && (test_token.find('?') == -1) && (test_token.find('/') == -1))
		{
			string test_start = "";
			test_content = "";
			int start_bracket = test_token.find('>');
			int test_token_l = test_token.length();
			if (test_token_l > start_bracket)
				test_content = test_token.substr(start_bracket + 1, test_token.length());
			test_start = test_token.substr(0, start_bracket);
			if (int i = test_start.find('>') != -1)
				test_start = test_start.substr(0, i);
			_TokenStruct_ A = { START_TAG, test_start };
			tokenizedInputVector.push_back(A);
			if (test_content.size() != 0 && (test_content.find_first_not_of(" ") != std::string::npos) && (test_content.find('>') == -1))
			{
				_TokenStruct_ B = { CONTENT, test_content };
				tokenizedInputVector.push_back(B);
			}
		}

		//Case2: End tag.
		if (second_bracket && (test_token.find('?') == -1) && (test_token.find('/') != -1) && (test_token[0] == '/'))
		{
			string test_end = "";
			test_content = "";
			int end_bracket = test_token.find('>');
			int test_token_length = test_token.length();
			if (test_token_length > end_bracket)
				test_content = test_token.substr(end_bracket + 1, test_token.length());
			test_end = test_token.substr(1, end_bracket);
			int test_bracket = test_end.find('>');
			if (test_bracket != -1)
				test_end = test_end.substr(0, test_bracket);
			_TokenStruct_ A = { END_TAG, test_end };
			tokenizedInputVector.push_back(A);
			if (test_content.size() != 0 && (test_content.find_first_not_of(" ") != std::string::npos) && (test_content.find('>') == -1))
			{
				_TokenStruct_ B = { CONTENT, test_content };
				tokenizedInputVector.push_back(B);
			}
		}

		//Case3: Empty tag.
		if (second_bracket && (test_token.find('?') == -1) && (test_token.find('/') != -1))
		{
			string test_empty;
			test_content = "";
			int empty_bracket = test_token.find('>');
			int test_token_length = test_token.length();
			if (test_token_length > empty_bracket)
				test_content = test_token.substr(empty_bracket + 1, test_token.length());
			test_empty = test_token.substr(0, empty_bracket);
			int test_bracket = test_empty.find('>');
			if (test_bracket != -1)
				test_empty = test_empty.substr(0, test_bracket - 1);
			if (test_empty[test_empty.length() - 1] == '/')
			{
				test_empty = test_token.substr(0, empty_bracket - 1);
				_TokenStruct_ A = { EMPTY_TAG, test_empty };
				tokenizedInputVector.push_back(A);
				if (test_content.size() != 0 && (test_content.find_first_not_of(" ") != std::string::npos) && (test_content.find('>') == -1))
				{
					_TokenStruct_ B = { CONTENT, test_content };
					tokenizedInputVector.push_back(B);
				}
			}
		}

		//Case4: Declaration.
		if (second_bracket && (test_token.find('?') != -1) && (test_token[0] == '?'))
		{
			test_content = "";
			int dec_bracket = test_token.find('>');
			int test_token_length = test_token.length();
			if (test_token_length > dec_bracket)
				test_content = test_token.substr(dec_bracket + 1, test_token.length());
			string test_dec = "";
			test_dec = test_token.substr(0, test_token.length());
			int find_bracket = test_dec.find('>');
			test_dec = test_dec.substr(0, find_bracket);
			if ((test_dec[0] == '?') && (test_dec[test_dec.length() - 1] == '?'))
			{
				test_dec = test_dec.substr(1, test_dec.length() - 2);
				_TokenStruct_ A = { DECLARATION, test_dec };
				tokenizedInputVector.push_back(A);
				if (test_content.size() != 0 && (test_content.find_first_not_of(" ") != std::string::npos) && (test_content.find('>') == -1))
				{
					_TokenStruct_ B = { CONTENT, test_content };
					tokenizedInputVector.push_back(B);
				}
			}

		}
	}
	return true;

}  // end

   // TODO: Implement a helper function to delete attributes from a START_TAG
   // or EMPTY_TAG string (you can change this...)
static std::string deleteAttributes(string &value)
{
	locale loc;

	int whitespace_index = value.find(" ");
	int length = value.length();
	value = value.substr(0, whitespace_index);

	return value;
}

//Helper function created to determine if the tag names are valid.
static bool isNameValid(string value)
{
	locale loc;

	//XML tag names can't start with "-" or "."
	if (value[0] == '-' || value[0] == '.')
		return false;

	//Checking if tag names contains only valid characters.
	if (value.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_.-") != std::string::npos)
		return false;
	else
		return true;
}

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
	string start_string = "";
	string end_string = "";
	vector<string> end_vector = {};
	vector<string> start_vector = {};

	int size = tokenizedInputVector.size();
	string newName = "";

	//Deleting attributes.
	for (int i = 0; i < size; i++)
	{
		if ((tokenizedInputVector[i].tokenType == START_TAG) || (tokenizedInputVector[i].tokenType == END_TAG))
		{
			string newName = tokenizedInputVector[i].tokenString;
			deleteAttributes(newName);
			tokenizedInputVector[i].tokenString = newName;
		}
	}

	//Checking if name is valid.
	for (int i = 0; i < size; i++)
	{
		if ((tokenizedInputVector[i].tokenType == START_TAG) || (tokenizedInputVector[i].tokenType == END_TAG))
		{
			string newName = tokenizedInputVector[i].tokenString;
			if (!isNameValid(newName))
			{
				return false;
				clear();
			}
		}
	}

	//If txt file starts with an END_TAG or CONTENT file is invalid.
	if ((tokenizedInputVector[0].tokenType == END_TAG) || (tokenizedInputVector[0].tokenType == CONTENT))
	{
		clear();
		return false;
	}

	//If all valid, stack START_TAG.
	for (int i = 0; i < size; i++)
	{
		if (tokenizedInputVector[i].tokenType == START_TAG)
		{
			string start_string = tokenizedInputVector[i].tokenString;
			parseStack->push(start_string);

		}
	}

	for (int i = 0; i < size; i++) //Save all start tags.
	{

		if (tokenizedInputVector[i].tokenType == START_TAG)
		{
			start_string = tokenizedInputVector[i].tokenString;
			start_vector.push_back(start_string);
		}
	}

	for (int i = size - 1; i > 0; i--) //Save all end_tags in string vector in reverse order to compare first start tag and last end tag.
	{

		if (tokenizedInputVector[i].tokenType == END_TAG)
		{
			end_string = tokenizedInputVector[i].tokenString;
			end_vector.push_back(end_string);
		}
	}

	//Since XML files should have one element the last start tag and end tag name should match.
	if ((start_vector[0] != end_vector[0]) && (start_vector.size() != end_vector.size()))
		return false;

	int vector_size = end_vector.size();

	for (int i = 1; i < vector_size; i++) //Pop everytime when tags are balanced.
	{
		if (start_vector[i] == end_vector[vector_size - i])
			parseStack->pop();
	}

	if ((start_vector[0] == end_vector[0])) //Pop last tag if they match.
		parseStack->pop();

	if (!parseStack->isEmpty()) //If the stack is empty the XML file is balanced and valid.
		return false;
	else
	{
		return true;
	}
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
	tokenizedInputVector.clear();
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

//TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
	int size = tokenizedInputVector.size();

	for (int i = 0; i < size; i++)
	{
		if (tokenizedInputVector[i].tokenType == EMPTY_TAG || tokenizedInputVector[i].tokenType == START_TAG)
			elementNameBag->add(tokenizedInputVector[i].tokenString);
	}

	if (elementNameBag->contains(inputString))
		return true;
	else
		false;
}

//TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{
	return elementNameBag->getFrequencyOf(inputString);
}
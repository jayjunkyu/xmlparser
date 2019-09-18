// by JJeong

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include <iostream>
#include "catch.hpp"
#include "XMLParser.hpp"

using namespace std;

// Implement tests of your Stack class and XMLParser class
//Given test to verify Bag.
TEST_CASE("Test Bag add", "[XMLParser]")
{
	INFO("Hint: testing Bag add()");
	// Create a Bag to hold ints
	Bag<int> intBag;
	int testSize = 2;
	int bagSize;
	bool success;
	for (int i = 0; i<testSize; i++) {
		success = intBag.add(i);
		REQUIRE(success);
		bagSize = intBag.size();
		success = (bagSize == (i + 1));
		REQUIRE(success);
	}
}

//Given test to verify push()
TEST_CASE("Test Stack push", "[XMLParser]")
{
	INFO("Hint: testing Stack push()");
	// Create a Stack to hold ints
	Stack<int> intStack;
	int testSize = 3;
	int stackSize;
	bool success;
	for (int i = 0; i<testSize; i++) {
		success = intStack.push(i);
		REQUIRE(success);
		stackSize = intStack.size();
		success = (stackSize == (i + 1));
		REQUIRE(success);
	}
}

//Testing Stack constructor.
TEST_CASE("Test Stack constructor", "[XMLParser]")
{
	INFO("Hint: testing Stack constructor()");
	// Create a Stack to hold ints
	Stack<int> intStack;
	REQUIRE(intStack.isEmpty()); //intStack is initialized to NULL so this should be true.
}

//Testing isEmpty().
TEST_CASE("Test Stack isEmpty()", "[XMLParser]")
{
	INFO("Hint: testing Stack isEmpty()");
	// Create a Stack to hold ints
	Stack<int> intStack;
	int testSize = 3;
	for (int i = 0; i<testSize; i++)
	{
		intStack.push(i);
	}
	REQUIRE(!intStack.isEmpty());
	intStack.clear();
	REQUIRE(intStack.isEmpty());
}

//Testing size().
TEST_CASE("Test Stack size()", "[XMLParser]")
{
	INFO("Hint: testing Stack size()");
	// Create a Stack to hold ints
	Stack<int> intStack;
	REQUIRE(intStack.size() == 0);
}

//Testing pop().
TEST_CASE("Test Stack pop()", "[XMLParser]")
{
	INFO("Hint: testing Stack push()");
	// Create a Stack to hold ints
	Stack<int> intStack;
	int testSize = 3;
	for (int i = 0; i<testSize; i++)
	{
		intStack.push(i);
	}
	intStack.pop();
	REQUIRE(intStack.size() == 2); //If popped correctly, the size should decrease.
}

//Testing peek().
TEST_CASE("Test Stack peek()", "[XMLParser]")
{
	INFO("Hint: testing Stack peek()");
	Stack<int> intStack;
	intStack.push(1); //Add one itemtype to intStack
	REQUIRE(intStack.peek() == 1); //Check if peek returns true.
}

//Testing clear().
TEST_CASE("Test Stack clear()", "[XMLParser]")
{
	INFO("Hint: testing Stack clear()");
	// Create a Stack to hold ints
	Stack<int> intStack;
	int testSize = 3;
	for (int i = 0; i<testSize; i++)
	{
		intStack.push(i);
	}
	intStack.clear();
	REQUIRE(intStack.isEmpty());
}

//Testing tokenizing
TEST_CASE("Test XMLParser tokenizeInputString", "[XMLParser]")
{
	INFO("Hint: tokenize single element test of XMLParse");
	// Create an instance of XMLParse
	XMLParser myXMLParser;
	string testString = "<test>stuff</test>";
	bool success;
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
}

//Testing parsing.
TEST_CASE("Test XMLParser tokenizeParse", "[XMLParser]")
{
	INFO("Hint: tokenize single element test of XMLParse");
	// Create an instance of XMLParse
	XMLParser myXMLParser;
	string testString = "<abc>hi</abc>";
	bool success;
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(myXMLParser.parseTokenizedInput());
	myXMLParser.clear();
}

//Testing XMLParser containsElementName
TEST_CASE("Test XMLParser containsElementName", "[XMLParser]")
{
	INFO("Hint: tokenize single element test of XMLParse");
	// Create an instance of XMLParse
	XMLParser myXMLParser;
	string testString = "<abc>hi</abc>";
	bool success;
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(myXMLParser.parseTokenizedInput());
	string test = "abc";
	REQUIRE(myXMLParser.containsElementName(test));
	myXMLParser.clear();
}

//Testing XMLParser frequency.
TEST_CASE("Test XMLParser frequency", "[XMLParser]")
{
	INFO("Hint: tokenize single element test of XMLParse");
	// Create an instance of XMLParse
	XMLParser myXMLParser;
	string testString = "<abc>hi<abc/></abc>";
	bool success;
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(myXMLParser.parseTokenizedInput());
	string test = "abc";
	bool success2;
	if (myXMLParser.frequencyElementName(test) == 2)
		REQUIRE(true);
}
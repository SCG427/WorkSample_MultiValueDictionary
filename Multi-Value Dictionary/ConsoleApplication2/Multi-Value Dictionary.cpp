//The Multi-Value Dictionary app is a command line application that stores a multivalue dictionary in memory
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;

// making typedef for short declaration
typedef unordered_multimap<string, string>::iterator unit;  //Iterator
typedef unordered_multimap<string, string> dict;            //unordered multivalue dictionary [key,value] of string type 

//supported command enums
enum level { ADD, ALLMEMBERS, KEYS, MEMBERS, CLEAR, REMOVEALL, ITEMS, REMOVE, KEYEXISTS, MEMBEREXISTS,EXIT };
map<string, level> levels;

//mapping string to its enum value
void register_levels()
{
	levels["ADD"] = ADD;
	levels["ALLMEMBERS"] = ALLMEMBERS;
	levels["KEYS"] = KEYS;
	levels["MEMBERS"] = MEMBERS;
	levels["CLEAR"] = CLEAR;
	levels["REMOVEALL"] = REMOVEALL;
	levels["ITEMS"] = ITEMS;
	levels["REMOVE"] = REMOVE;
	levels["KEYEXISTS"] = KEYEXISTS;
	levels["MEMBEREXISTS"] = MEMBEREXISTS;
	levels["EXIT"] = EXIT;
}



//Returns all the members in the dictionary
void printAllMemebers(unordered_multimap<string, string> dict)
{
	// empty returns true, if container is empty else it
	// returns false
	if (dict.empty())
	{
		std::cout << "dictionary set is empty" << endl;
	}
	else {

		// size returns total number of elements in dictionary
		std::cout << "Size of dictionary set is :" << dict.size() << endl;

		// begin() returns iterator to first element of dictionary
		unit it = dict.begin();

		for (; it != dict.end(); it++)
			std::cout << "[" << it->first << '\t' << it->second
			<< "]" << endl;
	}
}

//Returns all keys in the dictionary and all of their members. Returns nothing if there are none. Order is not guaranteed.
void PrintITEMS(unordered_multimap<string, string> dict)
{
	// empty returns true, if container is empty else it
	// returns false
	if (dict.empty())
	{
		std::cout << "dictionary set is empty" << endl;
	}
	else {

		// size returns total number of elements in dictonary
		std::cout << "Size of dictionary set is :" << dict.size() << endl;

		// begin() returns iterator to first element of dictionary
		unit it = dict.begin();

		for (; it != dict.end(); it++)
			std::cout << it->first << ":" << it->second << endl;
	}
}


//Returns all the keys in the dictionary
void Keys(unordered_multimap<string, string> dict)
{
	// empty returns true, if container is empty else it
	   // returns false
	if (dict.empty())
	{
		std::cout << "dictionary set is empty" << endl;
	}
	else {
		// begin() returns iterator to first element of dictionary
		unit it = dict.begin();

		for (; it != dict.end(); it++)
			std::cout << it->first << endl;
	}
}

// Returns the collection of strings for the given key. Return order is not guaranteed. Returns an error if the key does not exists.
void Members(unordered_multimap<string, string> dict, string keys)
{
	bool retValue = false;
	unit it = dict.begin();
	std::cout << "Member of " << keys << " :" << endl;
	for (; it != dict.end(); it++)
	{
		
		if (keys == it->first)
		{
			std::cout << it->second << endl;
			retValue = true;
		}
	}

	if (!retValue)
	{
		std::cout << "ERROR :Key does not exist in Dictionary" << endl;
	}
}


// Driver code
int main()
{
	string cmd;
	dict d;

	//Entry point into the application. Reroutes to commandLineInterface to begin taking in user input and interactions with the multi-value dictionary

	std::cout << "******Multi-Value Dictionary Application - Supported Commands*******" << endl;
	std::cout << "ADD	"<< "ALLMEMBERS	" << "KEYS	" << "MEMBERS		"<< "CLEAR	" <<"ITEMS	" << endl;
	std::cout << "EXIT	"<< "REMOVEALL	" << "REMOVE	" << "KEYEXISTS	"<< "MEMBEREXISTS	" << endl;
	try {
		do {
			register_levels();

			std::cout << "*****************************************************************************" << endl;
			// takes user input in order to interact with the multi-value dictionary in memory console application
			std::getline(std::cin, cmd);

			//  Extract the command into words
			std::istringstream input(cmd);

			std::string word;
			std::vector<std::string> words;

			//converting into vector list to store commad, key and member values.
			while (input >> word)
				words.push_back(word);

			switch (levels[words[0]])
			{
			case ADD:
				// Adds a member to a Dictionary

				//checks for correct arguments before ADD operation
				if (words.size() != 3) {
					std::cout << "ERROR - Incorrect arguments" << endl;;
				}
				else
				{
					// check for dictinory empty or not
					if (d.empty())
					{
						d.insert(dict::value_type(words[1], words[2]));
						std::cout << "ADDED" << endl;;
					}
					else
					{
						// find and return any pair, associated with key
						unit it = d.find(words[1]);
						if (it != d.end())
						{
							if (words[2] == it->second)
							{
								std::cout << "ERROR - Member already exsists" << endl;;
							}
							else
							{
								d.insert(dict::value_type(words[1], words[2]));
								std::cout << "ADDED" << endl;
							}
						}
						else
						{
							d.insert(dict::value_type(words[1], words[2]));
							std::cout << "ADDED" << endl;
						}
					}
				}


				break;

			case ALLMEMBERS:
				//Returns all the members in the dictionary. Returns nothing if there are none. Order is not guaranteed.
				if (words.size() != 1) {
					std::cout << "ERROR - Incorrect arguments" << endl;;
				}
				else {
					printAllMemebers(d);
					break;
				}

			case KEYS:
				// Returns all the keys in the dictionary. Order is not guaranteed.
				if (words.size() != 1) {
					std::cout << "ERROR - Incorrect arguments" << endl;;
				}
				else {
					Keys(d);
				}
				break;

			case MEMBERS:
				// Returns the collection of strings for the given key. Return order is not guaranteed. Returns an error if the key does not exists.
				// check for dictionary empty or not
				if (words.size() != 2) {
					std::cout << "ERROR - Incorrect arguments" << endl;;
				}
				else {
					if (d.empty())
					{
						std::cout << "dictionary set is empty" << endl;
					}
					else
					{
						Members(d, words[1]);
					}
				}

				break;
			case CLEAR:
				// Removes all keys and all members from the dictionary.
				if (words.size() != 1) {
					std::cout << "ERROR - Incorrect arguments" << endl;;
				}
				else {
					d.clear();
					std::cout << "CLEARED" << endl;
				}
				break;

			case REMOVEALL:
				//Removes all members for a key and removes the key from the dictionary. Returns an error if the key does not exist.
				if (words.size() != 2) {
					std::cout << "ERROR - Incorrect arguments" << endl;;
				}
				else {
					// check for dictionary empty or not
					if (d.empty())
					{
						std::cout << "dictionary set is empty" << endl;
					}
					else
					{
						d.erase(words[1]);
						std::cout << "\nAfter deletion of " << words[1] << endl;
						printAllMemebers(d);
					}
				}
				break;
			case ITEMS:
				//Returns all keys in the dictionary and all of their members. Returns nothing if there are none. Order is not guaranteed.
				if (words.size() != 1) {
					std::cout << "ERROR - Incorrect arguments" << endl;;
				}
				else {
					PrintITEMS(d);
				}
				break;
			case REMOVE:
				//Removes a member from a key. If the last member is removed from the key, the key is removed from the dictionary.
				//If the key or member does not exist, displays an error
				if (words.size() != 3) {
					std::cout << "ERROR - Incorrect arguments" << endl;;
				}
				else {
					// check for dictionary empty or not

					if (d.empty())
					{
						std::cout << "dictionary set is empty" << endl;
					}
					else
					{
						// find and return any pair, associated with key
						unit it = d.find(words[1]);
						for (; it != d.end(); it++)
						{
							if (it != d.end()) {
								if (words[2] == it->second)
								{
									d.erase(it);
									std::cout << "REMOVED" << endl;
									printAllMemebers(d);
									break;
								}
							}
							else
							{
								std::cout << "ERROR :Key does not exist in Dictionary" << endl;
							}
						}
					}
				}
				break;
			case KEYEXISTS:
				//Returns whether a key exists or no
				if (words.size() != 2) {
					std::cout << "ERROR - Incorrect arguments" << endl;
				}
				else {
					// check for dictionary empty or not
					if (d.empty())
					{
						std::cout << "dictionary set is empty" << endl;
					}
					else
					{
						if (d.find(words[1]) != d.end()) {
							std::cout << "TRUE - Key exists in Dictionary" << endl;
						}
						else {
							std::cout << "FALSE - Key not exists in Dictionary" << endl;
						}
					}
				}
				break;
			case MEMBEREXISTS:
				//Returns whether a member exists within a key. Returns false if the key does not exist.
				if (words.size() != 3) {
					std::cout << "ERROR - Incorrect arguments" << endl;;
				}
				else {
					// check for dictionary empty or not
					if (d.empty())
					{
						std::cout << "dictionary set is empty" << endl;
					}
					else
					{

						unit it = d.find(words[1]);
						if (it != d.cend()) {
							if (words[2] == it->second)
							{
								std::cout << "TRUE - Member exists in Dictionary" << endl;
							}
							else
							{
								std::cout << "FALSE -Member not exists in Dictionary" << endl;
							}
						}
						else
						{
							std::cout << "FALSE - Key not exists in Dictionary" << endl;
						}
					}
				}
				break;
			case EXIT:
				exit(0);
				break;
			default:
				std::cout << "Invalid Option" << endl;
				exit(0);
				break;
			}
		} while (!cmd._Equal("EXIT"));
	}
	catch (std::string e)
	{
		std::cout << "encountered exception"<< e << endl;
	}
}
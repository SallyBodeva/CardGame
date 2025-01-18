/**
* 
* Solution to course project #8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024 / 2025
* 
* @author Salihe Ali Bodeva
* @idnumber 9MI0600468
* @compiler VS
*
* file with methods for helper functions
* 
*/
#include <stdlib.h>
#include <time.h>      
#include <iostream>
#include <string>
#include <vector>
#include "GameLogic.h"
#include "GameLogicPart2.h"
#include "Constants.h"


using namespace std;
using std::string;
using std::vector;


void toLower(string& input) {

	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] >= 'A' && input[i] <= 'Z')
		{
			input[i] += DIFF_BETWEEN_SMALL_AND_CAPITAL_LETTERS;
		}
	}
}

void toUpper(string& input) {

	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] >= 'a' && input[i] <= 'z')
		{
			input[i] -= DIFF_BETWEEN_SMALL_AND_CAPITAL_LETTERS;
		}
	}
}

bool validateYesNoResponse() {
	string response;
	cin >> response;

	toLower(response);

	while (response != "yes" && response != "no") {
		cout << "Invalid response. Please enter 'yes' or 'no': ";
		cin >> response;
		toLower(response);
	}

	return response == "yes";
}

bool isValidCardType(string& cardType) {

	const vector<string> validCardTypes = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "A", "J", "Q", "K" };

	toUpper(cardType);

	for (int i = 0; i < validCardTypes.size();i++) {

		if (cardType == validCardTypes[i])
		{
			return true;
		}
	}
	return false;
}

int getCardRank(const string& card) {
	if (card == "A") return 1;
	if (card == "J") return 11;
	if (card == "Q") return 12;
	if (card == "K") return 13;
	return stoi(card); 
}

void bubbleSort(vector<string>& cards) {
	int n = cards.size();
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (getCardRank(cards[j]) > getCardRank(cards[j + 1])) {
				string temp = cards[j];
				cards[j] = cards[j + 1];
				cards[j + 1] = temp;
			}
		}
	}
}
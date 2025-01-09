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

void bubbleSort(vector<string>& deck) {
	int n = deck.size();

	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
			
			int currentCard = stoi(deck[j]);
			int nextCard = stoi(deck[j + 1]);
			if (currentCard > nextCard) {

				string temp = deck[j];
				deck[j] = deck[j + 1];
				deck[j + 1] = temp;
			}
		}
	}
}
/*
* Solution to course project #8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024 / 2025
* @author Salihe Ali Bodeva
* @idnumber 9MI0600468
* @compiler VS
*
* file with methods for game logic part 2
*/

#include <stdlib.h>
#include <time.h>      
#include <iostream>
#include <string>
#include <vector>

#include "GameLogicPart2.h"
#include "GameLogic.h"
#include "Constants.h"
#include "HelperFunctions.h"


using namespace std;
using std::string;
using std::vector;

bool doesOpponentHaveIt(vector<string>& playerSets, vector<string>& opponentSets, string wantedCardType) {

	for (size_t i = 0; i < opponentSets.size(); i++)
	{
		if (opponentSets[i] == wantedCardType)
		{
			return true;
		}
	}
	return false;
}

void opponentGivesTheSet(vector<string>& playerSets, vector<string>& opponentSets, string wantedCardType) {

	playerSets.push_back(wantedCardType);

	int cardIndex = getCardIndex(opponentSets, wantedCardType);

	opponentSets.erase(opponentSets.begin() + cardIndex);

}


void startPart2(vector<string>& userSets, vector<string>& compSets) {

	const vector<string> validCardTypes = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "A", "J", "Q", "K" };

	srand(time(0));
	bool turn = USER_TURN;
	while ((!userSets.empty()) && (!compSets.empty()))
	{
		bool turnContinous = true;

		if (turn)
		{
			while (turnContinous)
			{
				cout << "Please enter the card set you would like to ask for:  ";
				string cardType;

				cin >> cardType;

				while (!isValidCardType(cardType)) {
					cout << "Invalid card type. Please enter a valid card type from your set: ";
					cin >> cardType;
				}

				cout << "\n";

				if (doesOpponentHaveIt(userSets, compSets, cardType))
				{
					opponentGivesTheSet(userSets, compSets, cardType);
					cout << "Great you guessed a card set your opponent had." << endl;
					if (compSets.empty())
					{
						break;
					}
					cout << "It's your turn again!";
				}
				else
				{
					cout << "Nice try, but your oppponent doesnt't have this card type."<<endl;
					cout << "Your turn is over...";
					turnContinous = false;
					turn = !turn;
				}
			}
		}
		else
		{
			int randomSetIndex = rand() % validCardTypes.size();
			string requestedSet = validCardTypes[randomSetIndex];
			cout << "\n";
			cout << "Your opponent asks for [" << requestedSet << "]. Do you have it? (yes/no): ";

			cout << '\n';

			printDeck(userSets);

			bool hasCard = validateYesNoResponse();

			if (hasCard)
			{
				opponentGivesTheSet(compSets, userSets, requestedSet);
			}
			else
			{
				cout << "You deny having the set." << endl;
				cout << "The computer didn't get the set it wanted.\n";
				cout << "It's turn is over...\n" << endl;

				turnContinous = false;
				turn = !turn;
			}
		}

	}

	if (compSets.empty()) {
		cout << "Congratulations! You've won the game!\n";
	}
	else {
		cout << "Computer wins! Better luck next time.\n";
	}

}
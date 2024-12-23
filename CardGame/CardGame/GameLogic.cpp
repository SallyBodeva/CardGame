#include <stdlib.h>
#include <time.h>      
#include <iostream>
#include <string>
#include <vector>
#include "GameLogic.h"
#include "Constants.h"


using namespace std;
using std::string;
using std::vector;

void shuffleDeck(vector<string>& deck) {
	for (int i = deck.size() - 1; i > 0; i--) {

		int j = rand() % (i + 1);

		string temp = deck[i];
		deck[i] = deck[j];
		deck[j] = temp;
	}
}

void initialiseGame(vector<string>& mainDeckOfCars, vector<string>& userCards, vector<string>& computerCards)
{

	vector<string> cardTypes = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "A", "J", "Q", "K" };

	for (int i = 0; i < cardTypes.size(); i++)
	{
		for (int j = 0; j < COUNT_OF_CARDS_IN_DECK; j++)
		{
			mainDeckOfCars.push_back(cardTypes[i]);
		}
	}

	shuffleDeck(mainDeckOfCars);


	for (int i = 0; i < COUNT_OF_PLAYERS_CARDS; i++)
	{
		userCards.push_back(mainDeckOfCars.back());
		mainDeckOfCars.pop_back();

		computerCards.push_back(mainDeckOfCars.back());
		mainDeckOfCars.pop_back();
	}
}

bool changeTurn(bool previousTurn) {

	return !previousTurn;
}

int getCardIndex(vector<string>& deck, string card) {

	if (deck.empty())
	{
		return -1;
	}

	for (int i = 0; i < deck.size(); i++)
	{
		if (deck[i] == card)
		{
			return i;
		}
	}
	return -1;
}

void userAsksForCard(vector<string>& userCards, vector<string>& computerCards, string card) {

	int cardIndexAtComputerDeck = getCardIndex(computerCards, card);
	while (cardIndexAtComputerDeck != -1)
	{
		userCards.push_back(card);
		computerCards.erase(computerCards.begin() + cardIndexAtComputerDeck);
		cardIndexAtComputerDeck = getCardIndex(computerCards, card);
	}
}



void compAsksForCard(vector<string>& userCards, vector<string>& computerCards) {

	srand(time(0));
	int randomCardIndex = rand() % computerCards.size();
	
	string wantedCard = userCards[randomCardIndex];


	int cardIndexAtUserDeck = getCardIndex(userCards, wantedCard);

	while (cardIndexAtUserDeck != -1)
	{
		computerCards.push_back(wantedCard);
		userCards.erase(userCards.begin() + cardIndexAtUserDeck);

		cardIndexAtUserDeck = getCardIndex(userCards, wantedCard);
	}
}


void ptintDeck(vector<string> test) {

	for (int i = 0; i < test.size(); i++)
	{
		cout << test[i] << endl;
	}

}

void startGame()
{

}

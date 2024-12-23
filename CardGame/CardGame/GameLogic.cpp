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

	srand(time(0));
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

bool isTheAskingValid(vector<string>& cards, string card) {

	int result = getCardIndex(cards, card);
	if (result != -1)
	{
		return true;
	}
	return false;
}

void userTurn(vector<string>& userCards, vector<string>& computerCards, string card, vector<string>& mainDeck, bool& userContinues) {

	if (isTheAskingValid)
	{
		int cardIndexAtComputerDeck = getCardIndex(computerCards, card);
		userContinues = false;
		while (cardIndexAtComputerDeck != -1)
		{
			userContinues = true;
			userCards.push_back(card);
			computerCards.erase(computerCards.begin() + cardIndexAtComputerDeck);
			cardIndexAtComputerDeck = getCardIndex(computerCards, card);
		}

		if (!mainDeck.empty())
		{
			string cardFromMainDeck = mainDeck.back();

			userCards.push_back(cardFromMainDeck);
			mainDeck.pop_back();

			if (cardFromMainDeck == card)
			{
				userContinues = true;
			}
		}
	}
	else
	{
		cout << "You cannot ask for a card that you do not already possess.";
		return;
	}
}


void compTurn(vector<string>& userCards, vector<string>& computerCards, vector<string>& mainDeck, bool& compContinues) {

	srand(time(0));
	int randomCardIndex = rand() % computerCards.size();
	string wantedCard = userCards[randomCardIndex];
	int cardIndexAtUserDeck = getCardIndex(userCards, wantedCard);

	compContinues = false;

	while (cardIndexAtUserDeck != -1)
	{
		compContinues = true;
		computerCards.push_back(wantedCard);
		userCards.erase(userCards.begin() + cardIndexAtUserDeck);

		cardIndexAtUserDeck = getCardIndex(userCards, wantedCard);
	}

	if (!mainDeck.empty())
	{
		string cardFromMainDeck = mainDeck.back();

		userCards.push_back(cardFromMainDeck);
		mainDeck.pop_back();

		if (cardFromMainDeck == wantedCard)
		{
			compContinues = true;
		}
	}
}

bool hasFourCards(vector<string>& cards, string card, vector<string>& removedSets) {

	int cardCount = 0;

	for (int i = 0; i < cards.size(); i++)
	{
		if (cards[i] == card)
		{
			cardCount++;
		}
	}
	if (cardCount == CARD_IN_A_SET)
	{

		for (int i = 0; i < cards.size(); i++)
		{
			if (cards[i] == card)
			{
				cards.erase(cards.begin() + i);
			}
			else
			{
				i++;
			}
		}

		removedSets.push_back(card);
		return true;
	}
	return false;
}


void printDeck(vector<string>& deck) {
	cout << "Deck of Cards:" << endl;
	cout << "===================" << endl;

	for (size_t i = 0; i < deck.size(); i++) {
		cout << "*" << "[" << deck[i] << "]" << "*" << endl;
	}

	cout << "===================" << endl;
}

void startGame()
{
	vector<string> mainDeck;
	vector<string> userCards;
	vector<string> compCards;

	cout << "Dealing cards....\n\n";

	initialiseGame(mainDeck, userCards, compCards);

	cout << "You have these cards: " << endl;

	printDeck(userCards);

	bool turn = USER_TURN;
	while (!mainDeck.empty())
	{
		if (turn)
		{

		}
	}
}

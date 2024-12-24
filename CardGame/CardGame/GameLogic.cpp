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
			string card = cardTypes[i];
			mainDeckOfCars.push_back(card);
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

bool userTurn(vector<string>& userCards, vector<string>& computerCards, string card, vector<string>& mainDeck, bool& isTheTurnValid) {

	bool continous = false;
	if (isTheAskingValid(userCards, card))
	{
		int cardIndexAtComputerDeck = getCardIndex(computerCards, card);
		while (cardIndexAtComputerDeck != -1)
		{
			userCards.push_back(card);
			computerCards.erase(computerCards.begin() + cardIndexAtComputerDeck);
			cardIndexAtComputerDeck = getCardIndex(computerCards, card);
			continous = true;
		}

		if (continous)
		{
			return true;
		}

		if (!mainDeck.empty())
		{
			string cardFromMainDeck = mainDeck.back();

			userCards.push_back(cardFromMainDeck);
			mainDeck.pop_back();

			return cardFromMainDeck == card;
		}
	}
	else
	{
		cout << "Invalid card name. Please enter a card, that you already possess or valid card name.";
		isTheTurnValid = false;
		return true;
	}

	return false;
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
			while (true)
			{
				cout << "Ask your opponent for a card: ";
				string card;
				cin >> card;

				bool isTheTurnValid = true;
				bool result = userTurn(userCards, compCards, card, mainDeck, isTheTurnValid);

				if (isTheTurnValid == false)
				{
					continue;
				}

				if (result)
				{
					cout << "Your opponent gives you all the [" << card << "], he got" << "!\n";

					cout << "Great, you have received the card you wanted, it is your turn again!..." << endl;
				}
				else
				{
					cout << "Nice try, but you didn't get the card you wanted..." << endl;
					cout << "You got [" << userCards.back() << "] from the main deck...";
					cout << "Your turn is over..." << endl;
					turn = !turn;
					break;
				}
			}
		}
		else
		{

		}
	}
}

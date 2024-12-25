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


bool compTurn(vector<string>& userCards, vector<string>& computerCards, vector<string>& mainDeck, string& requestedCard) {

	srand(time(0));
	int randomCardIndex = rand() % computerCards.size();
	requestedCard = computerCards[randomCardIndex];

	cout << "Your opponent asks for [" << requestedCard << "]. Do you have it? (yes/no): " << endl;
	cout << '\n';
	printDeck(userCards);
	cout << '\n';

	string response;
	cin >> response;

	bool continuousTurn = false;

	if (response == "yes") {
		int cardIndexAtUserDeck = getCardIndex(userCards, requestedCard);
		while (cardIndexAtUserDeck != -1) {
			continuousTurn = true;

			computerCards.push_back(requestedCard);
			userCards.erase(userCards.begin() + cardIndexAtUserDeck);
			cardIndexAtUserDeck = getCardIndex(userCards, requestedCard);
		}
	}
	else {
		cout << "You deny having the card." << endl;

		if (!mainDeck.empty()) {
			string cardFromMainDeck = mainDeck.back();
			mainDeck.pop_back();
			computerCards.push_back(cardFromMainDeck);

			if (cardFromMainDeck == requestedCard) {
				continuousTurn = true;
			}
		}
	}

	return continuousTurn;
}



bool playerHasFourCards(vector<string>& cards, string card) {

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
		return true;
	}
	return false;
}

void putDownFullSet(vector<string>& playersCards, vector<string>& putDownSet, string card) {

	putDownSet.push_back(card);

	for (int i = 0; i < playersCards.size(); i++)
	{
		if (playersCards[i] == card)
		{
			playersCards.erase(playersCards.begin() + i);
		}
		else
		{
			i++;
		}
	}

}

void checkAndHandleFullSet(bool isComputer, vector<string>& playerCards, vector<string>& putDownSet) {

	for (int i = 0; i < playerCards.size(); i++)
	{
		string card = playerCards[i];

		if (playerHasFourCards(playerCards, card)) {
			if (isComputer) {
				cout << "Computer has collected a set of [" << card << "] and puts it down.\n";
				putDownFullSet(playerCards, putDownSet, card);
			}
			else {
				cout << "You have a set of [" << card << "]. Please put it down manually.\n";
				cout << "Do you want to put it down? (yes/no): ";
				string response;
				cin >> response;
				if (response == "yes") {
					putDownFullSet(playerCards, putDownSet, card);
				}
				else {
					cout << "You chose not to put down the set.\n";
				}
			}
		}
	}
}

void printDeck(vector<string>& deck) {
	cout << "My deck of Cards:" << endl;
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

	vector<string> userPutDownCards;
	vector<string> compPutDownCards;

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
					cout << '\n';
					printDeck(userCards);
					cout << '\n';
				}
				else
				{
					cout << "Nice try, but you didn't get the card you wanted..." << endl;
					cout << "You got [" << userCards.back() << "] from the main deck...";
					cout << "Your turn is over..." << endl;

					cout << '\n';
					turn = !turn;

					checkAndHandleFullSet(false, userCards, userPutDownCards);
					break;
				}

				checkAndHandleFullSet(false, userCards, userPutDownCards);
			}
		}
		else
		{
			while (true) {
				string requestedCard;

				bool result = compTurn(userCards, compCards, mainDeck, requestedCard);

				if (result)
				{
					cout << "The computer got the cards it wanted";
					cout << "Its turn continues...\n";
				}

				else
				{
					cout << "The computer didn't get the card it wanted.\n";
					cout << "Its turn is over...\n" << endl;
					turn = !turn;
					checkAndHandleFullSet(true, compCards, compPutDownCards);
					break;
				}

				cout << '\n';
				checkAndHandleFullSet(true, compCards, compPutDownCards);
			}
		}
	}
}

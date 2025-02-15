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
* file with methods for game logic part 1
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
#include "HelperFunctions.h"


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

string drawFromTheMainDeck(vector<string>& playersCards, vector<string>& mainDeck) {

	if (!mainDeck.empty())
	{
		string cardFromMainDeck = mainDeck.back();
		playersCards.push_back(cardFromMainDeck);
		mainDeck.pop_back();

		return cardFromMainDeck;
	}


	return "";
}

bool userTurn(vector<string>& userCards, vector<string>& computerCards, string card, vector<string>& mainDeck, bool& isItFromMainDeck) {

	bool continous = false;

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

		if (cardFromMainDeck == card)
		{
			isItFromMainDeck = true;
		}

		return cardFromMainDeck == card;
	}

	return false;
}


string getRequestedCardForCompTurn(vector<string>& computerCards) {

	srand(time(0));
	int randomCardIndex = rand() % computerCards.size();
	string requestedCard = computerCards[randomCardIndex];

	return requestedCard;
}

bool compTurn(vector<string>& userCards, vector<string>& computerCards, vector<string>& mainDeck, string& requestedCard, bool response, bool& isItFromMainDeck) {

	bool continuousTurn = false;

	if (response) {
		int cardIndexAtUserDeck = getCardIndex(userCards, requestedCard);
		while (cardIndexAtUserDeck != -1) {
			continuousTurn = true;

			computerCards.push_back(requestedCard);
			userCards.erase(userCards.begin() + cardIndexAtUserDeck);
			cardIndexAtUserDeck = getCardIndex(userCards, requestedCard);
		}
	}
	else if (!mainDeck.empty()) {

		string cardFromMainDeck = mainDeck.back();
		mainDeck.pop_back();
		computerCards.push_back(cardFromMainDeck);

		if (cardFromMainDeck == requestedCard)
		{
			isItFromMainDeck = true;
		}

		return cardFromMainDeck == requestedCard;

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

	for (int i = 0; i < playersCards.size();) {
		if (playersCards[i] == card) {
			playersCards.erase(playersCards.begin() + i);
		}
		else {
			i++;
		}
	}

}

bool checkCompFullSet(vector<string>& playerCards, vector<string>& putDownSet, string& power) {

	for (int i = 0; i < playerCards.size(); i++)
	{
		string card = playerCards[i];

		if (playerHasFourCards(playerCards, card))
		{
			power = card;
			putDownFullSet(playerCards, putDownSet, card);
			return  true;
		}
	}

	return false;
}


bool checkUserFullSet(vector<string>& playerCards, vector<string>& putDownSet, string card, bool response) {

	if (response) {
		putDownFullSet(playerCards, putDownSet, card);
		return true;
	}
	return false;

}



void printDeck(vector<string>& deck) {
	cout << "Your deck of Cards:" << endl;
	cout << "===================" << endl;

	bubbleSort(deck);

	for (size_t i = 0; i < deck.size(); i++) {
		cout << "*" << "[" << deck[i] << "]" << "*" << endl;
	}

	cout << "===================" << endl;
}

void checkAndHandleFullSetUser(vector<string>& userCards, vector<string>& userPutDownCards)
{
	cout << "\n";
	cout << "Do you have a full set of a card type to put it down? (yes/no)" << endl;

	printDeck(userCards);

	bool response = validateYesNoResponse();

	if (response)
	{
		cout << "\n";
		cout << "Enter the card type you want to put down (e.g., A, 2, J, etc.): ";
		string card;
		cin >> card;

		while (!isValidCardType(card)) {
			cout << "Invalid card type. Please enter a valid card type: ";
			cin >> card;
		}

		checkUserFullSet(userCards, userPutDownCards, card, true);
		cout << "\n";
		cout << "The user successfully put down a full set of [" << card << "]!\n";
	}
	else {
		cout << "Okay, moving on...\n";
	}
}

void handleFullSetComp(vector<string>& compCards, vector<string>& compPutDownCards)
{
	string card = "";
	bool result = checkCompFullSet(compCards, compPutDownCards, card);
	if (result)
	{
		cout << "Computer has collected a full set" << " of [" << card << "] and puts it down.\n";
	}
}


void handleUserEmptyDeck(vector<string>& userCards, vector<string>& mainDeck) {
	if (userCards.empty()) {

		if (mainDeck.empty()) {
			cout << "You have no cards left and the main deck is empty. The game is over!\n";
		}
		else {
			cout << "Your deck is empty, drawing a card...\n";
			string card = drawFromTheMainDeck(userCards, mainDeck);
			if (!card.empty()) {
				cout << "You drew: [" << card << "]\n";
			}
		}
	}
}

void handleComputerEmptyDeck(vector<string>& compCards, vector<string>& mainDeck) {
	if (compCards.empty()) {

		if (mainDeck.empty())
		{
			cout << "The computer has no cards left and the main deck is empty. The game is over!\n";
		}
		else {
			cout << "The computer's deck is empty. It draws a card...\n";
			string card = drawFromTheMainDeck(compCards, mainDeck);
			if (!card.empty()) {
				cout << "The computer drew a card.\n";
			}
		}
	}
}


void handleUserTurn(vector<string>& userCards, vector<string>& compCards, vector<string>& mainDeck, vector<string>& userPutDownCards, vector<string>& compPutDownCards, bool& turn) {
	while (true) {
		if (userCards.empty()) {

			handleUserEmptyDeck(userCards, mainDeck);

			if (userCards.empty()) {
				cout << "Your turn is over because the main deck is empty\n";
			}

			turn = !turn;
			break;

		}

		cout << "\n--- Your Turn ---\n";
		printDeck(userCards);
		cout << "Enter the name of a card to ask your opponent for: ";
		string card;
		cin >> card;

		while (!isValidCardType(card)) {
			cout << "Invalid card type. Please enter a valid card type: ";
			cin >> card;
		}

		if (!isTheAskingValid(userCards, card)) {
			cout << "Invalid choice. Please choose a card you already have.\n";
			continue;
		}

		bool isItFromTheMainDeck = false;
		bool result = userTurn(userCards, compCards, card, mainDeck, isItFromTheMainDeck);
		cout << "\n";

		if (result && isItFromTheMainDeck == false) {
			cout << "You got all the [" << card << "] cards from your opponent!\n";
			cout << "Your turn continues...\n";
		}
		else if (isItFromTheMainDeck)
		{
			cout << "You did not get the card from your opponent.  Drawing a card from the deck...\n";
			cout << "You drew: [" << card << "] and that's why it is your turn again\n";
		}
		else {
			cout << "You did not get the card. Drawing a card from the deck...\n";
			cout << "You drew: [" << userCards.back() << "]\n";
			checkAndHandleFullSetUser(userCards, userPutDownCards);
			cout << "Your turn is over.\n";
			turn = !turn;
			break;
		}

		checkAndHandleFullSetUser(userCards, userPutDownCards);
	}
}

void handleComputerTurn(vector<string>& userCards, vector<string>& compCards, vector<string>& mainDeck, vector<string>& userPutDownCards, vector<string>& compPutDownCards, bool& turn) {
	while (true) {

		cout << "\n--- Computer's Turn ---\n";

		if (compCards.empty()) {
			handleComputerEmptyDeck(compCards, mainDeck);

			if (compCards.empty()) {
				cout << "The computer's turn is over because the main deck \n";
			}
			turn = !turn;
			break;
		}

		string requestedCard = getRequestedCardForCompTurn(compCards);
		cout << "\n";
		cout << "The computer asks for [" << requestedCard << "].\n";
		cout << "Do you have this card? (yes/no): ";

		printDeck(userCards);

		bool hasCard = validateYesNoResponse();
		bool isItFromTheMainDeck = false;

		bool result = hasCard
			? compTurn(userCards, compCards, mainDeck, requestedCard, true, isItFromTheMainDeck)
			: compTurn(userCards, compCards, mainDeck, requestedCard, false, isItFromTheMainDeck);

		cout << "\n";
		if (result && isItFromTheMainDeck == false) {
			cout << "The computer got the cards it wanted. Its turn continues...\n";
		}
		else if (isItFromTheMainDeck)
		{
			cout << "The computer did not get the card from the user.  Drawing a card from the deck...\n";
			cout << "The computer drew: [" << requestedCard << "] and that's why it is its turn again\n";
		}
		else {
			cout << "The computer did not get the card it wanted. Its turn is over.\n";
			handleFullSetComp(compCards, compPutDownCards);
			turn = !turn;
			break;
		}

		handleFullSetComp(compCards, compPutDownCards);
	}
}
//test

void startGame() {

	vector<string> mainDeck;
	vector<string> userCards;
	vector<string> compCards;
	vector<string> userPutDownCards;
	vector<string> compPutDownCards;

	cout << "Dealing cards....\n\n";
	initialiseGame(mainDeck, userCards, compCards);

	cout << "Welcome to the card game!\n";

	bool turn = USER_TURN;
	int totalCards = userPutDownCards.size() + compPutDownCards.size();

	while ((userCards.size() > 0 || mainDeck.size() > 0) && (compCards.size() > 0 || mainDeck.size() > 0) && totalCards != COUNT_OF_CARDS_TYPES) {

		if (userCards.empty() && compCards.empty() && mainDeck.empty()) {
			cout << "Both players have no cards left, and the main deck is empty. The game is over!\n";
			break;
		}

		if (turn) {
			handleUserTurn(userCards, compCards, mainDeck, userPutDownCards, compPutDownCards, turn);
		}
		else {
			handleComputerTurn(userCards, compCards, mainDeck, userPutDownCards, compPutDownCards, turn);
		}
	}

	cout << "\nGame Over! Moving to the next phase...\n";
	startPart2(userPutDownCards, compPutDownCards);
}
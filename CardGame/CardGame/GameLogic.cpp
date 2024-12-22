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

void ptintDeck(vector<string> test) {

	for (int i = 0; i < test.size(); i++)
	{
		cout << test[i] << endl;
	}

}

void startGame()
{

}

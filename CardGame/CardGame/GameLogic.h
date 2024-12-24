#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

void initialiseGame(vector<string>& mainDeckOfCars, vector<string>& userCards, vector<string>& computerCards);
void printDeck(vector<string>& deck);
void shuffleDeck(vector<string>& deck);
bool changeTurn(bool previousTurn);

bool isTheAskingValid(vector<string>& cards, string card);
bool userTurn(vector<string>& userCards, vector<string>& computerCards, string card, vector<string>& mainDeck, bool& isTheTurnValid);
void compTurn(vector<string>& userCards, vector<string>& computerCards, vector<string>& mainDeck, bool& compContinues);
int getCardIndex(vector<string>& deck, string card);
void startGame();
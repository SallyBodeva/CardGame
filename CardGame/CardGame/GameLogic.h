#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

void initialiseGame(vector<string>& mainDeckOfCars, vector<string>& userCards, vector<string>& computerCards);
void ptintDeck(vector<string> deck);
void shuffleDeck(vector<string>& deck);
bool changeTurn(bool previousTurn);

void userAsksForCard(vector<string>& userCards, vector<string>& computerCards, string card);
void compAsksForCard(vector<string>& userCards, vector<string>& computerCards);
int getCardIndex(vector<string>& deck, string card);
void startGame();
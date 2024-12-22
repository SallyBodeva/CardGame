#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

void initialiseGame(vector<string>& mainDeckOfCars, vector<string>& userCards, vector<string>& computerCards);
void ptintDeck(vector<string> deck);
void shuffleDeck(vector<string>& deck);
void startGame();
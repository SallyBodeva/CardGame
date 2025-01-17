/*
* Solution to course project #8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024 / 2025
* @author Salihe Ali Bodeva
* @idnumber 9MI0600468
* @compiler VS
*
* header file for game part 1
*/


#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

void initialiseGame(vector<string>& mainDeckOfCars, vector<string>& userCards, vector<string>& computerCards);
void printDeck(vector<string>& deck);
void shuffleDeck(vector<string>& deck);

bool isTheAskingValid(vector<string>& cards, string card);
bool userTurn(vector<string>& userCards, vector<string>& computerCards, string card, vector<string>& mainDeck, bool& isItFromMainDeck);
string getRequestedCardForCompTurn(vector<string>& computerCards);
bool compTurn(vector<string>& userCards, vector<string>& computerCards, vector<string>& mainDeck, string& requestedCard, bool response, bool& isItFromMainDeck);
bool playerHasFourCards(vector<string>& cards, string card);
int getCardIndex(vector<string>& deck, string card);
void putDownFullSet(vector<string>& playersCards, vector<string>& putDownSet, string card);
bool checkCompFullSet(vector<string>& playerCards, vector<string>& putDownSet, string& power);
bool checkUserFullSet(vector<string>& playerCards, vector<string>& putDownSet, string card, bool response);
void checkAndHandleFullSetUser(std::vector<std::string>& userCards, std::vector<std::string>& userPutDownCards);
void handleFullSetComp(std::vector<std::string>& compCards, std::vector<std::string>& compPutDownCards);
void startGame();
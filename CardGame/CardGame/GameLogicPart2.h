#pragma once


bool doesOpponentHaveIt(vector<string>& playerSets, vector<string>& opponentSets, string wantedCardType);

void opponentGivesTheSet(vector<string>& playerSets, vector<string>& opponentSets, string wantedCardType);

void printDeck(vector<string>& deck);

void clearScreen();

void startPart2(vector<string>& userSets, vector<string>& compSets);
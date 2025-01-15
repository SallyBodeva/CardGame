/*
* Solution to course project #8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024 / 2025
* @author Salihe Ali Bodeva
* @idnumber 9MI0600468
* @compiler VS
*
* header file for game part 2
*/

#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;
bool doesOpponentHaveIt(vector<string>& playerSets, vector<string>& opponentSets, string wantedCardType);
void opponentGivesTheSet(vector<string>& playerSets, vector<string>& opponentSets, string wantedCardType);
void startPart2(vector<string>& userSets, vector<string>& compSets);
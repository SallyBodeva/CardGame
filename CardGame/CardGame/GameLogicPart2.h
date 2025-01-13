#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;
bool doesOpponentHaveIt(vector<string>& playerSets, vector<string>& opponentSets, string wantedCardType);
void opponentGivesTheSet(vector<string>& playerSets, vector<string>& opponentSets, string wantedCardType);
void startPart2(vector<string>& userSets, vector<string>& compSets);
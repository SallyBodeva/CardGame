#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;


void toLower(string& input);
void toUpper(string& input);
bool validateYesNoResponse();
bool isValidCardType(string& cardType);
int getCardRank(const string& card);
void bubbleSort(vector<string>& cards);
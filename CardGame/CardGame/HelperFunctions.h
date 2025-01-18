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
* header file with helper functions
* 
*/

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
// Written by: Sofia Gratny
// Date: October 1st


#include <iostream>
#include <map>
#include <string.h>
#include <fstream>
#include <algorithm>

using namespace std;

map<char, int> dechex(void);
map<int, char> hexdecimal(void);
string addhex(string, string);

int main() {

    string operation, firsth, secondh;
    int resultNum = 1;
    ifstream inFile("Programming-Project-1.txt");

    while (inFile >> operation >> firsth >> secondh) {


        firsth.erase(0,2);
        secondh.erase(0,2);

        string result = addhex(firsth, secondh);
        cout << "Result " << resultNum++ << ": " << result << endl;

    }

    inFile.close();

    return 0;
}

/**
 * @brief 
 * 
 * @return 
 */
map<char, int> dechex(void) {

    map<char, int> values{
        {'0', 0}, {'1', 1},
        {'2', 2}, {'3', 3},
        {'4', 4}, {'5', 5},
        {'6', 6}, {'7', 7},
        {'8', 8}, {'9', 9},
        {'A', 10}, {'B', 11},
        {'C', 12}, {'D', 13},
        {'E', 14}, {'F', 15}
    };

    return values;
}

/**
 * @brief 
 * 
 * @return 
 */
map<int, char> hexdecimal(void) {

    map<int, char> values{
        {0, '0'}, {1, '1'},
        {2, '2'}, {3, '3'},
        {4, '4'}, {5, '5'},
        {6, '6'}, {7, '7'},
        {8, '8'}, {9, '9'},
        {10, 'A'}, {11, 'B'},
        {12, 'C'}, {13, 'D'},
        {14, 'E'}, {15, 'F'}
    };

    return values;    
}

/**
 * @brief 
 * 
 * @param operand1 
 * @param operand2 
 * @return 
 */
string addhex(string operand1, string operand2) {

    // map variable declarations
    map<char, int> decToHex = dechex();
    map<int, char> hexToDec = hexdecimal();

    
    if (operand1.length() > operand2.length()) {
        swap(operand1, operand2);
    }

    // initialise length of operand variables, and result and carry digit variables
    int length1 = operand1.length(), length2 = operand2.length();
    string result = "";
    int carryDigit = 0, i, j;

   
    for (i = length1 - 1, j = length2 - 1; j >= 0; i--, j--) {
       
        int sum = decToHex[operand1[i]] + decToHex[operand2[j]] + carryDigit;
        
        int additionBit = hexToDec[sum % 16];
        
        result.push_back(additionBit);
        
        carryDigit = sum / 16;
    }

    while (i >= 0) {
        int sum = decToHex[operand1[i]] + carryDigit;
        int additionBit = hexToDec[sum % 16];
        result.push_back(additionBit);
        carryDigit = sum / 16;
        i--;
    }

    if (carryDigit) {
        result.push_back(hexToDec[carryDigit]);
    }

    reverse(result.begin(), result.end());

    string formattedResult = "0x" + result;

    return formattedResult;

}
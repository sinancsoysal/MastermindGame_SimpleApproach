// MastermindGame.cpp : Author Yunus Emre Mavi
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void createCombinationPool();
void printCombinationPool();
void printVector(vector<int> vector);
void adjustCombinationPool(vector<int> guess, string pegScore);
string checkCode(vector<int> guess, vector<int> code);

static const int NUMS = 9;
static const int CODE_LENGTH = 4;
vector<vector<int>> combinationPool;

int main()
{
    createCombinationPool();
    //printCombinationPool();

    bool won = false;
    int turn = 1;

    vector<int> code = { 8, 2, 4, 3 };

    cout << "Code: ";
    
    printVector(code);
    cout << endl;

    while (!won) {
        vector<int> guess = combinationPool[0];

        string pegScore = checkCode(guess, code);

        cout << "Guess: ";
        printVector(guess);
        cout << "\tPegScore: " + pegScore;

        adjustCombinationPool(guess, pegScore);

        cout << "\tPool Size: " + to_string(combinationPool.size()) << endl;

        if (pegScore == "4 0") {
            won = true;
            cout << "Game Won!" << endl;
            break;
        }
    }

    return 0;
}

void createCombinationPool() {
    const vector<int> validDigits = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    for (int d1 = 1; d1 <= NUMS; d1++)
    {
        for (int d2 = 0; d2 <= NUMS; d2++)
        {
            for (int d3 = 0; d3 <= NUMS; d3++)
            {
                for (int d4 = 0; d4 <= NUMS; d4++)
                {
                    if (d1 != d2 && d1 != d3 && d1 != d4
                        && d2 != d3 && d2 != d4 && d3 != d4)
                    {
                        vector<int> comb;
                        comb.push_back(validDigits[d1]);
                        comb.push_back(validDigits[d2]);
                        comb.push_back(validDigits[d3]);
                        comb.push_back(validDigits[d4]);

                        combinationPool.push_back(comb);
                    }
                }
            }
        }
    }
}

void printCombinationPool() {
    for (auto i : combinationPool) {
        for (auto j : i)
            cout << j << ' ';
        cout << endl;
    }
}

void printVector(vector<int> vector) {
    for (auto i : vector) {
        cout << i << ' ';
    }
}

void adjustCombinationPool(vector<int> guess, string pegScore) {
    for (int i = 0; i < combinationPool.size(); ++i) {

        if (checkCode(combinationPool[i], guess) != pegScore) {
            combinationPool.erase(combinationPool.begin() + i);
        }

    }
}

string checkCode(vector<int> guess, vector<int> code) {

    string result;
    int plus = 0, minus = 0;

    for (int i = 0; i < CODE_LENGTH; ++i) {

        if (guess[i] == code[i]) {
            plus += 1;
        }
        else {
            if (code[i] > 0) {
                vector<int>::iterator it = find(guess.begin(), guess.end(), code[i]);
                if (it != guess.end()) {
                    minus -= 1;
                }
            }
        }
    }

    result.append(to_string(plus) + " " + to_string(minus));

    return result;
}

/*
 * Copyright (C) Mohsen Zohrevandi, 2017
 *               Rida Bazzi 2019
 * Do not share this file with anyone
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include "lexer.h"
#include <vector>
#include <algorithm>

using namespace std;
LexicalAnalyzer lexicalAnalyzer = *new LexicalAnalyzer();
Token first;
// read grammar
void ReadGrammar()
{
    first = lexicalAnalyzer.GetToken();

    //cout << "0\n";
}

vector<Token> TerminalsandNonTerminalsVec() {
    //cout << "1\n";
    //Write Code
    Token token;
    //LexicalAnalyzer lexicalAnalyzer = *new LexicalAnalyzer();

//    unordered_map<string, int> nonTerminals;
//    unordered_map<string, int> Terminals;
    vector<Token> nonTerminals;
    vector<Token> Terminals;

    //int count = 1;
    int tokenCount = 1;

    //Inserting every string in each line which is before the arrow
    token = first;
    nonTerminals.push_back(token);
//    while(token.token_type != HASH) {
//        //If when we peek the next string is an ARROW then the current index is a
//        if (lexicalAnalyzer.peek(1).token_type == ARROW) {
//            nonTerminals.insert({lexicalAnalyzer.GetToken().lexeme, count});
//            count++;
//        }
//
//        tokenCount++;
//        token = lexicalAnalyzer.peek(tokenCount);
//    }

    while(token.token_type != HASH) {
        //If when we peek the next string is an ARROW then the current index is a
        bool repeated = false;

        for (auto it = nonTerminals.begin(); it != nonTerminals.end(); it++) {
            if (it->lexeme == token.lexeme) {
                repeated = true;
                break;
            }
        }

        if (lexicalAnalyzer.peek(tokenCount + 1).token_type == ARROW && !repeated) {
            nonTerminals.push_back(token);
            //count++;
        }
        tokenCount++;
        token = lexicalAnalyzer.peek(tokenCount);
    }

    token = first;
    tokenCount = 1;
    while(token.token_type != HASH) {
        //If when we peek the next string is an ARROW then the current index is a
        bool repeated = false;
        for (auto it = nonTerminals.begin(); it != nonTerminals.end(); it++) {
            if (it->lexeme == token.lexeme) {
                repeated = true;
                break;
            }
        }

        for (auto it = Terminals.begin(); it != Terminals.end(); it++) {
            if (it->lexeme == token.lexeme) {
                repeated = true;
                break;
            }
        }
        if (!repeated) {
            Terminals.push_back(token);
        }

        tokenCount++;
        token = lexicalAnalyzer.peek(tokenCount);
    }

    Terminals.reserve(Terminals.size() + nonTerminals.size());

    // copy elements of vec2 into vec1
    std::copy(nonTerminals.begin(), nonTerminals.end(), std::back_inserter(Terminals));

    return Terminals;
}

// Task 1
void printTerminalsAndNoneTerminals()
{
    vector<Token> TerminalsandNonTerminals = TerminalsandNonTerminalsVec();

    //Print Terminals and Non Terminals
    for (auto it = TerminalsandNonTerminals.begin(); it != TerminalsandNonTerminals.end(); it++) {
        std::cout << it->lexeme << " ";
    }
}

// Task 2
void RemoveUselessSymbols()
{
    vector<Token> TerminalsandNonTerminals = TerminalsandNonTerminalsVec();
    Token* arr = TerminalsandNonTerminals.data();
    int vecSize = TerminalsandNonTerminals.size();

    Token generatingArray[vecSize];
    std::copy(TerminalsandNonTerminals.begin(), TerminalsandNonTerminals.end(), generatingArray);
}

// Task 3
void CalculateFirstSets()
{
    cout << "3\n";
}

// Task 4
void CalculateFollowSets()
{
    cout << "4\n";
}

// Task 5
void CheckIfGrammarHasPredictiveParser()
{
    cout << "5\n";
}
    
int main (int argc, char* argv[])
{
    int task;

    if (argc < 2)
    {
        cout << "Error: missing argument\n";
        return 1;
    }

    /*
       Note that by convention argv[0] is the name of your executable,
       and the first argument to your program is stored in argv[1]
     */

    task = atoi(argv[1]);
    
    ReadGrammar();  // Reads the input grammar from standard input
                    // and represent it internally in data structures
                    // ad described in project 2 presentation file

    switch (task) {
        case 1: printTerminalsAndNoneTerminals();
            break;

        case 2: RemoveUselessSymbols();
            break;

        case 3: CalculateFirstSets();
            break;

        case 4: CalculateFollowSets();
            break;

        case 5: CheckIfGrammarHasPredictiveParser();
            break;

        default:
            cout << "Error: unrecognized task number " << task << "\n";
            break;
    }
    return 0;
}


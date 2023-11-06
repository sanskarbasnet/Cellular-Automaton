#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <cstdlib>
#include <locale>
#include <bitset>
#include <limits>
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <csignal>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#include <unistd.h>
#endif

using namespace std;

// Constants for the size of the cellular automaton grid
const int ROW_SIZE = 60;
const int GENERATIONS = 45;

// Constants for the size of the Game of Life grid
const int ROWS = 30;
const int COLS = 100;

// Function declarations
void menu();
void generate(int *cells, int ruleset[]);
int rules(int left, int me, int right, int ruleset[]);
void runCellularAutomata(int ruleset[], int ruleNumber);
void runCustomisedCellularAutomaton(int ruleset[], int gens, int size, vector<int> index, int ruleNumber);
int *initialise(int size);
void populateFirstGeneration(vector<int> index, int *cells);
void printGeneration(int *cells, int ruleset[], int gens, int ruleNumber);
void cellularAutomatonMenu();
void decimalToBinary(int decimal, int binary[8]);
vector<int> parseAndStoreNumbers(const string &input, int max_size, int max_size2);
void gameOfLifeMenu();
void printMenuAgain();

// Function declarations for Game of Life
void generateBoard(int **cells);
void clearScreen();
void printBoard(int **cells);
void initializeRandom(int **cells);
int **initializeBoard();
void runWithRandomAliveCells();
void runWithCustomAliveCells(vector<int> index, bool editMode);
void saveToFile(string &boardState, int ruleNumber);
void simulateGlider();
void simulate2GliderMess();
void simulateAcorn();
void simulateAK47Reaction();
void startSimulation(int **board);

#endif // HELPER_H

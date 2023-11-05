#include <iostream>
#include <sstream>
#include <unistd.h>
using namespace std;

const int ROWS = 30;
const int COLS = 100;

void generate(int (*cells)[COLS]);
void clearScreen();
void printBoard(int (*cells)[COLS]);
void initializeRandom(int (*cells)[COLS]);

int main()
{
    int cells[ROWS][COLS];
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            cells[i][j] = 0;
        }
    }
    // cells[2][1] = 1;
    // cells[3][2] = 1;
    // cells[1][3] = 1;
    // cells[2][3] = 1;
    // cells[3][3] = 1;
    int(*pCells)[COLS] = cells;
    initializeRandom(pCells);
    while (true)
    {
        generate(pCells);
        clearScreen();
        printBoard(pCells);
        usleep(90000);
    }
}

void generate(int (*cells)[COLS])
{
    int next[ROWS][COLS] = {};

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            int neighbours = 0;
            for (int k = -1; k <= 1; ++k)
            {
                for (int l = -1; l <= 1; ++l)
                {
                    if (k != 0 || l != 0) // Exclude the cell itself
                    {
                        // Use modulo to wrap the edges
                        int row = (i + k + ROWS) % ROWS;
                        int col = (j + l + COLS) % COLS;
                        neighbours += cells[row][col];
                    }
                }
            }

            // Rules of Life
            if ((cells[i][j] == 1) && (neighbours < 2))
                next[i][j] = 0;
            else if ((cells[i][j] == 1) && (neighbours > 3))
                next[i][j] = 0;
            else if ((cells[i][j] == 0) && (neighbours == 3))
                next[i][j] = 1;
            else
                next[i][j] = cells[i][j];
        }
    }

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            cells[i][j] = next[i][j];
        }
    }
}


void printBoard(int (*cells)[COLS])
{
    std::stringstream ss;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            ss << (cells[i][j] == 1 ? '0' : '.');
        }
        ss << '\n';
    }
    cout << ss.str();
}
void clearScreen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
void initializeRandom(int (*cells)[COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cells[i][j] = rand() % 2; // Randomly set each cell to 0 or 1
        }
    }
}
#include "Helper.h"

void runWithCustomAliveCells(vector<int> index, bool editMode)
{
    // cells[2][1] = 1;
    // cells[3][2] = 1;
    // cells[1][3] = 1;
    // cells[2][3] = 1;
    // cells[3][3] = 1;
    int **board = initializeBoard();
    if (editMode)
    {
        if (index.size() > 2)
        {
            cout << "You can't enter more than one index at a time" << endl;
            gameOfLifeMenu();
            return;
        }
        board[index.at(0)][index.at(1)] = 1;
        printBoard(board);
    }
    else
    {
        while (true)
        {
            generateBoard(board);
            clearScreen();
            printBoard(board);
            usleep(90000);
        }
    }
}
void runWithRandomAliveCells()
{
    int **board = initializeBoard();
    initializeRandom(board);
    while (true)
    {
        generateBoard(board);
        clearScreen();
        printBoard(board);
        usleep(90000);
    }
}

void simulateGlider()
{
    int **board = initializeBoard();
    board[2][1] = 1;
    board[3][2] = 1;
    board[1][3] = 1;
    board[2][3] = 1;
    board[3][3] = 1;
    while (true)
    {
        generateBoard(board);
        clearScreen();
        printBoard(board);
        usleep(90000);
    }
}

void simulate2GliderMess()
{
    int **board = initializeBoard();
    board[5][5] = 1;
    board[5][7] = 1;
    board[6][7] = 1;
    board[6][6] = 1;
    board[4][7] = 1;
    board[7][16] = 1;
    board[9][15] = 1;
    board[9][16] = 1;
    board[8][15] = 1;
    board[8][14] = 1;
    while (true)
    {
        generateBoard(board);
        clearScreen();
        printBoard(board);
        usleep(90000);
    }
}

void simulateAcorn()
{
    int **board = initializeBoard();
    board[9][9] = 1;
    board[11][9] = 1;
    board[11][8] = 1;
    board[10][11] = 1;
    board[11][12] = 1;
    board[11][13] = 1;
    board[11][14] = 1;
    while (true)
    {
        generateBoard(board);
        clearScreen();
        printBoard(board);
        usleep(90000);
    }
}

void simulateAK47Reaction()
{
    int **board = initializeBoard();
    board[11][9] = 1;
    board[11][11] = 1;
    board[10][10] = 1;
    board[12][12] = 1;
    board[12][8] = 1;
    board[13][8] = 1;
    board[13][12] = 1;
    board[16][10] = 1;
    board[15][11] = 1;
    board[15][9] = 1;
    board[14][8] = 1;
    board[14][12] = 1;
    board[18][8] = 1;
    board[18][7] = 1;
    board[19][8] = 1;
    board[20][7] = 1;
    board[20][6] = 1;
    board[20][5] = 1;
    board[21][5] = 1;
    board[21][13] = 1;
    board[21][14] = 1;
    board[20][13] = 1;
    board[20][14] = 1;
    printBoard(board);
    cout << "Do you want to start?(y/n): ";
    char opt;
    cin >> opt;
    if(opt == 'y'){ while (true)
    {
        generateBoard(board);
        clearScreen();
        printBoard(board);
        usleep(90000);
    }}
   
}

int **initializeBoard()
{
    static int **cells = nullptr; // static pointer to ensure it is initialized only once
    if (!cells)
    {                            // Only initialize if cells is null
        cells = new int *[ROWS]; // ROWS pointers
        for (int i = 0; i < ROWS; ++i)
        {
            cells[i] = new int[COLS]{}; // Allocate COLS integers and initialize to 0
        }
    }

    // Return the pointer to the array of pointers
    return cells;
}
void generateBoard(int **cells)
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
                        // Wrap the edges
                        int row = (i + k + ROWS) % ROWS;
                        int col = (j + l + COLS) % COLS;
                        neighbours += cells[row][col];
                    }
                }
            }

            // Rules of Life
            if ((cells[i][j] == 1) && (neighbours < 2)) // Loneliness
                next[i][j] = 0;
            else if ((cells[i][j] == 1) && (neighbours > 3)) // Overpopulation
                next[i][j] = 0;
            else if ((cells[i][j] == 0) && (neighbours == 3)) // Birth
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

void printBoard(int **cells)
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
void initializeRandom(int **cells)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            cells[i][j] = rand() % 2; // Randomly set each cell to 0 or 1
        }
    }
}
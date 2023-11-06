#include "helper.h"

// Function to run the simulation with custom alive cells
void runWithCustomAliveCells(vector<int> index, bool editMode)
{
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
            startSimulation(board);
        }
    }
}

// Function to run the simulation with random alive cells
void runWithRandomAliveCells()
{
    int **board = initializeBoard();
    initializeRandom(board);
    printBoard(board);
    cout << "Do you want to start?(y/n): ";
    char opt;
    cin >> opt;
    if (opt == 'y')
    {
        while (true)
        {
            startSimulation(board);
        }
    }
}

// Function to simulate the glider pattern
void simulateGlider()
{
    int **board = initializeBoard();
    board[2][1] = 1;
    board[3][2] = 1;
    board[1][3] = 1;
    board[2][3] = 1;
    board[3][3] = 1;
    printBoard(board);
    cout << "Do you want to start?(y/n): ";
    char opt;
    cin >> opt;
    if (opt == 'y')
    {
        while (true)
        {
            startSimulation(board);
        }
    }
}

// Function to simulate the 2-glider mess pattern
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
    printBoard(board);
    cout << "Do you want to start?(y/n): ";
    char opt;
    cin >> opt;
    if (opt == 'y')
    {
        while (true)
        {
            startSimulation(board);
        }
    }
}

// Function to simulate the acorn pattern
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
    printBoard(board);
    cout << "Do you want to start?(y/n): ";
    char opt;
    cin >> opt;
    if (opt == 'y')
    {
        while (true)
        {
            startSimulation(board);
        }
    }
}

// Function to simulate the AK-47 reaction pattern
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
    if (opt == 'y' || 'Y')
    {
        while (true)
        {
            startSimulation(board);
        }
    }
}

// Function to start the simulation
void startSimulation(int **board)
{
    generateBoard(board);
    clearScreen();
    printBoard(board);
    cout << "To stop please press CTRL+C ";
    usleep(90000);
}

// Function to initialize the game board
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

// Function to generate the next state of the game board based on rules
void generateBoard(int **cells)
{
    int next[ROWS][COLS] = {};  // Initialize a new board for the next generation

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
                        // Wrap around the edges to consider cells on the opposite side
                        int row = (i + k + ROWS) % ROWS;
                        int col = (j + l + COLS) % COLS;
                        neighbours += cells[row][col];
                    }
                }
            }

            // Apply the rules of Conway's Game of Life
            if ((cells[i][j] == 1) && (neighbours < 2)) // Loneliness
                next[i][j] = 0;
            else if ((cells[i][j] == 1) && (neighbours > 3)) // Overpopulation
                next[i][j] = 0;
            else if ((cells[i][j] == 0) && (neighbours == 3)) // Birth
                next[i][j] = 1;
            else
                next[i][j] = cells[i][j];  // Cell remains the same

        }
    }

    // Copy the next generation board back to the original board
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            cells[i][j] = next[i][j];
        }
    }
}

// Function to print the game board to the console
void printBoard(int **cells)
{
    std::stringstream ss;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            ss << (cells[i][j] == 1 ? '0' : '.'); // Display '0' for live cells and '.' for dead cells
        }
        ss << '\n'; // Newline after each row
    }
    cout << ss.str(); // Print the board to the console
}

// Function to clear the console screen (platform-dependent)
void clearScreen()
{
#ifdef _WIN32
    std::system("cls");  // Clear the screen on Windows
#else
    std::system("clear");  // Clear the screen on Unix-like systems
#endif
}

// Function to initialize the game board with random cells
void initializeRandom(int **cells)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            cells[i][j] = rand() % 2; // Randomly set each cell to 0 (dead) or 1 (alive)
        }
    }
}

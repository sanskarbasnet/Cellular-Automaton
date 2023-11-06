#include "helper.h"

int main()
{
    menu(); // Entry point of the program, starts the menu
    return 0;
}

// Function to run cellular automaton with given ruleset and rule number
void runCellularAutomata(int ruleset[], int ruleNumber)
{
    vector<int> index = {ROW_SIZE / 2};
    int *cells = initialise(ROW_SIZE);                        // Initialize the cells
    populateFirstGeneration(index, cells);                    // Set initial alive cells
    printGeneration(cells, ruleset, GENERATIONS, ruleNumber); // Print generations
    free(cells);                                              // Free memory allocated for cells
}

// Function to run custom cellular automaton with given ruleset, generations, size, indices, and rule number
void runCustomisedCellularAutomaton(int ruleset[], int gens, int size, vector<int> index, int ruleNumber)
{
    int *cells = initialise(size);                     // Initialize the cells with custom size
    populateFirstGeneration(index, cells);             // Set initial alive cells
    printGeneration(cells, ruleset, gens, ruleNumber); // Print custom generations
    free(cells);                                       // Free memory allocated for cells
}

// Function to initialize an array of cells with zeros
int *initialise(int size)
{
    int *cells = (int *)malloc(sizeof(int) * size);

    for (int i = 0; i < ROW_SIZE; i++)
    {
        cells[i] = 0;
    }
    return cells;
}

// Function to populate the first generation with alive cells at specified indices
void populateFirstGeneration(vector<int> index, int *cells)
{
    for (int i = 0; i < index.size(); i++)
    {
        cells[index.at(i)] = 1;
    }
}

// Function to print the generations of cells
void printGeneration(int *cells, int ruleset[], int gens, int ruleNumber)
{
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_U16TEXT); // Set console output mode for Unicode characters on Windows
#else
    std::locale::global(std::locale("en_US.utf8")); // Set the locale for UTF-8 characters on Unix-like systems
#endif
    string board;
    for (int gen = 0; gen < gens; gen++)
    {
        if (gen <= 9)
            wcout << L' ';

        wcout << gen;
        for (int i = 0; i < ROW_SIZE; i++)
        {
            if (cells[i] == 1)
            {
                wcout << L'█'; // Display '█' for live cells
                board += '0';
            }
            else
            {
                wcout << L' '; // Display space for dead cells
                board += '.';
            }
        }
        board += "\n";
        wcout << endl;
        generate(cells, ruleset); // Generate the next generation
    }
    saveToFile(board, ruleNumber); // Save the board state to a file
}

// Function to generate the next generation of cells based on rules
void generate(int *cells, int ruleset[])
{
    int nextgen[ROW_SIZE];
    nextgen[0] = cells[0];
    nextgen[ROW_SIZE - 1] = cells[ROW_SIZE - 1];

    for (int i = 1; i < (ROW_SIZE - 1); i++)
    {
        int left = cells[i - 1];
        int right = cells[i + 1];
        int me = cells[i];
        nextgen[i] = rules(left, me, right, ruleset); // Apply rules to determine cell state
    }
    for (int i = 0; i < ROW_SIZE; i++)
    {
        cells[i] = nextgen[i];
    }
}

// Function to convert a decimal number to an 8-bit binary representation
void decimalToBinary(int decimal, int binary[8])
{
    // Ensure the number is within the 8-bit range
    if (decimal < 0 || decimal > 255)
    {
        std::cerr << "Number out of 8-bit range." << std::endl;
        return; // Exit the function
    }

    // Fill the binary array with the corresponding binary digits
    for (int i = 7; i >= 0; --i)
    {
        binary[i] = decimal % 2;
        decimal /= 2;
    }
}

// Function to apply rules to determine the next state of a cell
int rules(int left, int me, int right, int ruleset[])
{
    // Apply rules based on the state of neighboring cells
    if (left == 1 && me == 1 && right == 1)
        return ruleset[0];
    if (left == 1 && me == 1 && right == 0)
        return ruleset[1];
    if (left == 1 && me == 0 && right == 1)
        return ruleset[2];
    if (left == 1 && me == 0 && right == 0)
        return ruleset[3];
    if (left == 0 && me == 1 && right == 1)
        return ruleset[4];
    if (left == 0 && me == 1 && right == 0)
        return ruleset[5];
    if (left == 0 && me == 0 && right == 1)
        return ruleset[6];
    if (left == 0 && me == 0 && right == 0)
        return ruleset[7];

    return 0;
}

// Function to save the current board state to a file
void saveToFile(string &boardState, int ruleNumber)
{
    // Convert the rule number to a string and use it as the filename
    std::string filename = "Rule" + std::to_string(ruleNumber) + ".txt";

    std::ofstream out(filename, std::ios::out);

    if (!out.is_open())
    {
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return;
    }

    out << boardState; // Write the board state to the file

    // Check for any errors in writing to the file
    if (out.fail())
    {
        std::cerr << "Failed to write to the file." << std::endl;
    }

    // Close the file stream
    out.close();
}

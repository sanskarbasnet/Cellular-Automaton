#include "Helper.h"

int main()
{
    menu();
    return 0;
}

void runCellularAutomata(int ruleset[], int ruleNumber)
{
    vector<int> index = {ROW_SIZE / 2};
    int *cells = initialise(ROW_SIZE);
    populateFirstGeneration(index, cells);
    printGeneration(cells, ruleset, GENERATIONS, ruleNumber);
    free(cells);
}

void runCustomisedCellularAutomaton(int ruleset[], int gens, int size, vector<int> index, int ruleNumber)
{
    int *cells = initialise(size);
    populateFirstGeneration(index, cells);
    printGeneration(cells, ruleset, gens, ruleNumber);
    free(cells);
}

int *initialise(int size)
{
    int *cells = (int *)malloc(sizeof(int) * size);

    for (int i = 0; i < ROW_SIZE; i++)
    {
        cells[i] = 0;
    }
    return cells;
}
void populateFirstGeneration(vector<int> index, int *cells)
{
    for (int i = 0; i < index.size(); i++)
    {
        cells[index.at(i)] = 1;
    }
}

void printGeneration(int *cells, int ruleset[], int gens, int ruleNumber)
{
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_U16TEXT);
#else
    std::locale::global(std::locale("en_US.utf8"));
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
                wcout << L'█';
                board += '0';
            }
            else
            {
                wcout << L' ';
                board += '.';
            }
        }
        board += "\n";
        wcout << endl;
        generate(cells, ruleset);
    }
    saveToFile(board, ruleNumber);
}
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
        nextgen[i] = rules(left, me, right, ruleset);
    }
    for (int i = 0; i < ROW_SIZE; i++)
    {
        cells[i] = nextgen[i];
    }
}

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

int rules(int left, int me, int right, int ruleset[])
{
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
    
    out << boardState;

    // Check for any errors in writing to the file
    if (out.fail())
    {
        std::cerr << "Failed to write to the file." << std::endl;
    }

    // Close the file stream
    out.close();
}

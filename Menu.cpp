#include "Helper.h"

void menu()
{
    int choice;
    cout << "1. Run cellular automaton" << endl;
    cout << "2. Game of life" << endl;
    cout << "3. Exit" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        cellularAutomatonMenu();
        break;
    case 2:
        gameOfLifeMenu();
        break;
    case 3:
        exit(1);
    default:
        cout << "Please enter a valid option." << endl;
        menu();
        break;
    }
}

void cellularAutomatonMenu()
{
    int opt;

    cout << "[1]. Run with default settings" << endl;
    cout << "[2]. Customise settings" << endl;
    cout << "Enter an option (1-2): ";
    cin >> opt;

    switch (opt)
    {
    case 1:
    {
        int rule;
        do
        {
            cout << "Enter a rule to print(0-255): ";
            cin >> rule;
            if (rule < 0 || rule > 255)
                cout << "Invalid Rule. Enter a Number between 0 and 255";
        } while (rule < 0 || rule > 255);
        int ruleset[8] = {0};
        decimalToBinary(rule, ruleset);
        runCellularAutomata(ruleset, rule);
        break;
    }
    case 2:
    {
        int rule;
        int size;
        int gens;
        string index;
        cout << "Enter the size of parent generation: ";
        cin >> size;
        cout << "Enter the number of generations to print: ";
        cin >> gens;
        if (size < 0 || gens < 0)
        {
            cout << "Negative Value not allowed" << endl;
            cellularAutomatonMenu();
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter the index/indices of cells to make alive(Eg. 0 1 10 15): ";
        getline(cin, index);
        do
        {
            cout << "Enter a rule to print(0-255): ";
            cin >> rule;
            if (rule < 0 || rule > 255)
                cout << "Invalid Rule. Enter a Number between 0 and 255";
        } while (rule < 0 || rule > 255);
        int ruleset[8] = {0};
        decimalToBinary(rule, ruleset);
        cout << endl;
        runCustomisedCellularAutomaton(ruleset, gens, size, parseAndStoreNumbers(index, size, size), rule);
    }
    default:
        cout << "Please enter a valid option" << endl;
        cellularAutomatonMenu();
        break;
    }
}

void gameOfLifeMenu()
{
    int opt;

    cout << "[1]. Simulate presets" << endl;
    cout << "[2]. Choose cells to make alive" << endl;
    cout << "Enter an option (1-2): ";
    cin >> opt;

    switch (opt)
    {
    case 1:
    {
        int choice;
        cout << "[1]. Random Alive Cells" << endl;
        cout << "[2]. Glider" << endl;
        cout << "[3]. 2-glider mess" << endl;
        cout << "[4]. Acorn" << endl;
        cout << "[5]. AK47 Reaction" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            runWithRandomAliveCells();
            break;
        case 2:
            simulateGlider();
            break;
        case 3:
            simulate2GliderMess();
            break;

        case 4:
            simulateAcorn();
            break;
        case 5:
            simulateAK47Reaction();
            break;
        default:
            break;
        }
    }
    case 2:
    {
        bool editMode = true;
        string index;
        char opt;
        while (true)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter index of a cell to make it alive(0-30 0-100)(Eg. 10 45): ";
            getline(cin, index);
            runWithCustomAliveCells(parseAndStoreNumbers(index, ROWS, COLS), editMode);
            cout << "Do you want to continue editing? (y/n): ";
            cin >> opt;
            if (opt == 'n' || opt == 'N')
                break;
        }
        runWithCustomAliveCells({}, !editMode);
    }
    default:
        cout << "Please enter a valid option" << endl;
        gameOfLifeMenu();
        break;
    }
}
vector<int> parseAndStoreNumbers(const string &input, int max_size, int max_size2)
{
    std::vector<int> indexVector;
    std::stringstream ss(input);
    int num;
    while (ss >> num)
    {
        if (num >= 0 && num < max_size && num < max_size2)
        {
            indexVector.push_back(num);
        }
        else
        {
            cout << "Invalid input" << endl;
            cout << "Make sure you enter indices between 0 and permitted size" << endl;
            cellularAutomatonMenu();
        }
    }
    return indexVector;
}
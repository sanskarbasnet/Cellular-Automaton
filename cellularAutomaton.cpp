#include <iostream>
#include <cstdlib>
#include <locale>
#include <io.h>
#include <fcntl.h>
using namespace std;

const int ROW_SIZE = 60;
const int GENERATIONS = 45;

void menu();
void generate(int *cells, int ruleset[]);
int rules(int left, int me, int right, int ruleset[]);

int main()
{
    //menu();
    int ruleset[] = {0, 0, 1, 1, 1, 1, 1, 0};
    int *cells = (int *)malloc(sizeof(int) * ROW_SIZE);

    for (int i = 0; i < ROW_SIZE; i++)
    {
        if (i == ROW_SIZE / 2)
        {
            cells[i] = 1;
        }
        else
        {
            cells[i] = 0;
        }
    }

#ifdef _WIN32
    _setmode(_fileno(stdout), _O_U16TEXT);
#else
    std::locale::global(std::locale("en_US.utf8"));
#endif

    for (int gen = 0; gen < GENERATIONS; gen++)
    {
        if (gen <= 9)
            wcout << L' ';
        wcout << gen;
        for (int i = 0; i < ROW_SIZE; i++)
        {
            if (cells[i] == 1)
            {
                wcout << L'█';
            }
            else
            {
                wcout << L' ';
            }
        }
        wcout << endl;
        generate(cells, ruleset);
    }

    free(cells);
    return 0;
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

void menu(){
    int choice;
    cout << "1. Run cellular automaton" << endl;
    cout << "2. Game of life" << endl;
    cout << "3. Exit" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        void generate(int *cells, int ruleset[]);
        break;
    case 2:
        //testing
        break;
    case 3: 
        exit(1);
    default:
        cout << "Please enter again";
        menu();
        break;
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

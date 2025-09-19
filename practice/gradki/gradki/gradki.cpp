#include <iostream>
#include <fstream>

using namespace std;
const int Max = 200;
char field[Max][Max];
int m, n, countBeds = 0;

void Metka(int i, int j)
{
    if (field[i][j] == '#')
    {
        field[i][j] = '.';
        Metka(i + 1, j);
        Metka(i - 1, j);
        Metka(i, j + 1);
        Metka(i, j - 1);
    }
}

int main(int argc, char* argv[])
{
    ifstream input(argv[1]);
    if (!input.is_open())
    {
        cout << "Failed to open " << argv[1] << " for reading\n";
        return 1;
    }
    ofstream output(argv[2]);
    if (!output.is_open())
    {
        cout << "Failed to open " << argv[2] << " for writing\n";
        return 1;
    }
    int i, j;
    input >> m;
    input >> n;
    for (int i = 0; i < m + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            field[i][j] = '.';
        }
    }
    for (i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            input >> field[i][j];
        }
    }
    for (i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++)
        {
            if (field[i][j] == '#')
            {
                countBeds++;
                Metka(i, j);
            }
        }
    }
  
    output << countBeds <<endl;
    return 0;
}

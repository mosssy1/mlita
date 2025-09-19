/*
19.1. Кроссворд 2 (3) 
Кроссворд размещен в квадрате. Строки и столбцы квадрата нумеруются сверху вниз и слева направо, начиная с 1.
Поля для слов располагаются горизонтально либо вертикально и задаются путем указания координат начальной и 
конечной клеток. Какая-либо сортировка при задании полей отсутствует. Два пересекающихся слова могут располагаться
как на одной горизонтали либо вертикали, так и перпендикулярно друг другу. Подсчитать количество занятых клеток кроссворда.
Ввод. В первой строке файла INPUT.TXT заданы размер квадрата M (1 ≤ M ≤ 50) и количество слов кроссворда N (1 ≤ N ≤ 20). 
В следующих N строках указываются координаты (ai, bi) начальной и конечной клеток очередного слова (1 ≤ ai, bi ≤ M). 
Вывод. В единственной строке выходного файла OUTPUT.TXT должно содержаться общее количество занятых клеток кроссворда.
Пример
Ввод
10 2
2 3 3 3
1 3 4 3 
Вывод
4

Комиссарова Арина ПС-21
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <optional>

using namespace std;

struct Args
{
    string inputFileName;
    string outputFileName;
};
optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }

    ifstream input;
    input.open(args->inputFileName);

    if (!input.is_open())
    {
        cout << "Failed to open '" << args->inputFileName << "' for reading\n";
        return 1;
    }

    int m, n;
    input >> m >> n;
    vector<vector<int>> crossword(m, vector<int>(m, 0));

    for (int i = 0; i < n; i++) 
    {
        int x1, y1, x2, y2;
        input >> x1 >> y1 >> x2 >> y2;

        for (int x = min(x1, x2); x <= max(x1, x2); x++) 
        {
            for (int y = min(y1, y2); y <= max(y1, y2); y++) 
            {
                crossword[x - 1][y - 1] = 1;
            }
        }
    }

    input.close();

    int occupiedCells = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (crossword[i][j] == 1) {
                occupiedCells++;
            }
        }
    }

    ofstream output;
    output.open(args->outputFileName);

    if (!output.is_open())
    {
        cout << "Failed to open '" << args->outputFileName << "' for writing\n";
        return 1;
    }
    output << occupiedCells << endl;
    output.close();

    return 0;

}

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Invalid arguments count\n";
        return nullopt;
    }

    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    return args;
}


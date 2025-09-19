/*
19.24 Домино (2)
Найти количество вариантов покрытия прямоугольника 2×N прямоугольниками 2×1. Покрытия, которые преобразуются друг в друга симметриями, считать различными.
Ввод. В единственной строке входного файла INPUT.TXT задано значение N (1 ≤ N ≤ 20).
Вывод. В единственной строке выходного файла OUTPUT.TXT должно содержаться количество вариантов покрытия прямоугольника.
Пример
Ввод
5
Вывод
8

Комиссарова Арина ПС-21
*/

#include <iostream>
#include <fstream>
#include <optional>
#include <vector>

using namespace std;

struct Args
{
    string inputFileName;
    string outputFileName;
};

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

int CountCoverings(int n) 
{
    vector<int> countVariants(n + 1);
    countVariants[0] = 1;
    countVariants[1] = 1;

    for (int i = 2; i <= n; i++) 
    {
        countVariants[i] = countVariants[i - 1] + countVariants[i - 2];
    }

    return countVariants[n];
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }

    ifstream input(args->inputFileName);
    if (!input.is_open())
    {
        cout << "Failed to open '" << args->inputFileName << "' for reading\n";
        return 1;
    }

    int n;
    input >> n;
    input.close();

    ofstream output(args->outputFileName);
    if (!output.is_open())
    {
        cout << "Failed to open '" << args->outputFileName << "' for writing\n";
        return 1;
    }

    int count = CountCoverings(n);
    output << count << endl;
    output.close();

    return 0;
}

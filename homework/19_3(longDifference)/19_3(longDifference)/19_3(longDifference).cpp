/*19.3. Длинная разность (4)
Заданы два целых положительных числа.Требуется найти их разность.Запрещается использование библиотек длинной арифметики.
Ввод.В первых двух строках файла INPUT.TXT содержатся  два  целых  числа  M  и  N(1 ≤ N < M  ≤ 10^200).
Вывод.В единственной строке выходного файла OUTPUT.TXT необходимо вывести разность M – N.
Примеры
    Ввод 1                   Ввод 2
    123456787654321          1000000000000000
    35                       1
    Вывод 1                  Вывод 2
    123456787654286          999999999999999

Комиссарова Арина ПС-21
*/
#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <algorithm>

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

    string m, n;
    getline(input, m);
    getline(input, n);

    int charDiff = max(m.length(), n.length());
    m = string(charDiff - m.length(), '0') + m;
    n = string(charDiff - n.length(), '0') + n;

    string result;
    int take = 0;
    for (int i = charDiff - 1; i >= 0; i--) 
    {
        int diff = m[i] - n[i] - take;
        if (diff < 0) 
        {
            diff += 10;
            take = 1;
        }
        else 
        {
            take = 0;
        }
        result = to_string(diff) + result;
    }

    while (result.length() > 1 && result[0] == '0') 
    {
        result.erase(0, 1);
    }

    if (result.empty()) 
    {
        result = "0";
    }

    ofstream output(args->outputFileName);
    if (!output.is_open())
    {
        cout << "Failed to open '" << args->outputFileName << "' for writing\n";
        return 1;
    }

    output << result;
    input.close();
    output.close();
    return 0;
}

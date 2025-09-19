/*10.2. Последовательность 2 (5)
Каждый член последовательности десятичных цифр d1, d2, d3..., начиная с четвёртого, вычисляется по формуле
di  = (di-3 + di-2  + di-1) mod x. По заданным d1, d2, d3, x найти N-й член последовательности.
Ввод из файла INPUT.TXT. В первой строке находятся d1, d2, d3, x, разделённые пробелами,
во второй - число N.
Вывод в файл OUTPUT.TXT. Вывести одну цифру - dN.
Ограничения: 1 ≤ N ≤ 10^18, 2 ≤  x ≤ 10, время 1 с.
Примеры
Ввод 1    Ввод 2
1 4 8 10  5 5 5 10
4         1000000000000000
Вывод 1   Вывод 2
3         5

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
    int d1, d2, d3, x;
    long long n;
    input >> d1 >> d2 >> d3 >> x >> n;
    input.close();

    ofstream output(args->outputFileName);
    if (!output.is_open())
    {
        cout << "Failed to open '" << args->outputFileName << "' for writing\n";
        return 1;
    }

    vector<long> sequence = { d1, d2, d3 };

    bool doIt = true;
    int result = 0;

    while (doIt)
    {
        int nextNumber = (sequence[sequence.size() - 3] + sequence[sequence.size() - 2] + sequence[sequence.size() - 1]) % x;
        sequence.push_back(nextNumber);

        if (sequence[0] == sequence[sequence.size() - 3] && sequence[1] == sequence[sequence.size() - 2] && sequence[2] == sequence[sequence.size() - 1])
        {
            if (sequence.size() == 4)
            {
                doIt = false;
                result = sequence[sequence.size() - 1];
            }
            else
            {
                sequence.resize(sequence.size() - 3);
                long trueIndex = n % sequence.size();
                doIt = false;
                result = sequence[trueIndex - 1];
            }
        }
        else if (sequence[sequence.size() - 3] == 0 && sequence[sequence.size() - 2] == 0 && sequence[sequence.size() - 1] == 0)
        {
            doIt = false;
            result = 0;
        }

        if (doIt && (sequence.size() - 1) == n)
        {
            doIt = false;
            result = sequence[n - 1];
        }
    }
    output << result << endl;
    output.close();
    return 0;
}







/*Король Камбузии с детства боится несчастливых арифметических прогрессий с разностью 13. Однажды ему представили список расходов на нужды подданных, состоящий из N чисел. Король потребовал оставить только такую начальную часть списка, в которой не скрывается несчастливая арифметическая прогрессия. Либеральная общественность, считаясь с мнением короля, настаивает, тем не менее, на сохранении как можно большей части списка. Найти максимальное значение K такое, что из первых K чисел списка невозможно выделить M чисел, следующих в порядке их нахождения в списке и образующих последовательные члены несчастливой арифметической прогрессии. Выдать члены первой обнаруженной несчастливой прогрессии. 
Ввод из файла INPUT.TXT. Первая строка содержит два целых положительных числа N и M, разделенных пробелом: N – количество чисел в списке, а M – недопустимое число членов прогрессии. Вторая строка содержит список расходов в виде целых положительных чисел. 
Ограничения: 2 ≤ N, M ≤ 5000, 1 ≤ Xi ≤ 65000, время 1 с.
Вывод в файл OUTPUT.TXT. В первой строке выводится единственное число K- максимальное количество начальных чисел списка, не содержащих в качестве подсписка M последовательных членов несчастливой арифметической прогрессии. Во второй строке выводятся через пробел члены первой обнаруженной несчастливой прогрессии. Если ее не обнаружено, вывести No.
Пример 
Ввод
9 3
5 9 3 22 16 19 35 7 29
Вывод
6
9 22 35
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

vector<int> FindUnluckyProgression(const vector<int>& nums, int M)
{
    int N = static_cast<int>(nums.size());
    vector<vector<int>> dp(N, vector<int>(M, 0));

    vector<int> result;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (j == 0)
            {
                dp[i][j] = 1;
            }
            else if (i - j >= 0 && nums[i] - nums[i - 1] != nums[i - j] - nums[i - j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = 1;
            }

            if (dp[i][j] == M)
            {
                for (int k = i - j; k <= i; k++)
                {
                    result.push_back(nums[k]);
                }
                return result;
            }
        }
    }

    return result;
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

    ofstream output(args->outputFileName);
    if (!output.is_open())
    {
        cout << "Failed to open '" << args->outputFileName << "' for writing\n";
        return 1;
    }

    // чтение входных данных
    int N, M;
    input >> N >> M;
    if (N < 2 || N > 5000 || M < 1 || M > N)
    {
        cout << "Invalid input values\n";
        return 1;
    }

    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        input >> nums[i];
        if (nums[i] < 1 || nums[i] > 65000)
        {
            cout << "Invalid input values\n";
            return 1;
        }
    }
    input.close();

    // поиск несчастливой прогрессии
    vector<int> unluckyProgression = FindUnluckyProgression(nums, M);

    // вывод результатов
    if (unluckyProgression.empty())
    {
        output << "No" << endl;
    }
    else
    {
        output << unluckyProgression.size() << endl;
        for (int i = 0; i < unluckyProgression.size(); i++)
        {
            output << unluckyProgression[i] << " ";
        }
        output << endl;
    }
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

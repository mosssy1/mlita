/*  1.2. Колорадский жук (4)
Прямоугольный садовый участок длиной M ×N метров (1≤ M, N ≤5) разбит на квадраты со стороной 1 метр.
На этом участке вскопана грядка картошки. Грядкой является связанное множество квадратов.  
Иными словами, из любого квадрата этой грядки можно попасть в любой другой квадрат этой же грядки, 
последовательно переходя по грядке из квадрата в квадрат через их общую сторону.
В некоторых квадратах грядки растут кусты картошки. Колорадский жук прилетел на один из кустов. 
Съев все листья, он переходит через общую сторону к какому-либо соседнему свежему кусту той же грядки.
Жук не возвращается к тому кусту, на котором он уже был, и не приходит в те квадраты, где картошка
не посажена. Определить наибольшее количество кустов картошки, которые сможет съесть колорадский жук.
Ввод. В первой строке файла INPUT.TXT находятся числа M и N через пробел. Далее идут M строк по N 
символов. Квадраты грядки с кустами картошки обозначаются символами '#', свободные квадраты – 
символами '.'.
Вывод. В единственной строке файла OUTPUT.TXT вывести одно число - наибольшее возможное количество
съеденных кустов картошки.
Пример 
Ввод
3 4
####
.#..
.###
Вывод
7

*/
//Комиссарова Арина ПС-21

#include <iostream>
#include <fstream>
#include <algorithm>
#include <optional>

using namespace std;

const int MAX_N = 50;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int m, n;
char garden[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int maxCount = 0;


struct Args
{
    string inputFileName;
    string outputFileName;
};
optional<Args> ParseArgs(int argc, char* argv[]);

void Backward(int x, int y, int count) {
    maxCount = max(maxCount, count);
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && garden[nx][ny] == '#' && !visited[nx][ny]) {
            visited[nx][ny] = true;
            count++;
            Backward(nx, ny, count);
            visited[nx][ny] = false;
            count--;
        }
    }
}

int main(int argc, char* argv[]) {

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

    input >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            input >> garden[i][j];
        }
    }
    input.close();

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (garden[i][j] == '#') {
                visited[i][j] = true;
                int count = 1;
                Backward(i, j, count);
                visited[i][j] = false;
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
    output << maxCount << endl;
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

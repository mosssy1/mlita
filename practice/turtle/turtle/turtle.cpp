#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

const int MAXN = 100;
int M, N;
int a[MAXN][MAXN], dp[MAXN][MAXN], path[MAXN][MAXN];

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
    input >> M;
    input >> N;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            input >> a[i][j];
        }
    }

    // инициализация первой строки и первого столбца
    dp[0][0] = a[0][0];
    for (int j = 1; j < N; j++) {
        dp[0][j] = dp[0][j - 1] + a[0][j];
    }
    for (int i = 1; i < M; i++) {
        dp[i][0] = dp[i - 1][0] + a[i][0];
    }

    // заполнение массива dp и path
    for (int i = 1; i < M; i++) {
        for (int j = 1; j < N; j++) {
            int from_top = dp[i - 1][j];
            int from_left = dp[i][j - 1];
            if (from_top < from_left) {
                dp[i][j] = from_top + a[i][j];
            }
            else {
                dp[i][j] = from_left + a[i][j];
            }
        }
    }

    // построение пути с минимальной длиной
    int i = M - 1, j = N - 1;
    while (i != 0 && j != 0) {
        path[i][j] = 1;
        if (i == 0) {
            j--;
        }
        else if (j == 0) {
            i--;
        }
        else {
            int from_top = dp[i - 1][j];
            int from_left = dp[i][j - 1];
            if (from_top < from_left) {
                i--;
            }
            else {
                j--;
            }
        }
    }
    path[0][0] = 1;

    // выводим кратчайший путь и его длин
    i = 0, j = 0;
    while (i != M - 1  && j != N - 1) {
        output << a[i][j] << " -> ";
        if (path[i + 1][j]) {
            i++;
        }
        else {
            j++;
        }
    }
    output << a[M - 1][N - 1] << endl;
    output << "Длина кратчайшего пути: " << dp[M - 1][N - 1] << endl;

    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <optional>


using namespace std;

struct Args
{
    string inputFileName;
    string outputFileName;
};

optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[]) {

    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    }
    
    ifstream input(args->inputFileName);
    if (!input.is_open())
    {
        cout << "Failed to open " << argv[1] << " for reading\n";
        return 1;
    }
    ofstream output(args->outputFileName);
    if (!output.is_open())
    {
        cout << "Failed to open " << argv[2] << " for writing\n";
        return 1;
    }

    int n, m;
    input >> n >> m;

    vector<vector<int>> field(n, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        int x, y;
        input >> x >> y;
        field[x - 1][y - 1] = 1;
    }

    queue<pair<int, int>> infection;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (field[i][j] == 1) {
                infection.push(make_pair(i, j));
            }
        }
    }

    int days = 0;
    while (!infection.empty()) {
        int size = infection.size();
        for (int i = 0; i < size; i++) {
            int x = infection.front().first;
            int y = infection.front().second;
            infection.pop();
            if (x > 0 && field[x - 1][y] == 0) {
                field[x - 1][y] = 1;
                infection.push(make_pair(x - 1, y));
            }
            if (y > 0 && field[x][y - 1] == 0) {
                field[x][y - 1] = 1;
                infection.push(make_pair(x, y - 1));
            }
            if (x < n - 1 && field[x + 1][y] == 0) {
                field[x + 1][y] = 1;
                infection.push(make_pair(x + 1, y));
            }
            if (y < n - 1 && field[x][y + 1] == 0) {
                field[x][y + 1] = 1;
                infection.push(make_pair(x, y + 1));
            }
        }
        days++;
    }

    output << days - 1 << endl;

    return 0;
}

optional<Args> ParseArgs(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Invalid arguments count\n";
        return nullopt;
    }

    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    return args;
}

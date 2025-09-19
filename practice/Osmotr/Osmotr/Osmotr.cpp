#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <optional>

using namespace std;

const int MAXN = 100;

vector<int> graph[MAXN + 1];
int in_degree[MAXN + 1];

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
        int NumOfDocs;
        input >> NumOfDocs;

        for (int i = 1; i <= NumOfDocs; i++) {
            int j;
            input >> j;

            for (int l = 0; l < j; l++) {
                int v;
                input >> v;

                graph[v].push_back(i);
                in_degree[i]++;
            }
        }

        queue<int> queueToDocs;
        for (int i = 1; i <= NumOfDocs; i++) {
            if (in_degree[i] == 0) {
                queueToDocs.push(i);
            }
        }

        vector<int> vertexOrder;
        while (!queueToDocs.empty()) {
            int v = queueToDocs.front();
            queueToDocs.pop();

            vertexOrder.push_back(v);

            for (int i = 0; i < graph[v].size(); i++) {
                int u = graph[v][i];
                in_degree[u]--;
                if (in_degree[u] == 0) {
                    queueToDocs.push(u);
                }
            }
        }

        if (vertexOrder.size() != NumOfDocs) {
            output << "NO" << endl;
        }
        else {
            output << "YES" << endl;
            for (int i = 0; i < vertexOrder.size(); i++) {
                output << vertexOrder[i] << endl;
            }
        }

        return 0;
 }
   
optional<Args> ParseArgs(int argc, char* argv[]){
    if (argc != 3){
        cout << "Invalid arguments count\n";
        return nullopt;
    }

    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    return args;
}
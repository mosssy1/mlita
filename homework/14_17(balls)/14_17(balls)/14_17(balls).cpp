/*
14.17. Шары (5)
По горизонтально расположенному желобу бесконечной длины катятся с одинаковой скоростью
N металлических шаров (1 ≤ N ≤ 10^5). Некоторые шары катятся вправо, некоторые влево.
Сталкиваясь, шары испытывают абсолютно упругое соударение (то есть меняют направление движения, сохраняя скорость).
Зная расположение шаров в желобе  и направление их движения, сосчитать количество столкновений (соударений) пар шаров.
Ввод. Входной файл INPUT.TXT содержит одну строку. В ней символами «>» и «<» указаны направления движения шаров.
Вывод. В единственной строке файла OUTPUT.TXT требуется вывести число соударений.
Ввод. Входной файл INPUT.TXT содержит одну строку. В ней символами «>» и «<» указаны направления движения шаров.
Вывод. В единственной строке файла OUTPUT.TXT требуется вывести число соударений.
Ограничение. Затраты оперативной памяти не должны превышать 1 Мгб.
Примеры
Ввод 1        Ввод 2
7             5
>><>>><       <<<>>
Вывод 1       Вывод 2
7             0

*/
//Комиссарова Арина ПС-21
#include <iostream>
#include <fstream>
#include <string>
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

	long int count = 0;
    long int k = 0;
	char ch;
	while (input.get(ch)) {
		if (ch == '>') {
			k++;
		}
		else if (ch == '<') {
			count += k;
		}
	}

	ofstream output;
	output.open(args->outputFileName);

	if (!output.is_open())
	{
		cout << "Failed to open '" << args->outputFileName << "' for writing\n";
		return 1;
	}
	output << count << endl;
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
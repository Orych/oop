#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <optional>
#include <string>

using namespace std;


// Функция для считывания массива чисел с плавающей запятой из файла
std::vector<double> ReadArrayFromFile(const std::string& fileName)
{
    std::vector<double> array;
    double number;
    std::ifstream inputFile(fileName);
    while (inputFile >> number)
    {
        array.push_back(number);
    }
    return array;
}

// Функция для обработки массива: прибавление среднего арифметического положительных элементов
void ProcessArray(std::vector<double>& array)
{
    // Находим сумму положительных элементов
    double positiveSum = std::accumulate(array.begin(), array.end(), 0.0, [](double sum, double element) {
        return (element > 0) ? sum + element : sum;
    });

    // Вычисляем среднее арифметическое положительных элементов
    double positiveAverage = positiveSum / std::count_if(array.begin(), array.end(), [](double element) {
        return element > 0;
    });

    for (double& element : array)
    {
        element += positiveAverage;
    }
}

// Функция для сортировки массива в порядке возрастания
void SortArray(std::vector<double>& array)
{
    std::sort(array.begin(), array.end());
}

// Функция для вывода массива с заданной точностью
void PrintArray(const std::vector<double>& array, int precision)
{
    std::cout << std::fixed << std::setprecision(precision);
    for (const double& element : array)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

struct Args
{
    string input;
};

optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{

    auto args = ParseArgs(argc, argv);

    std::vector<double> array = ReadArrayFromFile(args->input);

    ProcessArray(array);

    SortArray(array);

    PrintArray(array, 2);

    return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage: primeNumbers.exe <upper bound>\n";
        return nullopt;
    }

    Args args;
    args.input = argv[1];
    return args;
}

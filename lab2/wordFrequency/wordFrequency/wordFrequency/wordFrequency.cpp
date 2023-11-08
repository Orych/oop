#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <optional>

using namespace std;

struct Args
{
    string input;
};

optional<Args> ParseArgs(int argc, char* argv[]);

std::map<std::string, int> CountWordFrequency(const std::string& fileName) 
{
    std::map<std::string, int> wordFrequency;
    std::string word;

    // Открытие файла для чтения
    std::ifstream inputFile(fileName);
    if (!inputFile) 
    {
        std::cerr << "Не удалось открыть файл." << std::endl;
        return wordFrequency;
    }

    // Чтение слов из файла до достижения конца файла (EOF)
    while (inputFile >> word) 
    {
        // Инкрементируем счетчик частоты встречаемости слова
        wordFrequency[word]++;
    }

    // Закрытие файла
    inputFile.close();

    return wordFrequency;
}

void PrintWordFrequency(const std::map<std::string, int>& wordFrequency) 
{
    // Вывод частоты встречаемости слов
    for (const auto& pair : wordFrequency) 
    {
        std::cout << pair.first << "- " << pair.second << std::endl;
    }
}

int main(int argc, char* argv[]) 
{
    auto args = ParseArgs(argc, argv);

    // Подсчет частоты встречаемости слов
    std::map<std::string, int> wordFrequency = CountWordFrequency(args->input);

    // Вывод частоты встречаемости слов
    PrintWordFrequency(wordFrequency);

    return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage: wordFrequency.exe <input.txt> <output.txt>\n";
        return nullopt;
    }

    Args args;
    args.input = argv[1];
    return args;
}

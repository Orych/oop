#include <iostream>
#include <string>
#include <optional>

using namespace std;

int CountBits(int byte) 
{
    int count = 0;
    while (byte != 0) 
    {
        count += byte & 1;
        byte >>= 1;
    }
    return count;
}

struct Args
{
    string number;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage calcbits.exe /number/\n";
        return nullopt;
    }
    Args args;
    args.number = argv[1];
    return args;
}

int main(int argc, char* argv[]) 
{
    auto args = ParseArgs(argc, argv);

    if (!args) 
    {
        return 1;
    }

    int byte = stoi(args->number);
    if (byte < 0 || byte > 255) 
    {
        cout << "Incorrect input for byte. Valid range: 0-255" << endl;
        return 1;
    }

    int bitCount = CountBits(byte);
    cout << bitCount << endl;

    return 0;
}

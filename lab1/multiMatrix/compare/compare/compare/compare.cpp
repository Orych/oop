#include <iostream>
#include <fstream>
#include <string>
#include <optional>


using namespace std;

bool OpenFile(ifstream& file, const string& fileName) {
    file.open(fileName);
    if (!file.is_open()) {
        cerr << "Unable to open " << fileName << endl;
        return false;
    }
    return true;
}

bool CompareFiles(const string& file1Name, const string& file2Name) {
    ifstream file1, file2;
    if (!OpenFile(file1, file1Name) || !OpenFile(file2, file2Name)) {
        return false;
    }

    string line1, line2;
    int lineNumber = 1;
    bool eof1 = false;
    bool eof2 = false;

    while (!(eof1) && !(eof2)) {
        bool eof1 = !getline(file1, line1);
        bool eof2 = !getline(file2, line2);

        if (eof1 && eof2) {
            cout << "Files are equal" << endl;
            return true;
        }

        if (eof1 || eof2 || line1 != line2) {
            cout << "Files are different. Line number is " << lineNumber << endl;
            return false;
        }

        ++lineNumber;
    }
}

struct Args
{
    string inputFileNameFirst;
    string inputFileNameSecond;
};

optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    }

    string file1Name = args->inputFileNameFirst;
    string file2Name = args->inputFileNameSecond;

    if (!CompareFiles(file1Name, file2Name)) {
        return 1;
    }

    return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage: Replace.exe <input file name> <output file name> <search string> <replace string>\n";
        return nullopt;
    }

    Args args;
    args.inputFileNameFirst = argv[1];
    args.inputFileNameSecond = argv[2];

    return args;
}

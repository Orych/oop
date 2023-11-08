#include <iostream>
#include <set>
#include <cmath>
#include <vector>
#include <optional>
#include <chrono>

void SieveOfEratosthenes(std::vector<bool>& sieve, int limit)
{
    for (int i = 2; i <= limit; ++i)
    {
        if (!sieve[i])
        {
            for (int j = i * i; j < sieve.size(); j += i)
            {
                sieve[j] = true;
            }
        }
    }
}

std::set<int> ExtractPrimes(const std::vector<bool>& sieve)
{
    std::set<int> primes;
    for (int i = 2; i < sieve.size(); ++i)
    {
        if (!sieve[i])
        {
            primes.insert(i);
        }
    }
    return primes;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::set<int> primes;

    if (upperBound < 2)
    {
        return primes;
    }

    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<bool> sieve(upperBound + 1, false);
    sieve[0] = sieve[1] = true;

    int limit = sqrt(upperBound);
    SieveOfEratosthenes(sieve, limit);

    primes = ExtractPrimes(sieve);


    if (upperBound == 100000000)
    {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        std::cout << "Search time: " << duration.count() << " ms" << std::endl;
    }

    return primes;
}

struct Args
{
    int upperBound;
};

std::optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[]) 
{
    auto args = ParseArgs(argc, argv);

    if (args->upperBound > 100000000 || args->upperBound < 0) 
    {
        std::cout << "Upper bound must be less than or equal to 100,000,000" << std::endl;
        return 1;
    }

    std::set<int> primes = GeneratePrimeNumbersSet(args->upperBound);

    for (int prime : primes) 
    {
        std::cout << prime << std::endl;
    }

    return 0;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: primeNumbers.exe <upper bound>\n";
        return std::nullopt;
    }

    Args args;
    args.upperBound = atoi(argv[1]);
    return args;
}
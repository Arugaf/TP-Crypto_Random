#include <fstream>
#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <random>
#include <vector>

/// Returns sha256 from the concatenation of a string and some salt
std::vector<uint> sha256FromString(const std::string &str, uint salt) {
    auto salt_str = std::to_string(salt);

    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, (str + salt_str).c_str(), str.size() + salt_str.size());
    SHA256_Final(hash, &sha256);

    return std::vector<uint>(hash, hash + SHA256_DIGEST_LENGTH);
}

/// Returns determined pseudo random number which is uniformly distributed in some range (start, end) based on a seed
template<typename T>
T generatePRNumber(const std::vector<uint> &seed, T start, T end) {
    std::seed_seq seedSeq(seed.begin(), seed.end());
    std::mt19937 engine(seedSeq);
    std::uniform_int_distribution<T> uniformDist(start, end);
    return uniformDist(engine);
}

std::vector<std::string> readStringsFromFile(const std::string &filename) {
    std::fstream file(filename);
    std::vector<std::string> result;

    std::string line;
    while (std::getline(file, line)) {
        result.push_back(line);
    }

    return result;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> clArguments;
    for (int i = 1; i < argc; ++i) {
        clArguments.emplace_back(argv[i]);
    }

    std::string filename;
    int seed = -1;
    int numOfBilets = 0;

    // Лениво было подрубать boost::program_options
    if (clArguments.size() < 6) {
        std::cout << "Not enough arguments" << std::endl;
        return 0;
    }

    if (clArguments[0] == std::string("--file")) {
        filename = clArguments[1];
    } else {
        std::cout << "No input file" << std::endl;
        return 0;
    }

    if (clArguments[2] == std::string("--numbilets")) {
        numOfBilets = std::stoi(clArguments[3]);
    } else {
        std::cout << "No number of bilets" << std::endl;
        return 0;
    }

    if (clArguments[4] == std::string("--parameter")) {
        seed = std::stoi(clArguments[5]);
    } else {
        std::cout << "No seed" << std::endl;
        return 0;
    }

    auto names = readStringsFromFile(filename);

    for (const auto &name : names) {
        std::cout <<
        name << ": " <<
        generatePRNumber(sha256FromString(name, seed), 1, numOfBilets) <<
        std::endl;
    }
    return 0;
}

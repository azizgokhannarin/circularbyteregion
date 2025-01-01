#include <iostream>
#include <vector>
#include <tuple>
#include <random>

#include "circularbyte.h"

uint8_t generateRandomNumber()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> dist(0, 255);
    return dist(gen);
}

#define BYTE_SIZE 10000

int main()
{
    CircularByte circularByte;
    std::vector<std::tuple<uint8_t, int>> encodedByteList;
    std::vector<uint8_t> byteList;
    uint8_t decoded = 0, encoded = 0;
    int direction = 0, oldDirection = 0;
    int failed = 0, changed = 0;

    for (size_t i = 0; i < BYTE_SIZE; i++) {
        byteList.push_back(generateRandomNumber());
    }

    //Encoding list
    circularByte.initialize();

    for (int i = 0; i < BYTE_SIZE; i++) {
        encoded = 0;
        direction = circularByte.encode(byteList[i], encoded);
        encodedByteList.push_back(std::make_tuple(encoded, direction));
    }


    //Decoding list
    circularByte.initialize();

    for (int i = 0; i < BYTE_SIZE; i++) {
        decoded = 0;
        circularByte.decode(decoded, std::get<0>(encodedByteList[i]), std::get<1>(encodedByteList[i]));

        if (byteList[i] != decoded) {
            failed++;
        }

        if (oldDirection != std::get<1>(encodedByteList[i])) {
            changed++;
            oldDirection = std::get<1>(encodedByteList[i]);
        }
    }

    std::cout << "Success rate %" << ((BYTE_SIZE - failed) / (float)BYTE_SIZE * 100) << std::endl;
    std::cout << "Direction changed " << changed << " times." << std::endl;

    return 0;
}

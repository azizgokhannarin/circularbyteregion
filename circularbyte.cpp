/******************************************************************************
 * File Name    : circularbyte.cpp
 * Coder        : Aziz Gökhan NARİN
 * E-Mail       : azizgokhannarin@yahoo.com
 * Explanation  : Circular Byte Region
 * Versiyon     : 1.0.0
 ******************************************************************************/

#include "circularbyte.h"

#include <iostream>

CircularByte::CircularByte()
{
    initialize();
}

CircularByte::~CircularByte()
{

}

int CircularByte::encode(const uint8_t &value, uint8_t &encoded)
{
    uint8_t region = 0;
    encoded &= 0x00;

    if (checkRegion(value, dynamicList, region)) { // Check regions first, no round
        encoded |= region & 0x03;
        return 0;
    } else {
        std::deque<uint8_t> tempList = dynamicList;

        for (size_t i = 0; i < 32; i++) {
            auto last_element = tempList.back();
            tempList.push_front(last_element);
            tempList.pop_back();

            if (checkRegion(value, tempList, region)) {
                encoded |= region & 0x03;
                encoded |= (i & 0x1F) << 2;
                dynamicList = tempList;
                return 1;
            }
        }

        tempList = dynamicList;

        for (size_t i = 0; i < 32; i++) {
            auto first_element = tempList.front();
            tempList.push_back(first_element);
            tempList.pop_front();

            if (checkRegion(value, tempList, region)) {
                encoded |= region & 0x03;
                encoded |= (i & 0x1F) << 2;
                dynamicList = tempList;
                return -1;
            }
        }

        return -2;
    }
}

void CircularByte::decode(uint8_t &value, const uint8_t &encoded, const int &direction)
{
    uint8_t round = 0, region = 0;

    if (direction == 0) {
        region |= encoded & 0x03;
        giveValue(value, region);
    } else if (direction == 1) {
        region |= encoded & 0x03;
        round |= (encoded & 0x7C) >> 2;

        for (size_t i = 0; i <= round; i++) {
            auto last_element = dynamicList.back();
            dynamicList.push_front(last_element);
            dynamicList.pop_back();
        }

        giveValue(value, region);
    } else if (direction == -1) {
        region |= encoded & 0x03;
        round |= (encoded & 0x7C) >> 2;

        for (size_t i = 0; i <= round; i++) {
            auto first_element = dynamicList.front();
            dynamicList.push_back(first_element);
            dynamicList.pop_front();
        }

        giveValue(value, region);
    } else {
        value = 0;
    }
}

void CircularByte::initialize()
{
    dynamicList.clear();

    for (size_t i = 0; i < 256; i++) {
        dynamicList.push_back(i);
    }
}

bool CircularByte::checkRegion(const uint8_t &value, const std::deque<uint8_t> &list, uint8_t &region)
{
    if (value == list[0]) {
        region = 0x00;
        return true;
    } else if (value == list[64]) {
        region = 0x01;
        return true;
    } else if (value == list[128]) {
        region = 0x02;
        return true;
    } else if (value == list[192]) {
        region = 0x03;
        return true;
    } else {
        return false;
    }
}

bool CircularByte::giveValue(uint8_t &value, const uint8_t &region)
{
    if (region == 0x00) {
        value = dynamicList[0];
        return true;
    } else if (region == 0x01) {
        value = dynamicList[64];
        return true;
    } else if (region == 0x02) {
        value = dynamicList[128];
        return true;
    } else if (region == 0x03) {
        value = dynamicList[192];
        return true;
    } else {
        return false;
    }
}

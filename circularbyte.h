/******************************************************************************
 * File Name    : circularbyte.h
 * Coder        : Aziz Gökhan NARİN
 * E-Mail       : azizgokhannarin@yahoo.com
 * Explanation  : Circular Byte Region
 * Versiyon     : 1.0.0
 ******************************************************************************/

#ifndef CIRCULARBYTE_H
#define CIRCULARBYTE_H

#include <cinttypes>
#include <deque>

class CircularByte
{
public:
    explicit CircularByte();
    virtual ~CircularByte();

    int encode(const uint8_t &value, uint8_t &encoded);
    void decode(uint8_t &value, const uint8_t &encoded, const int &direction);
    void initialize();

protected:
    bool checkRegion(const uint8_t &value, const std::deque<uint8_t> &list, uint8_t &region);
    bool giveValue(uint8_t &value, const uint8_t &region);

private:
    std::deque<uint8_t> dynamicList;
};

#endif // CIRCULARBYTE_H

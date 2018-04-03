#ifndef DS1302_HPP
#define DS1302_HPP

#define DS1302_SECONDS           0x80
#define DS1302_MINUTES           0x82
#define DS1302_HOURS             0x84
#define DS1302_DATE              0x86
#define DS1302_MONTH             0x88
#define DS1302_DAY               0x8A
#define DS1302_YEAR              0x8C
#define DS1302_CONTROL           0x8E
#define DS1302_TRICKLE           0x90
#define DS1302_CLOCK_BURST       0xBE
#define DS1302_CLOCK_BURST_WRITE 0xBE
#define DS1302_CLOCK_BURST_READ  0xBF
#define DS1302_RAM_START         0xC0
#define DS1302_RAM_END           0xFC
#define DS1302_RAM_BURST         0xFE
#define DS1302_RAM_BURST_WRITE   0xFE
#define DS1302_RAM_BURST_READ    0xFF

struct DS1302_RawTime {
    char tenSeconds, seconds;
    char tenMinutes, minutes;
    char tenHours, hours;
};

template <class T>
class DS1302 : public T {
public:
    void write(uint8_t addr, uint8_t v) {
        T::beginTransaction();
        T::setOutputMode();
        T::shiftOut(addr);
        T::shiftOut(v);
        T::endTransaction();
    }

    uint8_t read(uint8_t addr) {
        T::beginTransaction();
        T::setOutputMode();
        T::shiftOut(addr | 0x01);
        T::setInputMode();
        uint8_t v = T::shiftIn();
        T::endTransaction();
        return v;
    }

    void getTime(DS1302_RawTime *out) {
        uint8_t clockBuffer[8];
        readBurst(DS1302_CLOCK_BURST, 8, clockBuffer);
        out->tenSeconds = (clockBuffer[0] >> 4) & 0x07;
        out->seconds = (clockBuffer[0] & 0x0F);
        out->tenMinutes = (clockBuffer[1] >> 4) & 0x07;
        out->minutes = (clockBuffer[1] & 0x0F);
        out->tenHours = (clockBuffer[2] >> 4) & 0x03;
        out->hours = (clockBuffer[2] & 0x1F);
    }

    void readBurst(uint8_t addr, int count, char *out) {
        T::beginTransaction();
        T::setOutputMode();
        T::shiftOut(addr | 0x01);
        T::setInputMode();
        while (count--) {
            *(out++) = T::shiftIn();
        }
        T::endTransaction();
    }
};

#endif
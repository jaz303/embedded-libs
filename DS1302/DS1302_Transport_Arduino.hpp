#ifndef DS1302_TRANSPORT_ARDUINO_HPP
#define DS1302_TRANSPORT_ARDUINO_HPP

template <int clockPin, int resetPin, int dataPin>
class DS1302_Transport_Arduino {
public:
    void init(){
        digitalWrite(resetPin, LOW);
        pinMode(resetPin, OUTPUT);
        digitalWrite(clockPin, LOW);
        pinMode(clockPin, OUTPUT);
        pinMode(dataPin, OUTPUT);
    }
    
    void beginTransaction() {
        digitalWrite(resetPin, HIGH);
        delayMicroseconds(4);
    }

    void endTransaction() {
        digitalWrite(resetPin, LOW);
        delayMicroseconds(4);
    }

    void setInputMode() {
        pinMode(dataPin, INPUT);
    }
    
    void setOutputMode() {
        pinMode(dataPin, OUTPUT);
    }
    
    void shiftOut(uint8_t b) {
        for (byte i = 0; i < 8; ++i) {
            digitalWrite(dataPin, b & 0x01);
            delayMicroseconds(1);
            digitalWrite(clockPin, HIGH);
            delayMicroseconds(1);
            digitalWrite(clockPin, LOW);
            delayMicroseconds(1);
            b >>= 1;
        }
    }
    
    uint8_t shiftIn() {
        byte b = 0;
        for (byte i = 0; i < 8; ++i) {
            b >>= 1;
            b |= (digitalRead(dataPin) ? 0x80 : 0x00);
            digitalWrite(clockPin, HIGH);
            delayMicroseconds(1);
            digitalWrite(clockPin, LOW);
            delayMicroseconds(1);
        }
        return b;
    }
};

#endif
# Arduino

```
// Pins
#define CLK 2
#define RST 3
#define DAT 4

DS1302<DS1302_Transport_Arduino<CLK, RST, DAT>> rtc;

void setup() {
    rtc.init();
    rtc.write(DS1302_CONTROL, 0); // WP off
    rtc.write(DS1302_SECONDS, 0); // CH off, seconds zeroed
}

void loop() {
    DS1302_RawTime time;
    rtc.getTime(&time);
    delay(1000);
}
```
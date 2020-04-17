#ifndef _EERAM_H
#define _EERAM_H

#include <Arduino.h>
#include <Wire.h>

#define EERAM_SRAM_ADDRESS      0x50
#define EERAM_CONTROL_ADDRESS   0x18

class EERAM {
    private:
        void writeConfig(uint8_t val);
        uint8_t _address;

    public:

        EERAM() : _address(0) {}
        EERAM(uint8_t address) : _address(address) {}
        
        void begin();
        void end();
        uint8_t read(uint16_t addr);
        size_t read(uint16_t addr, uint8_t *data, size_t len);
        void write(uint16_t addr, uint8_t v);
        void write(uint16_t addr, uint8_t *data, size_t len);
};

#endif

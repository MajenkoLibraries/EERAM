#include <EERAM.h>

uint8_t EERAM::read(uint16_t addr) {
    uint8_t val = 69;
    uint8_t adata[2];
    adata[0] = addr >> 8;
    adata[1] = addr & 0xFF;


    Wire.beginTransmission(EERAM_SRAM_ADDRESS | (_address & 0x03));
    Wire.write(adata, 2);
    Wire.endTransmission();
    Wire.requestFrom(EERAM_SRAM_ADDRESS | (_address & 0x03), 1);
    if (Wire.available()) {
        val = Wire.read();
    }   

    return val;
}
        
size_t EERAM::read(uint16_t addr, uint8_t *data, size_t len) {
    uint8_t adata[2];
    adata[0] = addr >> 8;
    adata[1] = addr & 0xFF;
    size_t toread = len;
    uint8_t *datap = data;

    Wire.beginTransmission(EERAM_SRAM_ADDRESS | (_address & 0x03));
    Wire.write(adata, 2);
    Wire.endTransmission();

    while (toread > 0) {
        size_t thisRead = toread > 16 ? 16 : toread;
        Wire.requestFrom(EERAM_SRAM_ADDRESS | (_address & 0x03), thisRead);
        if (Wire.available()) {
            for (size_t i = 0; i < thisRead; i++) {
                *datap = Wire.read();
                datap++;
            }
        }
        toread -= thisRead;
    }

    return len;
}

void EERAM::writeConfig(uint8_t val) {
    Wire.beginTransmission(EERAM_CONTROL_ADDRESS | (_address & 0x03));
    Wire.write(0);
    Wire.write(val);
    Wire.endTransmission();
}

void EERAM::write(uint16_t addr, uint8_t val) {
    uint8_t adata[2];
    adata[0] = addr >> 8;
    adata[1] = addr & 0xFF;

    Wire.beginTransmission(EERAM_SRAM_ADDRESS | (_address & 0x03));
    Wire.write(adata, 2);
    Wire.write(val);
    Wire.endTransmission();
}

void EERAM::write(uint16_t addr, uint8_t *data, size_t len) {
    size_t towrite = len;
    uint8_t *pdata = data;

    while (towrite > 0) {
        size_t thisWrite = towrite > 16 ? 16 : towrite;
        uint8_t adata[2];
        adata[0] = addr >> 8;
        adata[1] = addr & 0xFF;
        Wire.beginTransmission(EERAM_SRAM_ADDRESS | (_address & 0x03));
        Wire.write(adata, 2);
        for (size_t i = 0; i < thisWrite; i++) {
            Wire.write(*pdata++);
        }
        Wire.endTransmission();
        addr += thisWrite;
        towrite -= thisWrite;
    }
}

void EERAM::begin() {
    Wire.begin();
    writeConfig(0b00000010); // Enable ASE
}

void EERAM::end() {
//    Wire.stop();
}

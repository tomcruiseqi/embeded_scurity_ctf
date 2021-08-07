//
// Created by qizengtian on 2021/8/7.
//

#include <stdint.h>

void Reykjavik(int16_t r14, int16_t r15) {
    int16_t r11 = 0;
    int16_t r10 = 0;
    int16_t r9 = 0;
    int16_t r8 = 0;
    int16_t r13 = 0;

    // Set 0x247c, 0x247d, 0x247e, 0x247f, 0x2480... total 256 to 0,1,2,3,...,255
    while (r13 < 0x100){
        *(r13 + 0x247c) = (int8_t)r13;
        r13++;
    }

    int16_t r12 = 0x247c;

    r13 = 0;
    r11 = 0;

    while (r11 < 0x100) {
        r8 = (int8_t)*r12;                                      // The 1st value.
        r10 = (int8_t)r8;                                       // Get the value
        r13 += r10;                                             // Sum
        r10 = r11;                                              // what's the meaning of r11?
        r10 &= 0x000f;                                          // Get the last half-byte value.
        r10 = (int8_t)*(r10 + 0x4472);                          // Get the 0~15th value starting from 0x4472
        r10 = 0x0080 & r10 ? (r10 & 0x00ff | 0xff00) : r10;     // Sign extended from byte to word (2 bytes), not affect the value.
        r13 += r10;                                             // Sum
        r13 &= 0x00ff;                                          // Get the byte value
        r10 = r13;
        r10 += 0x247c;                                          // The n-th.
        r9 = (int8_t)(*r10);                                    // Get the new n-th value
        *(r10 + 0) = (int8_t)r8;                                // Copy the original value to the new position.
        *(r12 + 0) = (int8_t )r9;                               // Copy the new value to the original position.
        r11++;
        r12++;
    }

    r11 = 0;
    r12 = r11;

    while(0 != r14) {
        r12++;
        r12 &= 0xff;
        r10 = r12;
        r10 += 0x247c;
        r8 = (int8_t)*r10;
        r11 += (int8_t )r8;
        r13 = r11;
        r13 += 0x247c;
        r9 = (int8_t )*r13;
        *r13 = (int8_t)r8;
        *r10 = (int8_t)r9;
        r9 += (int8_t)*r13;
        r13 = (int8_t)r9;
        *r15 ^= *(r13 + 0x247c);
        r15++;
        r14--;
    }
}

int main() {
    int16_t r15 = 0x4520;
    int16_t r14 = 0xf8;
    r15 = 0x2400;
    Reykjavik(r14, r15);
}

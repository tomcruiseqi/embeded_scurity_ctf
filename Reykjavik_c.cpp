//
// Created by qizengtian on 2021/8/7.
//

#include <stdint.h>

int8_t a_247c[0xff] = {0x00};
int8_t a_4472[0x10] = {0x54, 0x68, 0x69, 0x73, 0x49, 0x73, 0x53, 0x65,
                      0x63, 0x75, 0x72, 0x65, 0x52, 0x69, 0x67, 0x68};
int8_t a_2400[0xff] = {0x00};

void enc(int8_t n) {
    int16_t r11 = 0;
    int16_t r13 = 0;

    while (r13 < 0x100) {
        a_247c[r13] = r13;
        r13++;
    }

    int16_t r12 = 0x247c;

    r13 = 0;
    r11 = 0;

    int16_t sum_buffer = r13;
    int16_t i = r11;

    while (i < 0x100) {
        int8_t value_a = a_247c[i];
        sum_buffer += value_a;

        int16_t temp = i;
        temp = 0xff & a_4472[temp & 0xf];
        temp = 0x0080 & temp ? (0xff00 | temp) : temp;

        sum_buffer += temp;

        int8_t temp_buffer = a_247c[sum_buffer & 0xff];
        a_247c[sum_buffer & 0xff] = value_a;
        a_247c[i] = temp_buffer;

        i++;
    }

    r11 = 0;
    r12 = 0;

    sum_buffer = 0;
    i = 0;
    while (0 != n) {
        i++;
        int8_t  value_temp = a_247c[0xff & i];
        sum_buffer += value_temp;

        int8_t value_temp_2 = a_247c[sum_buffer];
        a_247c[sum_buffer] = value_temp;
        a_247c[0xff & i] = value_temp_2;

        value_temp_2 += value_temp;
        sum_buffer = value_temp_2;

        a_2400[i] ^= a_247c[sum_buffer];
        n--;
    }
}

int main() {
    enc(0xf8);
}
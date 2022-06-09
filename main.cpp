#include "mbed.h"


AnalogIn ain(PC_0);
DigitalOut dout(LED1);

int main(void)
{
    while (1) {
        if(ain > 0.3f) {
            dout = 1;
        } else {
            dout = 0;
        }

        printf("normalized: 0x%04X \n", ain.read_u16());
        wait_ns(1000000000);
    }
}
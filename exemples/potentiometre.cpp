#include "mbed.h"

AnalogIn ain(PC_0);

int main(void)
{
    printf("normalized: 0x%04X \n", ain.read_u16());
    wait_ns(1000000000);
}
}
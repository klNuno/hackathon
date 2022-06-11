#include "mbed.h"
#include <cstdlib>


DigitalOut stop(PF_2,0);
DigitalOut direction(PE_3,0);
DigitalOut direction2(PE_10,1);
PwmOut sah(PE_6);
PwmOut sah2(PE_5);

int main(){
    sah.period_us(50);
    sah2.period_us(50);
    sah = 1;
    sah2 = 1;
    ThisThread::sleep_for(5s);
    stop=1;
}
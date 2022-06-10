/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define BLINKING_RATE     500ms

void starting (void);
void mesure (void);
void pulseGenerator (void);

float getFrontDistance (void);
float getLeftDistance (void);
float getRearDistance (void);
float getRightDistance (void);

int getAllDistances (float* distanceTable);

InterruptIn Echo (PD_3);
DigitalOut Pulse (PC_3);
BusOut Selecter (PC_8,PF_9);
DigitalOut led (LED1);
Timer tempo;

Thread pulseGeneratorThread;
EventFlags myEvent;

float USSensor[4] = {0};
int canal=0;

int main() {

    float val;
    int flags = 0;

    printf("Boot-Up - NUCLEO F429ZI");

    Echo.rise(&starting);
    Echo.fall(&mesure);

    tempo.start();
    pulseGeneratorThread.start(&pulseGenerator);

    while (true) {
        flags = myEvent.wait_any(0x0F);
        val = getFrontDistance();
        if (flags & 0x01 && val < 900) printf ("\nfront = %f", val);     //FONCTIONNE
        val = getLeftDistance();
        if (flags & 0x02 && val < 900) printf ("\nleft = %f", val);         //FONCTIONNE seulement avec fix
        val = getRearDistance();
        if (flags & 0x04 && val < 900) printf ("\nrear = %f", val);        //FONCTIONNE
        val = getRightDistance();
        if (flags & 0x08 && val < 900) printf ("\nright = %f", val);         //FONCTIONNE
    }
    return 0;
}

void starting (void){
    tempo.reset();
}

void mesure (void){
    long long stoptime = std::chrono::duration_cast<std::chrono::microseconds>(tempo.elapsed_time()).count();
    USSensor[canal] = (float) stoptime / 58.0f;
    myEvent.set(1<<canal);
}

void pulseGenerator (void){
    while (true) {

        for (canal=0;canal<4;canal++){
            Selecter = (int)canal%4;
            wait_us (1);
            Pulse = 1;
            wait_us (10);
            Pulse = 0;
            ThisThread::sleep_for(60ms);
        }
    }
}

float getFrontDistance (void){
    return USSensor[0];
}

float getLeftDistance (void){
    return USSensor[1];
}

float getRearDistance (void){
    return USSensor[2];
}

float getRightDistance (void){
    return USSensor[3];
}

int getAllDistances (float* distanceTable){
    if (distanceTable == nullptr) return -1;
    for (int i=0; i<4; i++) {
        *(distanceTable+i) = USSensor[i];
    }
    return 0;
}
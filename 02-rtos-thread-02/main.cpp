/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "rtos.h"

Thread thread(osPriorityNormal, 1024);

DigitalOut led1(LED1);

#define STOP_FLAG 1

void blink() {
  bool threadStatus = false;
  while (!threadStatus) {
    threadStatus = ThisThread::flags_wait_any_for(STOP_FLAG, 100ms);
    led1 = !led1;
  }
}

int main() {
    thread.start(blink);
    ThisThread::sleep_for(5000ms);
    thread.flags_set(STOP_FLAG);
    thread.join();
    led1 = true;
}

/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "rtos.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

Thread thread1(osPriorityNormal, 1024);
Thread thread2(osPriorityNormal, 1024);

void led1_thread() {
  while (true) {
    led1 = !led1;
    ThisThread::sleep_for(750ms);
  }
}

void led2_thread() {
  while (true) {
    led2 = !led2;
    ThisThread::sleep_for(500ms);
  }
}

int main() {
  thread1.start(led1_thread);
  thread2.start(led2_thread);
  while (true) {
    led3 = !led3;
    ThisThread::sleep_for(250ms);
  }
}

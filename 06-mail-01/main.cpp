#include "mbed.h"
#include "rtos.h"
#include "MMA8451Q.h"
#include <cstdio>

PwmOut red(LED_RED);
PwmOut green(LED_GREEN);
PwmOut blue(LED_BLUE);

Thread ThIMU(osPriorityNormal, 1024);

MMA8451Q IMU(PTE25, PTE24, 0x3A);

typedef struct {
    float acc_x;
    float acc_y;
    float acc_z;
} mail_t;

Mail<mail_t, 16> mail_box;

void GetIMU(){
    while(true){
        mail_t *mail = mail_box.try_alloc();
        mail->acc_x = IMU.getAccX();
        mail->acc_y = IMU.getAccY();
        mail->acc_z = IMU.getAccZ();
        mail_box.put(mail);
        ThisThread::sleep_for(50ms);
    }
}

void SetLED(){
    while(true){
        mail_t *mail = mail_box.try_get();
        if(mail != nullptr){
            red.write(mail->acc_x);
            green.write(mail->acc_y);
            blue.write(mail->acc_z);
            printf("X: %f, Y: %f, Z: %f \n", mail->acc_x, mail->acc_y, mail->acc_z);
            mail_box.free(mail);
        }
    }
}



int main()
{
    red.period_ms(20);
    green.period_ms(20);
    blue.period_ms(20);

    ThIMU.start(GetIMU);
    SetLED();
}


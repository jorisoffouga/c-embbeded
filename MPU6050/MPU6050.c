#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "../src/i2c.h"
// Address si AD0=gnd 
#define MPU6050_ADDRESS  0x68
// registre who am i 
#define MPU6050_WHO_AM_I 0x75
// registre configuration 
#define MPU6050_CONFIG_GYRO 0x1B
#define MPU6050_CONFIG_ACCEL 0x1C
#define MPU6050_RA_PWR_MGMT_1 0x6B
// Registres de l'acclerometre 
#define MPU6050_ACCEL_XH 0x3B
#define MPU6050_ACCEL_XL 0x3C
#define MPU6050_ACCEL_YH 0x3D
#define MPU6050_ACCEL_YL 0x3E
#define MPU6050_ACCEL_ZH 0x3F
#define MPU6050_ACCEL_ZL 0x40
// Registres du gyroscope
#define MPU6050_GYRO_XH  0x43
#define MPU6050_GYRO_XL  0x44
#define MPU6050_GYRO_YH  0x45
#define MPU6050_GYRO_YL  0x46
#define MPU6050_GYRO_ZH  0x47
#define MPU6050_GYRO_ZL  0x48
// Registres temperature
#define MPU6050_TEMP_H 0x41
#define MPU6050_TEMP_L 0x42
i2c_t i2c;
struct {
    unsigned short ax;
    unsigned short ay;
    unsigned short az;
    unsigned short gx;
    unsigned short gy;
    unsigned short gz;
    float tmp;
}mpu6050;
void display_help(const char *arg){
    fprintf(stderr,"usage: %s -d for get id device, -a get accelaration, -g get gyroscope or -t get température",arg);
}
void get_device(void){
    uint8_t msg_reg[1]={0x75};
    uint8_t msg_data[1]={0};
    struct i2c_msg msg[2]=
    {
        {.addr=MPU6050_ADDRESS, .flags=0, .len=1, .buf=msg_reg},
        {.addr=MPU6050_ADDRESS, .flags = I2C_M_RD, .len=1, .buf=msg_data},
    };
     if (i2c_transfer(&i2c, msg, 1) < 0) {
        fprintf(stderr, "i2c_transfer(): %s\n", i2c_errmsg(&i2c));
        exit(1);
    }
    printf(" Device: %d\n",msg_data[0]);
}

void mpu6050_init(void){
    uint8_t msg_config[2]={0x6B,0x01};
    uint8_t msg_config_accel[2]={0x1B,0x00};
    uint8_t msg_config_gyro[2]={0x1C,0x00};
    struct i2c_msg msg[3]=
    {
        {.addr=MPU6050_ADDRESS,.flags=0, .len=2, .buf=msg_config},
        {.addr=MPU6050_ADDRESS,.flags=0, .len=2, .buf=msg_config_accel},
        {.addr=MPU6050_ADDRESS,.flags=0, .len=2, .buf=msg_config_gyro},
    };
    if (i2c_transfer(&i2c, msg, 3) < 0) {
        fprintf(stderr, "i2c_transfer(): %s\n", i2c_errmsg(&i2c));
        exit(1);
    }
}

void get_temp(void){
    uint8_t msg_reg_h[1]={0x41};
    uint8_t msg_reg_l[1]={0x42};
    uint8_t msg_data[2]={0};
    unsigned short tmp;
    struct i2c_msg msg[4]=
    {
        {.addr=MPU6050_ADDRESS,.flags=0, .len=1, .buf=msg_reg_h},
        {.addr=MPU6050_ADDRESS,.flags=I2C_M_RD, .len=1, .buf=&msg_data[0]},
        {.addr=MPU6050_ADDRESS,.flags=0, .len=1, .buf=msg_reg_l},
        {.addr=MPU6050_ADDRESS,.flags=I2C_M_RD, .len=1, .buf=&msg_data[1]},
    };
    if (i2c_transfer(&i2c, msg, 4) < 0) {
        fprintf(stderr, "i2c_transfer(): %s\n", i2c_errmsg(&i2c));
        exit(1);
    }
    tmp=(msg_data[0] <<8) | msg_data[1];
    mpu6050.tmp=((float)tmp/ 340.0) + 36.53;
    printf("Température : %f\n",mpu6050.tmp);

}

void get_accel(void){
    uint8_t msg_reg_xh[1]={0x3B};
    uint8_t msg_reg_xl[1]={0x3C};
    uint8_t msg_reg_yh[1]={0x3D};
    uint8_t msg_reg_yl[1]={0x3E};
    uint8_t msg_reg_zh[1]={0x3F};
    uint8_t msg_reg_zl[1]={0x40};
    uint8_t msg_data[6]={0};
    uint8_t tmp_ax;
    uint8_t tmp_ay;
    uint8_t tmp_az;
    struct i2c_msg msg[12]=
    {
        {.addr=MPU6050_ADDRESS,.flags=0, .len=1, .buf=msg_reg_xh},
        {.addr=MPU6050_ADDRESS,.flags=I2C_M_RD, .len=1, .buf=&msg_data[0]},
        {.addr=MPU6050_ADDRESS,.flags=0, .len=1, .buf=msg_reg_xl},
        {.addr=MPU6050_ADDRESS,.flags=I2C_M_RD, .len=1, .buf=&msg_data[1]},
        {.addr=MPU6050_ADDRESS,.flags=0, .len=1, .buf=msg_reg_yh},
        {.addr=MPU6050_ADDRESS,.flags=I2C_M_RD, .len=1, .buf=&msg_data[2]},
        {.addr=MPU6050_ADDRESS,.flags=0, .len=1, .buf=msg_reg_yl},
        {.addr=MPU6050_ADDRESS,.flags=I2C_M_RD, .len=1, .buf=&msg_data[3]},
        {.addr=MPU6050_ADDRESS,.flags=0, .len=1, .buf=msg_reg_zh},
        {.addr=MPU6050_ADDRESS,.flags=I2C_M_RD, .len=1, .buf=&msg_data[4]},
        {.addr=MPU6050_ADDRESS,.flags=0, .len=1, .buf=msg_reg_zl},
        {.addr=MPU6050_ADDRESS,.flags=I2C_M_RD, .len=1, .buf=&msg_data[5]},
    };
    if (i2c_transfer(&i2c, msg, 12) < 0) {
        fprintf(stderr, "i2c_transfer(): %s\n", i2c_errmsg(&i2c));
        exit(1);
    }
    mpu6050.ax=(msg_data[0]<<8)|msg_data[1];
    mpu6050.ay=(msg_data[2]<<8)|msg_data[3];
    mpu6050.az=(msg_data[4]<<8)|msg_data[5];
    printf("Accélération: ax: %d, ay: %d, az: %d\n",mpu6050.ax,mpu6050.ay,mpu6050.az);
}

void get_gyro(void){
    uint8_t msg_reg_xh[1]={0x43};
    uint8_t msg_reg_xl[1]={0x44};
    uint8_t msg_reg_yh[1]={0x45};
    uint8_t msg_reg_yl[1]={0x46};
    uint8_t msg_reg_zh[1]={0x47};
    uint8_t msg_reg_zl[1]={0x48};
    uint8_t msg_data[6]={0};
    uint8_t tmp_ax;
    uint8_t tmp_ay;
    uint8_t tmp_az;
    struct i2c_msg msg[12]=
    {
        {.addr=MPU6050_ADDRESS,.flags=0, .len=1, .buf=msg_reg_xh},
        {.addr=MPU6050_ADDRESS,.flags=I2C_M_RD, .len=1, .buf=&msg_data[0]},
        {.addr=MPU6050_ADDRESS,.flags=0, .len=1, .buf=msg_reg_xl},
        {.addr=MPU6050_ADDRESS,.flags=I2C_M_RD, .len=1, .buf=&msg_data[1]},
        {.addr=MPU6050_ADDRESS,.flags=0, .len=1, .buf=msg_reg_yh},
        {.addr=MPU6050_ADDRESS,.flags=I2C_M_RD, .len=1, .buf=&msg_data[2]},
        {.addr=MPU6050_ADDRESS,.flags=0, .len=1, .buf=msg_reg_yl},
        {.addr=MPU6050_ADDRESS,.flags=I2C_M_RD, .len=1, .buf=&msg_data[3]},
        {.addr=MPU6050_ADDRESS,.flags=0, .len=1, .buf=msg_reg_zh},
        {.addr=MPU6050_ADDRESS,.flags=I2C_M_RD, .len=1, .buf=&msg_data[4]},
        {.addr=MPU6050_ADDRESS,.flags=0, .len=1, .buf=msg_reg_zl},
        {.addr=MPU6050_ADDRESS,.flags=I2C_M_RD, .len=1, .buf=&msg_data[5]},
    };
    if (i2c_transfer(&i2c, msg, 12) < 0) {
        fprintf(stderr, "i2c_transfer(): %s\n", i2c_errmsg(&i2c));
        exit(1);
    }
    mpu6050.gx=(msg_data[0]<<8)|msg_data[1];
    mpu6050.gy=(msg_data[2]<<8)|msg_data[3];
    mpu6050.gz=(msg_data[4]<<8)|msg_data[5];
    printf("Accélération: ax: %d, ay: %d, az: %d\n",mpu6050.gx,mpu6050.gy,mpu6050.gz);
}

int main (int argc, char *argv[]){
    uint16_t option;
    if (argc < 2){
	display_help(argv[0]);
	exit(EXIT_FAILURE);
    }
    /* Open the i2c-2 bus on Pico-pi-imx7d */
    if (i2c_open(&i2c, "/dev/i2c-2") < 0) {
        fprintf(stderr, "i2c_open(): %s\n", i2c_errmsg(&i2c));
        exit(1);
    }
    mpu6050_init();
    while((option = getopt(argc,argv,"dagtq")!=-1)){
        switch(option){
            case 'd':
            get_device();
            break;
            case 'a':
            get_accel();
            break;
            case 'g':
            get_gyro();
            break;
            case 't':
            get_temp();
            break;
            default:
            display_help(argv[0]);
            break;
        }
    }
	
    i2c_close(&i2c);
    return 0;
}
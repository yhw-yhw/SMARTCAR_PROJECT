/*
 * File:		KL46_ADC.c
 * Purpose:		�򵥵�APIadc16 / PGA���������
 *  ����ļ���������������:
 *  1. adc_cal��У׼ADC
 *  2. adc_config_alt���򵥵�����ÿһ���ṹ��ģ��ת����
 *
 * ������;�����ṹ��ADCʹ�������ADC��PGA�Ĵ��������ݡ�
 * a) ����adc_config_alt��������ADC����ADC0��ADC1��
 * b) ���ú�����adc_calУ׼ADC
 * c) ����adc_config_alt�����ٴλָ���������ú�У׼
 *
 *
 */
#ifndef __I2C_H__
#define __I2C_H__ 

void i2c_set_tx_mode(I2C_MemMapPtr p);    
void i2c_set_rx_mode(I2C_MemMapPtr p);
void i2c_set_slave_mode(I2C_MemMapPtr p);
void i2c_set_master_mode(I2C_MemMapPtr p);
void i2c_give_nack(I2C_MemMapPtr p);
void i2c_give_ack(I2C_MemMapPtr p);
void i2c_repeated_start(I2C_MemMapPtr p);
void i2c_write_byte(I2C_MemMapPtr p, uint8 data);
uint8 i2c_read_byte(I2C_MemMapPtr p);
void i2c_start(I2C_MemMapPtr p);
void i2c_stop(I2C_MemMapPtr p);
void i2c_wait(I2C_MemMapPtr p);
uint16 i2c_get_ack(I2C_MemMapPtr p);
void hal_i2c0_init(I2C_MemMapPtr p); //Acelerometro
void hal_i2c_deinit(I2C_MemMapPtr p);

void hal_i2c1_init(I2C_MemMapPtr p);  //Magnetometro
#define I2C_READ  1
#define I2C_WRITE 0

#endif
/*
 * File:		KL46_ADC.c
 * Purpose:		简单的APIadc16 / PGA驱动程序或
 *  这个文件有以下两个功能:
 *  1. adc_cal：校准ADC
 *  2. adc_config_alt：简单地配置每一个结构的模数转换器
 *
 * 典型用途：填充结构的ADC使用所需的ADC和PGA寄存器的内容。
 * a) 调用adc_config_alt功能配置ADC，（ADC0或ADC1）
 * b) 调用函数，adc_cal校准ADC
 * c) 调用adc_config_alt功能再次恢复所需的配置后，校准
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
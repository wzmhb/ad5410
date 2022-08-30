#ifndef    __AD5410_H
#define    __AD5410_H

#define    AD5410_PORT            GPIOE
#define    AD5410_FAULT_PORT      GPIOC

#define    AD5410_LAT6_PIN   GPIO_PIN_1     //锁存,低电平恢复复位状态
#define    AD5410_SDO6_PIN   GPIO_PIN_2     //ad5410的输出
#define    AD5410_LAT5_PIN   GPIO_PIN_3
#define    AD5410_SDO5_PIN   GPIO_PIN_4
#define    AD5410_LAT4_PIN   GPIO_PIN_5
#define    AD5410_SDO4_PIN   GPIO_PIN_6
#define    AD5410_LAT3_PIN   GPIO_PIN_7
#define    AD5410_SDO3_PIN   GPIO_PIN_8
#define    AD5410_LAT2_PIN   GPIO_PIN_9
#define    AD5410_SDO2_PIN   GPIO_PIN_10
#define    AD5410_LAT1_PIN   GPIO_PIN_11
#define    AD5410_SDO1_PIN   GPIO_PIN_12

#define    AD5410_CLR_PIN    GPIO_PIN_13       //高电平清零
#define    AD5410_SDI_PIN    GPIO_PIN_14
#define    AD5410_SCK_PIN    GPIO_PIN_15


#define    AD5410_FAULT1     GPIO_PIN_6        //pc6
#define    AD5410_FAULT2     GPIO_PIN_7
#define    AD5410_FAULT3     GPIO_PIN_8
#define    AD5410_FAULT4     GPIO_PIN_9
#define    AD5410_FAULT5     GPIO_PIN_10
#define    AD5410_FAULT6     GPIO_PIN_11

#define   AD5410_GPIO_CLK_ENABLE()            __HAL_RCC_GPIOE_CLK_ENABLE();
#define   AD5410_FAULT_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE();      //输入设置成上拉

#define SET_CLEAR()		HAL_GPIO_WritePin(GPIOE,AD5410_CLR_PIN,GPIO_PIN_SET)	         //PE13->CLEAR
#define CLR_CLEAR()		HAL_GPIO_WritePin(GPIOE,AD5410_CLR_PIN,GPIO_PIN_RESET)
 
#define SET_LATCH_1()		HAL_GPIO_WritePin(GPIOE,AD5410_LAT1_PIN,GPIO_PIN_SET)	      //PE11->LATCH
#define CLR_LATCH_1()		HAL_GPIO_WritePin(GPIOE,AD5410_LAT1_PIN,GPIO_PIN_RESET)
#define SET_LATCH_2()		HAL_GPIO_WritePin(GPIOE,AD5410_LAT2_PIN,GPIO_PIN_SET)	      //PE11->LATCH
#define CLR_LATCH_2()		HAL_GPIO_WritePin(GPIOE,AD5410_LAT2_PIN,GPIO_PIN_RESET)
#define SET_LATCH_3()		HAL_GPIO_WritePin(GPIOE,AD5410_LAT3_PIN,GPIO_PIN_SET)	      //PE11->LATCH
#define CLR_LATCH_3()		HAL_GPIO_WritePin(GPIOE,AD5410_LAT3_PIN,GPIO_PIN_RESET)
#define SET_LATCH_4()		HAL_GPIO_WritePin(GPIOE,AD5410_LAT4_PIN,GPIO_PIN_SET)	      //PE11->LATCH
#define CLR_LATCH_4()		HAL_GPIO_WritePin(GPIOE,AD5410_LAT4_PIN,GPIO_PIN_RESET)
#define SET_LATCH_5()		HAL_GPIO_WritePin(GPIOE,AD5410_LAT5_PIN,GPIO_PIN_SET)	      //PE11->LATCH
#define CLR_LATCH_5()		HAL_GPIO_WritePin(GPIOE,AD5410_LAT5_PIN,GPIO_PIN_RESET)
#define SET_LATCH_6()		HAL_GPIO_WritePin(GPIOE,AD5410_LAT6_PIN,GPIO_PIN_SET)	      //PE11->LATCH
#define CLR_LATCH_6()		HAL_GPIO_WritePin(GPIOE,AD5410_LAT6_PIN,GPIO_PIN_RESET)
 
#define	SET_SCL()		    HAL_GPIO_WritePin(GPIOE,AD5410_SCK_PIN,GPIO_PIN_SET)	//PB13->SCLK
#define	CLR_SCL()		    HAL_GPIO_WritePin(GPIOE,AD5410_SCK_PIN,GPIO_PIN_RESET)
 
#define SET_SDO()		    HAL_GPIO_WritePin(GPIOE,AD5410_SDI_PIN,GPIO_PIN_SET)	//PB15->SDIN
#define CLR_SDO()		    HAL_GPIO_WritePin(GPIOE,AD5410_SDI_PIN,GPIO_PIN_RESET)

#define  STATUS_REG_ADDR    0x00
#define  DATA_REG_ADDR      0x01
#define  CTL_REG_ADDR       0x02

#define  AD5410_OVER_TEMP         0x01
#define  AD5410_SLEW_ACTIVE       0x02
#define  AD5410_IOUT_FAULT        0x04

typedef struct tagAD5410_Group_Status {
    u8  status[7];     //从1开始，status[0]是无意义的

}AD5410_Group_Status;

//Function that writes to the AD5420 via the SPI port. 
//--------------------------------------------------------------------------------
void WriteToAD5410(u8 count,u8 chip_no,u8 *Buf);
 
//Function that reads from the AD7190 via the SPI port. 
//--------------------------------------------------------------------------------
void ReadFromAD5410(u8 count,u8 chip_no,u8 *buf,u8 reg);
void ad5410_init(void);
void delay (int length);
void ad5410_gpio_init(void);
u8 check_ad5410_fault(void);
void set_ad5410_current(u8 chip,u32 value);    //value < 4096,256 = 1ma

#endif



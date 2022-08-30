#ifndef   __AD5410_C
#define   __AD5410_C

#include "include.h"

static u8 buf[4];
AD5410_Group_Status   ad5410_grp_sta;
void ad5410_gpio_init(void)
{
    AD5410_GPIO_CLK_ENABLE();
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = AD5410_LAT1_PIN|
                          AD5410_LAT2_PIN|
                          AD5410_LAT3_PIN|
                          AD5410_LAT4_PIN|
                          AD5410_LAT5_PIN|
                          AD5410_LAT6_PIN|
                          AD5410_CLR_PIN|AD5410_SDI_PIN|AD5410_SCK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(AD5410_PORT, &GPIO_InitStruct);  

//设置sdo管脚
    GPIO_InitStruct.Pin = AD5410_SDO1_PIN|
                          AD5410_SDO2_PIN|
                          AD5410_SDO3_PIN|
                          AD5410_SDO4_PIN|
                          AD5410_SDO5_PIN|
                          AD5410_SDO6_PIN;

    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(AD5410_PORT, &GPIO_InitStruct);       
//设置fault管脚
    GPIO_InitStruct.Pin = AD5410_FAULT1|
                          AD5410_FAULT2|
                          AD5410_FAULT3|
                          AD5410_FAULT4|
                          AD5410_FAULT5|
                          AD5410_FAULT6;

    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(AD5410_FAULT_PORT, &GPIO_InitStruct);     
}

void delay (int length)
{
	while (length >0)
    	length--;
}
 
void CLR_LATCH(u8 chip)
{
    switch(chip)
    {
        default:
        case 1:
            CLR_LATCH_1();
            break;
        case 2:
            CLR_LATCH_2();
            break;
        case 3:
            CLR_LATCH_3();
            break;
        case 4:
            CLR_LATCH_4();
            break;
        case 5:
            CLR_LATCH_5();
            break;
        case 6:
            CLR_LATCH_6();
            break;
    }
}

void SET_LATCH(u8 chip)
{
    switch(chip)
    {
        default:
        case 1:
            SET_LATCH_1();
            break;
        case 2:
            SET_LATCH_2();
            break;
        case 3:
            SET_LATCH_3();
            break;
        case 4:
            SET_LATCH_4();
            break;
        case 5:
            SET_LATCH_5();
            break;
        case 6:
            SET_LATCH_6();
            break;
    }
}
//---------------------------------
//void WriteToAD5420(unsigned char count,unsigned char *Buf);
//---------------------------------
//Function that writes to the AD5420 via the SPI port. 
//--------------------------------------------------------------------------------
void WriteToAD5410(u8 count,u8 chip_no,u8 *Buf)
{
 
	u8	ValueToWrite = 0;
    u32	i = 0;
	u32	j = 0;
	
 
	CLR_LATCH(chip_no);
 
	for ( i=count;i>0;i-- )
 	{
	 	ValueToWrite =	*(Buf+i-1);
		for (j=0; j<8; j++)
		{
			CLR_SCL();
			if(0x80 == (ValueToWrite & 0x80))
			{
				SET_SDO();	    //Send one to SDIN pin of AD5420
			}
			else
			{
				CLR_SDO();	    //Send zero to SDIN pin of AD5420
			}
										 
			delay(1);
			SET_SCL();
			delay(1);
			ValueToWrite <<= 1;	//Rotate data
	
		}
 
	}
	CLR_SCL();
	delay(1);
	SET_LATCH(chip_no);
	delay(20);
}
 
u8 ad5410_ReadPin(u8 chip_no)
{
    u8 ret_val = 0;
    
    switch(chip_no)
    {
        default:
        case 1:
            ret_val = HAL_GPIO_ReadPin(GPIOE,AD5410_SDO1_PIN);			//Read SDO of AD5410
            break;
        case 2:
            ret_val = HAL_GPIO_ReadPin(GPIOE,AD5410_SDO2_PIN);			//Read SDO of AD5410
            break;
        case 3:
            ret_val = HAL_GPIO_ReadPin(GPIOE,AD5410_SDO3_PIN);			//Read SDO of AD5410
            break;
        case 4:
            ret_val = HAL_GPIO_ReadPin(GPIOE,AD5410_SDO4_PIN);			//Read SDO of AD5410
            break;
        case 5:
            ret_val = HAL_GPIO_ReadPin(GPIOE,AD5410_SDO5_PIN);			//Read SDO of AD5410
            break;
        case 6:
            ret_val = HAL_GPIO_ReadPin(GPIOE,AD5410_SDO6_PIN);			//Read SDO of AD5410
            break;
    }    
    return ret_val;
}    

u8 ad5410_fault_ReadPin(u8 chip_no)
{
    u8 ret_val = 0;
    
    switch(chip_no)
    {
        default:
        case 1:
            ret_val = HAL_GPIO_ReadPin(GPIOC,AD5410_FAULT1);			//Read SDO of AD5410
            break;
        case 2:
            ret_val = HAL_GPIO_ReadPin(GPIOC,AD5410_FAULT2);			//Read SDO of AD5410
            break;
        case 3:
            ret_val = HAL_GPIO_ReadPin(GPIOC,AD5410_FAULT3);			//Read SDO of AD5410
            break;
        case 4:
            ret_val = HAL_GPIO_ReadPin(GPIOC,AD5410_FAULT4);			//Read SDO of AD5410
            break;
        case 5:
            ret_val = HAL_GPIO_ReadPin(GPIOC,AD5410_FAULT5);			//Read SDO of AD5410
            break;
        case 6:
            ret_val = HAL_GPIO_ReadPin(GPIOC,AD5410_FAULT6);			//Read SDO of AD5410
            break;
    }    
    return ret_val;
}    
//---------------------------------
//ReadFromAD5420();
//---------------------------------
//Function that reads from the AD5420 via the SPI port. 
//--------------------------------------------------------------------------------
void ReadFromAD5410(u8 count,u8 chip_no,u8 *buf,u8 reg)
{
	u32	i = 0;
	u32	j = 0;
	u32 iTemp = 0;
	unsigned	char  RotateData = 0;
 
    buf[2] = 0x02;
    buf[1] = 0x00;
    buf[0] = reg;
    WriteToAD5410(3,chip_no,buf);
    
	CLR_LATCH(chip_no);
	for(j=count; j>0; j--)
	{
		for(i=0; i<8; i++)
		{
            CLR_SCL();
			RotateData <<= 1;		//Rotate data
			delay(1);
			CLR_SDO();				//write a nop condition when read the data. 
			iTemp = ad5410_ReadPin(chip_no);
			SET_SCL();	
			if(iTemp == GPIO_PIN_SET)
			{
				RotateData |= 1;	
			}
			delay(1);
			
		}
		*(buf+j-1)= RotateData;
	}
	CLR_SCL();
	delay(1);	 
	SET_LATCH(chip_no);
	delay(20);
} 

void set_ad5410_current(u8 chip,u32 value)    //value < 4096,256 = 1ma
{
    u32  reg_val = 0;
    u8   high,low;
    
    high = low = 0;
    
    reg_val = value << 4;
    high = (reg_val>>8)&0xff;
    low = reg_val&0xff;
    
    buf[2] = 0x01;//数字寄存器,out = 4ma + 16ma*DATA/(2^12)
    buf[1] = high;   //512
    buf[0] = low;
    WriteToAD5410(3,chip,buf);	//Write 019966H to SHIFT REGISTER  to write 9966 to DATA REGISTER
    delay(2000);   
}

void reset_ad5410(u8 chip)
{
        buf[2] = 0x56;//复位寄存器
        buf[1] = 0x00;              //Disable Slew Rate
        buf[0] = 0x01;//复位
        WriteToAD5410(3,chip,buf);	//Write 551005 to SHIFT REGISTER  to write 1005 to control register
        delay(2000);
        buf[2] = 0x55;//控制寄存器
        buf[1] = 0x10;//REXT=0,内 部电流设置电阻;OUTEN=1,输出使能，禁止数字压摆率控制;
         //4-24mA控制,
        buf[0] = 0x05;
        WriteToAD5410(3,chip,buf);
        delay(2000);
}

void ad5410_init(void)
{
    u8 chip = 1;
    u32 i;
  
    ad5410_gpio_init();
    
    for(i = 1; i <= 6; i++){
        chip = i;
        
        reset_ad5410(chip);
        
        ReadFromAD5410(3,chip,buf,CTL_REG_ADDR);		//Read CONTROL REGISTER ,回读寄存器，看看是否正确
        if((buf[1] == 0x10) && (buf[0] == 0x05)){
            printf("ad5410 channel %d initial ok\r\n",chip);
        }else{
            printf("ad5410 channel %d initial fail\r\n",chip);
            ad5410_grp_sta.status[i] = 0x55;
        }
        

//        set_ad5410_current(chip,256);
        set_ad5410_current(chip,512);
        
        ReadFromAD5410(3,chip,buf,STATUS_REG_ADDR);		//Read STATUS REGISTER
        if(buf[0]&AD5410_OVER_TEMP){
            printf("fault: ad5410 channel %d over temperature\r\n",chip);
        }
        if(buf[0]&AD5410_SLEW_ACTIVE){
            printf("ad5410 channel %d slew active\r\n",chip);
        }
        if(buf[0]&AD5410_IOUT_FAULT){
            printf("ad5410 channel %d Iout fault\r\n",chip);
        } 
        ad5410_grp_sta.status[i] = buf[0];
    }
 /*   
    buf[2] = 0x01;//数字寄存器
    buf[1] = 0x00;
    buf[0] = 0x00;//0mA
    WriteToAD5410(3,chip,buf);	
    delay(2000);
    
    buf[2] = 0x01;//数字寄存器
    buf[1] = 0x15;
    buf[0] = 0x55;//2mA
    WriteToAD5410(3,chip,buf);	
    delay(2000);
    
    buf[2] = 0x01;//数字寄存器
    buf[1] = 0x2A;
    buf[0] = 0xAA;//4mA
    WriteToAD5410(3,chip,buf);	
    delay(2000);
    
    buf[2] = 0x01;//数字寄存器
    buf[1] = 0x6A;
    buf[0] = 0xAA;//10mA
    WriteToAD5410(3,chip,buf);	
    delay(2000);
    
    buf[2] = 0x01;//数字寄存器
    buf[1] = 0xD5;
    buf[0] = 0x55;//20mA
    WriteToAD5410(3,chip,buf);	
    delay(2000);
    
    buf[2] = 0x01;//数字寄存器
    buf[1] = 0xFF;
    buf[0] = 0xFF;//24mA
    WriteToAD5410(3,chip,buf);	
    delay(2000);
*/
}

const u8 AD5410_FAULT_REG_MAP[7] = {0,0x01,0x02,0x04,0x08,0x10,0x20};
u8 check_ad5410_fault(void)
{
    u8 status = 0,bit_value = 0;
    u8 i = 1;
    for(i = 1; i <=6; i++){
        bit_value = ad5410_fault_ReadPin(i);
        if(bit_value == GPIO_PIN_RESET){
            status |= AD5410_FAULT_REG_MAP[i];
            ReadFromAD5410(3,i,buf,STATUS_REG_ADDR);		//Read STATUS REGISTER
            ad5410_grp_sta.status[i] = buf[0];
        }else{
            ad5410_grp_sta.status[i] = 0;
        }
    }
    return status;
}

#endif

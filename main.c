#define LCD_RS_PIN PIN_C4
#define LCD_RW_PIN PIN_C5
#define LCD_ENABLE_PIN PIN_C6
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
//End LCD module connections

#include <16F877A.h>
#device ADC=10
#fuses HS,NOWDT,NOPROTECT,NOLVP                       
#use delay(clock = 20000000)
#include <lcd.c>


#define MAYBOM PIN_B2
#define REM1 PIN_B0
#define REM0 PIN_B1
unsigned int16 nhietdo;
unsigned int32 doam ;
unsigned int j;
void hienthi2(unsigned int32 doam);
void hienthi1(unsigned int16 nhietdo);
unsigned int16 cambiennietdo();
unsigned int32 cambiendoam();
void dcrem(unsigned int16 x);
void hienthi1(unsigned int16 nhietdo)
{
      
      delay_ms(10);
      lcd_gotoxy(1,1);
      lcd_putc("NHIET DO:");
      printf(lcd_putc, "%lu",nhietdo);
      delay_ms(10);


}
void hienthi2(unsigned int32 doam)
{
      lcd_gotoxy(1,2);
      lcd_putc("DO AM: ");
      printf(lcd_putc,"%lu",doam);
      lcd_putc("  %");
     // lcd_putc('\f');
      delay_ms(10);
}

unsigned int16 cambiennietdo()
{
   unsigned int16 nhietdo;
      set_adc_channel(0);
      for (j = 0; j<200;j++)
      {
     // set_adc_channel(0);
         nhietdo = nhietdo + read_adc();
         delay_ms(1);
      }
      nhietdo = nhietdo/2.046;
      nhietdo = nhietdo/200;
   return nhietdo;
}
unsigned int32 cambiendoam()
{
   unsigned int32 doam;
      set_adc_channel(1);
      for (j = 0; j<200;j++)
      {
         //set_adc_channel(1);
         doam = doam + read_adc();
         delay_ms(1);
      }
      doam = doam*100;
      doam = doam/1023;
      //doam = doam*100;
      doam = doam/200;
      doam = 100-doam;
   return doam;
}
void dcrem(unsigned int16 x)
{
   if (x >= 35) 
   {
      output_high(REM0);
      output_low(REM1);
   }
   else if ( x<35 && x>= 25)
   {
      output_low(REM0);
      output_low(REM1);
   }
   else
   {
      output_high(REM1);
      output_low(REM0);
   }
}
void main()
{
   setup_adc_ports(AN0_AN1_AN3);
   setup_adc(ADC_CLOCK_DIV_2);
   set_tris_c(0x00);
   set_tris_d(0x00);
   set_tris_d(0x00);
   set_tris_a(0xFF);
   lcd_init();
   //delay_ms(10);
   while(TRUE)
   {
      nhietdo = 0;
      doam = 0;
      nhietdo = cambiennietdo();
      
      doam = cambiendoam();
      hienthi1(nhietdo);
      //lcd_putc("\f");
      hienthi2(doam);
      delay_ms(500);
      lcd_putc("\f");
      //delay_ms(1);
      if (doam >=55) output_low(MAYBOM);
      else output_high(MAYBOM);
      dcrem(nhietdo);
   }
}

#include <main.h>
#include <ONE_wire.c>

//#define unit_on
#define unit_on    output_high(PIN_C0);
#define unit_off   output_low(PIN_C0);

#define ten_on     output_high (PIN_C1);
#define ten_off    output_low(PIN_C1);

#define thu_on     output_high (PIN_C2);
#define thu_off    output_low(PIN_C2);

const int8 digit[14]=~63,~6,~91,~79,~102,~109,~124,~7,~255,~103,~109,~121,~118,~56;

int8 i=0,data=0;int8 ii=0;
int16 value=0;
INT1 set_flagh=0,set_flagl=0;

INT1 SET_SET=0;
int16 min=350;
int16 max=370;

void display(int8 data)
{
 int8 dat;
// dat = digit[data];
   dat = data;
   for(i=0;i<8;i++)
   {
     if((dat & 0x01) == 0x01)DATA_HIGH; //Data High
     else DATA_LOW; //Data Low
     delay_us(1);
     CLOCK_HIGH;
     delay_us(1);
     CLOCK_LOW;
     delay_us(1);
     dat >>= 1; //Shift one bit
   }
   ENABLE_HIGH;
}

int8  thu,ten,unit;
int8 flag;

void display()
{
 thu = (value/100)%10;
 ten = (value/10)%10;
 unit = (value/1)%10;

 
 if (set_flagh==1)
 {
   thu=10;
   ten=11;
   unit=12;
 }
 if (set_flagl==1)
 {
   thu=10;
   ten=11;
   unit=13;
 }
 if (SET_SET==1)
 {
  thu  =10;
  ten  =11;
  unit =11;
 }
  
 unit_off;
 ten_off;
 thu_off
    
  unit = digit[unit];
  unit = unit | 0b10000000;
  display(unit);
  unit_on;
  delay_mS(1);
  unit_off;
  
  ten = digit[ten];
  ten = ten &  0b01111111;
  display(ten);
  ten_on;
  delay_ms(1);
  ten_off;
  
  thu = digit[thu];
  display(thu);
  thu_on;
  delay_ms(1);
  thu_off
}


#include <ds18B20.c>
int32 counter=0;
int1 delay_flag =1;
int1 relay_on_flag =0;
void main()
{
  relay_off;
  if (read_eeprom(10) == 'O')
  {
   Lo(max)=read_eeprom(1);
   Hi(max)=read_eeprom(2);

   Lo(min)=read_eeprom(3);
   Hi(min)=read_eeprom(4); 
  }
  ELSE 
  {
    min=350;
    max=370;      
    write_eeprom(10,'O');
    RESET_CPU();
  }
//int16 val;
   set_tris_c(0xff);
   set_tris_a(0xff);
//   set_tris_a(0x2f);
   setup_comparator(NC_NC_NC_NC);
   SETUP_ADC_PORTS(NO_ANALOGS);
    
relay_off;
ds1820_read();
ds1820_read();

int8 counter123;   
   while(TRUE)
   {
     counter123 ++;     
     if (counter123 > 14)
     {
      counter123=0;
      value =  (ds1820_read());     
     }
     display();

     if (value <= min)
     {          
      relay_off;     
      delay_flag = 1;
     }
     if (value >= max && relay_on_flag) 
     {
      relay_on;
      counter = 0;
      delay_flag = 0;
      relay_on_flag = 0;
     }
     
  if (delay_flag)
      {
       counter++;
       if (counter > 3000) // 3000
       {
         relay_on_flag = 1;        
       }
      }   
//=====================     
   if (SET_BUTTON == 1)
   {
     set_flagh=1;
     for (ii=0; ii < 100; ii++)
           {
             display();
             DELAY_MS(3);
           }
     set_flagh=0;
     while(SET_BUTTON == 1)
     {
             display();
     }
     VALUE = MAX ;
     while(1)
     {
       if (up_button==1)
       {
        if (value > 999)
        {
         value=0;
        }
        value+=5;
        for (ii=0; ii<=25; ii++)
           {
             display();
             DELAY_MS(3);
           }
       }
       else if (down_button==1)
       {
        if (value==0)
        {
         value=999;
        }
        value-=5;
        for (ii=0; ii<=25; ii++)
           {
             display();
             DELAY_MS(3);
           }
       }
      if (set_button==1)
      {
       max=value;
       write_eeprom(1,Lo(max));
       write_eeprom(2,Hi(max));
       break;
      }
       display();
     }
    //=====================
     set_flagl=1;
     for (ii=0; ii<=100; ii++)
           {
             display();
             DELAY_MS(3);
           }
     set_flagl=0;
     while(SET_BUTTON == 1)
     {
             display();
     }
//     Lo(value)=read_eeprom(3);
//     Hi(value)=read_eeprom(4);
     VALUE = MIN ;
     while(1)
     {
       if (up_button==1)
       {
        if (value > 999)
        {
         value=0;
        }
        value+=5;
           for (ii=0; ii<=25; ii++)
           {
             display();
             DELAY_MS(3);
           }
       }
       else if (down_button==1)
       {
        if (value==0)
        {
         value=999;
        }
        value-=5;
        for (ii=0; ii<=25; ii++)
           {
             display();
             DELAY_MS(3);
           }
       }
      if (set_button==1)
      {
       min=value;
       write_eeprom(3,Lo(min));
       write_eeprom(4,Hi(min));
            for (ii=0; ii < 100; ii++)
           {
             display();
             DELAY_MS(3);
           }
           write_eeprom(10,'O');
           SET_SET=1;
           for (ii=0; ii < 100; ii++)
           {            
            display();
            DELAY_MS(3);
           }
           SET_SET=0;
       break;
      }
     display();
    }
   }
  }
}

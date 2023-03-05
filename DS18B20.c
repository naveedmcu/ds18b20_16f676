int1 leak = 1;

int16 ds1820_read()
{
 int8 busy=0, temp1, temp2;
 signed int16 temp3;
 int16 result;
 display();
 onewire_reset();
 display();
 onewire_write(0xCC);
 display();
 onewire_write(0x44);

 while (busy == 0)
 {
  busy = onewire_read();
  display();
 }
 onewire_reset();
 display();
 onewire_write(0xCC);
 display();
 onewire_write(0xBE);
 display();
 temp1 = onewire_read();
 display();
 temp2 = onewire_read();
 display();
 temp3 = make16(temp2, temp1);
// display();
// result = (float) temp3 / 2;     //Calculation for DS18S20 with 0.5 deg C resolution
// result = (float) temp3 / 16.0;  //Calculation for DS18B20 with 0.1 deg C resolution

 result =  temp3 * 5;   // for  .5 deg
// result =  temp3;
 display();
// delay_ms(200);

 return(result );
}

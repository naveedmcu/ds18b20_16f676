#include <16F676.h>
#device adc=10

#define Lo(param) ((char *)&param)[0]
#define Hi(param) ((char *)&param)[1]
#define Higher(param) ((char *)&param)[2]
#define Highest(param) ((char *)&param)[3]

#define lo(param) ((char *)&param)[0]
#define hi(param) ((char *)&param)[1]
#define higher(param) ((char *)&param)[2]
#define highest(param) ((char *)&param)[3]

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                       //Internal RC Osc, no CLKOUT
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOBROWNOUT               //No brownout reset

//#use standard_io(A)
#use delay(INT=4Mhz)

//#use rs232(baud=2400, xmit=PIN_A5,rcv=PIN_A4)

#define DATA_HIGH    output_high(PIN_C3)
#define DATA_LOW     output_low(PIN_C3)

#define CLOCK_HIGH   output_high(PIN_C4)
#define CLOCK_LOW    output_low(PIN_C4)

#define ENABLE_HIGH  output_high(PIN_C5)
#define ENABLE_LOW   output_low(PIN_C5)
//==============================================================================
#ifndef unit_on
#define unit_on    output_LOW (PIN_C0);
#define unit_off   output_HIGH(PIN_C0);

#define ten_on     output_LOW (PIN_C1);
#define ten_off    output_HIGH(PIN_C1);

#define thu_on     output_LOW (PIN_C2);
#define thu_off    output_HIGH(PIN_C2);
#endif
//==============================================================================

#define relay_on     output_low  (PIN_A1);
#define relay_off    output_high (PIN_A1);

#define SET_button    INPUT_STATE(PIN_A2)
#define UP_button     INPUT_STATE(PIN_A3)
#define DOWN_button   INPUT_STATE(PIN_A4)

#byte   TRISAbits    = getenv("SFR:TRISA")
#bit    TRISA_B0     = TRISAbits.0


#include <avr/io.h>
#include <stdint.h>       
int ADCValue_Read(int ADC_channel)
{
  int ADCval;
  ADMUX = ADC_channel; // Select  ADC1/PC1
  ADMUX |= (1 << REFS0);    //  AVCC with external capacitor at AREF pin
  ADMUX &= ~(1 << ADLAR);   //  ADLAR: ADC Left Adjust Result
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);    // 128 prescale for 16Mhz
  ADCSRA |= (1 << ADEN);    // ADC Enable. Writing this bit to one enables the ADC. By writing it to zero, the ADC is turned off. 
  ADCSRA |= (1 << ADSC);    // Start the ADC conversion
  while(ADCSRA & (1 << ADSC));  // Wait for conversion
  ADCval = ADCL;     // First 8 Bit value 
  ADCval = (ADCH << 8) + ADCval;  // Total value = H+L
  return ADCval;
}

    

int main(void)
{
    int ADCvalue;// Varible for ADC Declaration 
    DDRB=1<<PB5;  // Port B , Pin 5 is made as Output 

    while (1)
    {
            ADCvalue = ADCValue_Read(1);
            
            if(ADCvalue>500)
            {
              PORTB=1<<PB5;  // PORTB to High
            }
            if(ADCvalue<500)
            {
              PORTB=0x00;  // PORTB to Low
            }
    }
}

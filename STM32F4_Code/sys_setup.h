


#ifndef _sys_setup_h
#define _sys_setup_h

#define isUsingDevBoard 1	//Use this to toggle setup conditions for switching between the actual SmartMouse and the devboard, which have different pinouts but functionality is the same.

#ifdef __cplusplus
 extern "C" {
#endif

void setup_system_clocks();	//Sets main system clocks and oscillator sources
void setup_gpio();  //Function to handle setting all IO registers for pins - call before setting up peripherals
void setup_uart();	//Function to handle setting up UART on power-up for serial debugging
void setup_dac();	//Sets DAC to enable output
void setup_adc();	//Sets ADC to begin reading
void setup_NVIC();	//sets NVIC to handle interrupt sources
void setup_SPI();

#ifdef __cplusplus
 }
#endif


#endif

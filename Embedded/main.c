#include <stdio.h>
#include <wiringPi.h>
#include <pcf8591.h>
#include <time.h>

#define PCF 120

int main(void)
{
	int value;
	wiringPiSetup ();
	pcf8591Setup (PCF, 0x48);

	// 17 27 21 5 6 13 19 26	
	while(1)
	{
		value = analogRead (PCF);
		printf("valuve:%d" , value);	
		if (value >= 100 && value < 110) 
			system("./gpio1"); ////////////////////17

		else if(value >= 85 && value < 100){
			system("./gpio2"); ///////////////////17 + 27/
		}
		
		else if(value >= 69 && value < 85){
			system("./gpio3"); ////////////////////17 27 21
		}	
                
		else if(value >= 60 && value < 69){
                        system("./gpio4"); ////////////////////17 27 21 5
		}
                else if(value >= 55 && value < 60)
                        system("./gpio5"); //////////////////////17 27 21 5 6

                else if(value >= 53 && value < 55)
                        system("./gpio6"); /////////////////////17 27 21 5 6 13

                else if(value >= 52 && value < 53)
                        system("./gpio7"); /////////////////////17 27 21 5 6 13 19

		else if(value >=50 && value < 52)
                        system("./gpio8"); /////////////////////17 27 21 5 6 13 19 26
	}

}	

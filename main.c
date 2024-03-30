/*
 * main.c
 *
 *  Created on: Mar 18, 2024
 *      Author: Eng Hamada Ahmed
 *
 */
/*************************LIB**************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

/*************************MCAL*************************/
#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/DIO/DIO_Config.h"
#include "MCAL/DIO/DIO_Private.h"

/*************************HAL**************************/
#include"HAL/LCD/LCD_Interface.h"
#include "HAL/KPD/KPD_Interface.h"
/*************************Delay*************************/
#include <util/delay.h>



int main(){

		DIO_Vid_SetPortDirection(Port_C,output);
		DIO_Vid_SetPortDirection(Port_D,output);
		LCD_Vid_Init();

		//Keypad_Init();

		DIO_Vid_SetPortDirection(Port_B,output);   //Column output
		DIO_Vid_SetPortDirection(Port_A,input);    //Row input pull up
		DIO_Vid_SetPortValue(Port_A,0b00001111);         //pullup
		//u8 Pressed_Key=Keypad_u8GetPressedKey();

		char password[] = "2024"; // Define the correct password
		char enteredPassword[5] = ""; // Initialize array to store user input

		LCD_vid_GoTo(0, 0);
		LCD_vid_SendString("Enter PW,");

		int i = 0;
		while(1) { //LCD_vid_DisplayClear();
		    u8 x = Keypad_u8GetPressedKey();

		    if(x != 101 && i < 4) {
		        LCD_vid_GoTo(1,3+i);
		        LCD_vid_SendData(x);
		        enteredPassword[i] = x; // Store entered character
		        i++;

		        if (i > 0 && (i-1) < 4) { // Check if within bounds of password length
		            _delay_ms(100);
		            LCD_vid_GoTo(1,3+i-1);
		            LCD_vid_SendData('*');
		        }
		    } else if (x == 101 && i == 4) { // Check if '#' (101) key is pressed and password length is 4
		        enteredPassword[i] = '\0'; // Null terminate the entered password

		        // Compare entered password with the correct password manually
		        int match = 1;
		        for (int j = 0; j < 4; j++) {
		            if (enteredPassword[j] != password[j]) {  //password[j]=correct pass
		                match = 0;
		                break;
		            }
		        }

		        // Display result based on comparison
		        LCD_vid_GoTo(1, 0);
		        if (match) {
		        	LCD_vid_DisplayClear();
		        	LCD_vid_SendString("PW is Correct");
		        	LCD_vid_GoTo(1,1);
		            LCD_vid_SendString("Hello,Open Door");
		            break;
		        } else {
		        		LCD_vid_DisplayClear();
		        	    LCD_vid_SendString("PW not correct");
		        	    _delay_ms(1000);
		        	    LCD_vid_DisplayClear();
		        	    LCD_vid_GoTo(0,0);
		        	    LCD_vid_SendString("Enter PW,");
		        	    i = 0; // Reset the password entry index
		        }
		         //break; // Exit the loop after password verification


		    }
		    x = 0xFF;
		}

		return 0;
}


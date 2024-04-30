/*
 ====================================================================================
 Name        : Calculator.h
 Author      : Mohamed Magdy Ali
 Description : Integrate the Keypad and LCD drivers with GPIO to make Calculator.
 Date        : 08/10/2023
 ====================================================================================
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_


#include <avr/io.h>
#include <util/delay.h>	/* For the delay functions */
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // for isDigit() function

#include "std_types.h"
#include "common_macros.h"
#include "gpio.h"
#include "keypad.h"
#include "lcd.h"



#define MAX_EXPRESSION_LENGTH 200





char * get_expression();


void displaySympol(uint8 key);


// function takes string of the eq and evaluates it then return value
//int evaluate(char str_equation[]);
int evaluateExpression(const char *expression, uint8 exp_length);




#endif /* CALCULATOR_H_ */

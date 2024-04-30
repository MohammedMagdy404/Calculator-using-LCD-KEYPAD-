/*
 ====================================================================================
 Name        : Calculator.c
 Author      : Mohamed Magdy Ali
 Description : Integrate the Keypad and LCD drivers with GPIO to make Calculator.
 Date        : 08/10/2023
 ====================================================================================
 */

#include "calculator.h"

uint8 row = 0;
uint8 key;
uint8 exp_length = 0;

char expr[MAX_EXPRESSION_LENGTH];
char * str;

// the Main function (Entry Point)
int main(void){
	LCD_init();

	LCD_displayStringRowColumn(0,0," LCD Calculator ");

	LCD_moveCursor(1,0); 			/* Move the cursor to the second row */

	str = get_expression();
	_delay_ms(500); 				/* Press time */

	LCD_displayString("=");
	LCD_intgerToString(evaluateExpression(expr,exp_length));


	while(1){
//		key = KEYPAD_getPressedKey();
		if(KEYPAD_getPressedKey() == (uint8)13){
			LCD_moveCursor(1, 0);
			LCD_displayString("                ");
			LCD_moveCursor(1, 0);
		}
	}
}

/*
 * Description :
 * function to get the equation in form of string expression
 */

char * get_expression(){
	//	uint8 exp_length = 0;
	while(1){
		key = KEYPAD_getPressedKey();

		if(key == 13){
			LCD_moveCursor(1, 0);
			LCD_displayString("                ");
			LCD_moveCursor(1, 0);
		}

		if (key == '=') {
			expr[exp_length] = '\0';  // Null-terminate the string
			return expr;  // Return the global expression as a string
		}

		if ((key >= 0) && (key <= 9)) {
			// Handle numeric keys
			if (exp_length < MAX_EXPRESSION_LENGTH - 1) {
				expr[exp_length] = key + '0'; 		// adding '0' to convert key to its corresponding ASCII
				exp_length++;
			}
		} else {
			// Handle non-numeric keys
			if (exp_length < MAX_EXPRESSION_LENGTH - 1) {
				switch(key){
				case '+':
					expr[exp_length] = '+'; 		// adding '0' to convert key to its corresponding ASCII

					break;
				case '-':
					expr[exp_length] = '-'; 		// adding '0' to convert key to its corresponding ASCII

					break;
				case '*':
					expr[exp_length] = '*'; 		// adding '0' to convert key to its corresponding ASCII

					break;
				case '/':
					expr[exp_length] = '/'; 		// adding '0' to convert key to its corresponding ASCII

					break;
				default:
					expr[exp_length] = key; 		// adding '0' to convert key to its corresponding ASCII

				}
				exp_length++;
			}
		}

		displaySympol(key);

		_delay_ms(500); /* Press time */
	}
}


/*
 * Description :
 * function to display symbols on the screen either "num" (or +,-,*,/)
 */

void displaySympol(uint8 key){
	// Display the gotten key
	if((key <= 9) && (key >= 0))
	{
		LCD_intgerToString(key);   /* display the pressed keypad switch */
	}
	else
	{
		LCD_displayCharacter(key); /* display the pressed keypad switch */
	}
}

/*
 * Description :
 * takes string of the eq and evaluates it then return value and negative number handling
 * the priority of operation handling
 */

int evaluateExpression(const char *expression, uint8 exp_length){
	int result = 0;
	int num = 0;
	int sign = 1;

	while (*expression && exp_length) {
		if (isdigit(*expression)) {
			num = num * 10 + (*expression - '0');
		} else if (*expression == '+' || *expression == '-') {
			result += sign * num;
			num = 0;
			sign = (*expression == '+') ? 1 : -1;
		} else if (*expression == '*' || *expression == '/') {
			char operator = *expression;
			expression++;  					// Move to the next character
			exp_length--;

			int nextNum = 0;
			int nextSign = 1;
			if (*expression == '-') {
				nextSign = -1;
				expression++;
				exp_length--;
			}
			while (isdigit(*expression) && exp_length) {
				nextNum = nextNum * 10 + (*expression - '0');
				expression++;
				exp_length--;
			}
			if (operator == '*') {
				num *= nextSign * nextNum;
			} else if (operator == '/') {
				if (nextNum != 0) {
					num /= nextSign * nextNum;
				} else {
					// Handle division by zero error
					LCD_moveCursor(1, 0);
					LCD_displayString("Error: Division by zero\n");
					return 0;
				}
			}
			continue;
		}
		expression++;
		exp_length--;
	}

	// Handle the last number and operator
	result += sign * num;

	return result;
}



/* To Be continued...
 *
 *	1. can handle multi-digit number 265 + 2543 ==> with stack
 *	+-+-1 =
 *	-+-+* = error
 *
 */





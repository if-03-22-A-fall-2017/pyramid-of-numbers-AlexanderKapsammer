/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <2AHIF>
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			Pyramid of Numbers
 * Author:			<Alexander Kapsammer>
 * ----------------------------------------------------------
 * Description:
 * Calculates a pyramid of numbers, i.e., it multiplies a big
 * integer by the number 2, its result by 3, etc. and then
 * returns to the original value by subsequently dividing,
 * again starting by 2, 3, etc.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>

/// The maximum number of digits allowed in a big int.
#define MAX_DIGITS 80
#define OPERATION_START 2
#define OPERATION_END 9

/** BigInt represents an integer number which can have MAX_DIGITS digits
*** @see MAX_DIGITS
*/
struct BigInt {
	/** number of digits of the big int. */
	int digits_count;

	/** array of digits of big int. */
	unsigned int the_int[MAX_DIGITS];
};

/** strtobig_int converts a string into a BigInt. If strtobig_int runs
*** against a character not between '0' and '9' the conversion stops
*** at this point.
*** @param *str The string to be converted.
*** @param len Number of characters in string to be converted.
*** @param *big_int The converted string now as BigInt.
* @return The number of characters converted.
*/
int strtobig_int(const char *str, int len, struct BigInt *big_int);

/** print_big_int() prints a BigInt.
*** @param *big_int The BigInt to be printed.
*/
void print_big_int(const struct BigInt *big_int);

/** multiply() multiplies a BigInt by an int.
*** @param big_int The BigInt to be multiplied.
*** @param factor The int value which is multiplied by BigInt.
*** @param *big_result The result of the multiplication.
*/
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result);

/** divide() multiplies a BigInt by an int.
*** @param big_int The BigInt to be divided.
*** @param divisor The int value by which we want to devide big_int.
*** @param *big_result The result of the division.
*/
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result);

/** copy_big_int() copies a BigInt to another BigInt.
*** @param from The source where we want to copy from.
*** @param *to The target where we want to copy to.
*/
void copy_big_int(const struct BigInt *from, struct BigInt *to);

/**
*** main() reads the base number from which the pyramid has to be calculated
*** into an array of char. The max. length of this number is MAX_DIGITS.
*** The number is checked to contain only digits. If not the program exits.
*** Then the inputted number is converted into a big int by calling the
*** function strtobig_int().
*** After the conversion the tower is calculated by calling the functions
*** multiply(), print_big_int(), and copy_big_int() consecutively from 2 to
*** 9 and then again with divide() instead of multiply() from 2 to 9.
***
*/
int main(int argc, char *argv[]) {
//input
	printf("Pyramid of Numbers\n\n");
	printf("Please enter a number: ");
	char input[MAX_DIGITS + 1];
	scanf("%s",input);
	int len = strlen(input);
	if (len > MAX_DIGITS - 5) {
		printf("error\n");
		return 0;
	}
//convert string to BigInt
	struct BigInt number = {len};
	int count = strtobig_int(input, len, &number);
	if (count != len) {
		printf("error\n");
		return 0;
	}
//multiply
	for (int i = OPERATION_START; i <= OPERATION_END; i++) {
		len = number.digits_count;
		int result_len = len;
		print_big_int(&number);

		printf(" * %d = ",i);
		if ((number.the_int[0] + number.the_int[1] * i / 10) * i >= 10 && result_len == len) {
			result_len++;
		}
		struct BigInt result = {result_len};
		multiply(&number,i,&result);
		print_big_int(&result);
		copy_big_int(&result,&number);
		printf("\n");

	}
	//divide
	for (int i = OPERATION_START; i <= OPERATION_END; i++) {
		len = number.digits_count;
		int result_len = len;
		print_big_int(&number);
		printf(" / %d = ", i);
		struct BigInt result = {result_len};
		divide(&number, i, &result);
		print_big_int(&result);
		number.digits_count = result.digits_count;
		copy_big_int(&result, &number);
		printf("\n");
	}
	return 0;
}
void divide(const struct BigInt *number, int divisor, struct BigInt *result) {
	int rest = 0;
	int count = 0;
	for (int i = 0; i < number->digits_count; i++)
	{
		int divide_number = number->the_int[i] + 10 * rest;
		if (divide_number >= divisor) {
			result->the_int[i - count] = divide_number / divisor;
			rest = divide_number % divisor;
		}
		else
		{
			rest = number->the_int[i];
			if (i == 0) {
				count++;
				result->digits_count--;
			}
			else
				result->the_int[i-count] = 0;
		}
	}
}
void copy_big_int(const struct BigInt *from, struct BigInt *to) {
	if (from->digits_count > to->digits_count) {
		to->digits_count = from->digits_count;
	}
	for (int i = from->digits_count - 1; i >= 0; i--) {
		to->the_int[i] = from->the_int[i];
	}
}
void multiply(const struct BigInt *number, int factor, struct BigInt *result){
	int transfer = 0;
	for (int i = number->digits_count -1; i >= 0; i--) {
		int subtotal = number->the_int[i] * factor + transfer;
		transfer = (int)(subtotal / 10);
		result->the_int[result->digits_count - (number->digits_count - i)] = subtotal - 10 * transfer;
	}
	if (transfer > 0) {
		result->the_int[0] = transfer;
	}
}
int strtobig_int(const char *input, int len, struct BigInt *number){

	for (int i = 0; i < len; i++) {
		if (!((int)input[i] >= 47 && (int)input[i] <= 57)) {
			return i;
		}
		else
			number->the_int[i] = input[i] - 48;
	}
	return len;
}
void print_big_int(const struct BigInt *number){
	for (int i = 0; i < number->digits_count; i++) {
		printf("%d", number->the_int[i]);
	}
}

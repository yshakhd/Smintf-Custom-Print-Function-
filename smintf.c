#define HW09_BONUS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include "smintf.h"

void mintf(const char *format, ...);
void _format_edit_display(const char *format, va_list format_list, int* size, bool dont_print, char *str);
void _format_num_mint(int n, int r, char* p, char* str, bool dont_print, int* idx);
void _put_char(char c, char *str, bool dont_print, int* idx);

char* smintf(const char *format, ...) {
	va_list format_list;
	va_start(format_list, format);

	int size_string = 1;
	char* str = NULL;
	_format_edit_display(format, format_list, &size_string, true, str);
	va_end(format_list);
	str = malloc(sizeof(*str) * size_string);
	int dummy_size = 0;
	
	va_start(format_list, format);
	_format_edit_display(format, format_list, &dummy_size, true, str);
	str[size_string - 1] = '\0';
	va_end(format_list);
	return str;
}

void mintf(const char *format, ...) {
	va_list format_list;
	va_start(format_list, format);
	int dummy = 0;
	_format_edit_display(format, format_list, &dummy, false, NULL);
	va_end(format_list);
}

void _format_edit_display(const char* format, va_list format_list, int* size, bool dont_print, char *str) {
	
	for(int formIdx = 0; format[formIdx] != '\0'; formIdx++) {
		if(format[formIdx] == '%') {
			if(format[formIdx + 1] == 'd') {
				int current_arg = va_arg(format_list, int);
				_format_num_mint(current_arg, 10, "", str, dont_print, size);
				formIdx++;
			}
			else if(format[formIdx + 1] == 'b') {
				int current_arg = va_arg(format_list, int);
				_format_num_mint(current_arg, 2, "0b", str, dont_print, size);
				formIdx++;
			}
			else if(format[formIdx + 1] == 'x') {
				int current_arg = va_arg(format_list, int);
				_format_num_mint(current_arg, 16, "0x", str, dont_print, size);
				formIdx++;
			}
			else if(format[formIdx + 1] == '$') {
				int current_arg = va_arg(format_list, int);
				int left_num = current_arg / 100;
				_format_num_mint(left_num, 10, "$", str, dont_print, size);
				_put_char('.', str, dont_print, size);
				int two_dec = current_arg - left_num * 100;
				int digit_one = two_dec / 10;
				int digit_two = two_dec % 10;
				_put_char('0' + digit_one, str, dont_print, size);
				_put_char('0' + digit_two, str, dont_print, size);
				formIdx++;
			}
			else if(format[formIdx + 1] == 's') {
				char* current_arg_ch = va_arg(format_list, char*);
				for(int strIdx = 0; current_arg_ch[strIdx] != '\0'; strIdx++) {
					_put_char(current_arg_ch[strIdx], str, dont_print, size);
				}
				formIdx++;
			}
			else if(format[formIdx + 1] == 'c') {
				char current_arg = va_arg(format_list, int);
				_put_char(current_arg, str, dont_print, size);
				formIdx++;
			}	
			else if(format[formIdx + 1] == '%') {
				_put_char('%', str, dont_print, size);	
				formIdx++;
			}
			else {
				_put_char(format[formIdx], str, dont_print, size);
			}
			va_end(format_list);
		}
		else {
			_put_char(format[formIdx], str, dont_print, size);
		}
	}
}

void _put_char(char c, char *str, bool dont_print, int* idx) {
	if(dont_print) {
		if(str != NULL) {
			str[*idx] = c;
		}
		(*idx)++;
	}
	else {
		fputc(c, stdout);
	}
}

void _format_num_mint(int n, int radix, char* prefix, char *str, bool dont_print, int *idx) {
	unsigned int num = n;
	if(n < 0) {
		num = -n; //allows for INT_MIN to be held in an unsigned int
		_put_char('-', str, dont_print, idx);
	}

	for(int chIndex = 0; prefix[chIndex] != '\0'; chIndex++) {
		_put_char(prefix[chIndex], str, dont_print, idx); //adapted from PROF
	}
	int placeValCounter = 1; //determines the length of the converted number
	unsigned int placeValNum = num;
	while(placeValNum >= radix) {
		placeValNum /= radix;
		placeValCounter++;
	}

	unsigned int placeNum = num;
	int valueOfPlace = 0;
	int digit = 0;
	while(placeValCounter > 0) {
		valueOfPlace = 1; //default place value is 1's place
		for(int valIndex = placeValCounter; valIndex > 1; valIndex--) {
			valueOfPlace *= radix; //squared place values based on number of digits
		}
		digit = placeNum / valueOfPlace;
		if(digit <= 9) { //adapted from PROF
			_put_char('0' + digit, str, dont_print, idx);
		}
		else {
			_put_char('a' + (digit - 10), str, dont_print, idx); //digit - 10 recalibrates the increment to start at 'a'
		}
		placeNum %= valueOfPlace; //determines the next dividend to determine next digit
		placeValCounter--;
	}
}

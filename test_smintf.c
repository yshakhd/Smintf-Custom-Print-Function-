#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include "smintf.h"
#include "miniunit.h"

#define mu_check_smintf(expected, ...)             \
	do {                                           \
		char* actual = smintf(__VA_ARGS__);        \
		mu_check_strings_eq((expected), (actual)); \
		free(actual);                              \
	} while(false)

void mintf(const char *format, ...);

int _test_space_string() {
	mu_start();
	mu_check_smintf(" ", " ");
	mu_end();
}

int _test_simple_string() {
	mu_start();
	mu_check_smintf("I have 100 gecs","I have 100 gecs");
	mu_end();
}

int _test_int() {
	mu_start();
	mu_check_smintf("I have 100 gecs\n", "I have %d gecs\n", 100);
	mu_check_smintf("I need 4 more\n", "I need %d more\n", 4);
	mu_check_smintf("My net gain is -8\n","My net gain is %d\n", -8);
	mu_end();
}

int _test_nums() {
	mu_start();
	mu_check_smintf("100 gecs in hex is 0x64 and it is 0b1100100 in binary", "%d gecs in hex is %x and it is %b in binary", 100, 100, 0x64);
	mu_check_smintf("10 in hex is 0xa", "%d in hex is %x", 10,10);
	mu_check_smintf("-16 is -0x10 in hex", "%d is %x in hex", -16, -16);
	mu_end();
}

int _test_percent() {
	mu_start();
	mu_check_smintf("%", "%%");
	//mu_check_smintf("%%%%", "%%%");
	mu_check_smintf("2% of 4 is 4% of 2\n","2%% of %d is %d%% of 2\n", 4, 4);
	mu_end();
}

int _test_dollar() {
	mu_start();
	mu_check_smintf("I have $2.00","I have %$", 200);
	mu_check_smintf("$2.00 + $2.00 = $4.00","%$ + %$ = %$", 200,200,400);
	mu_check_smintf("My net worth is -$40.00","My net worth is %$", -4000);
	mu_check_smintf("My net worth now is $21474836.47", "My net worth now is %$", INT_MAX);
	mu_end();
}

int _test_words() {
	mu_start();
	mu_check_smintf("I will c u l8r", "I will %c %c %s", 'c', 'u', "l8r");
	mu_check_smintf("My name is Bob", "My name is %s", "Bob");
	mu_end();
}

int main(int argc, char* argv[]) {
	mintf("%%x\n", 1);
	mintf("%%%%%\n");
	mintf("I have 100 gecs\n");
	mintf("I have %x gecs\n", 100);
	mintf("give me %$\n", 200);
	mintf("2%% of %d is %d%% of 2\n", 4, 4);
	mintf("My net worth now is %$\n", INT_MAX);
	mintf("My weight is %d\n", INT_MIN);
	mintf("I will %c %c %s\n", 'c', 'u', "l8r");
	mintf("My name is %s\n", "Bob");

	mu_run(_test_space_string);
	mu_run(_test_simple_string);
	mu_run(_test_int);
	mu_run(_test_nums);
	mu_run(_test_percent);
	mu_run(_test_dollar);
	mu_run(_test_words);

	return EXIT_SUCCESS;


}

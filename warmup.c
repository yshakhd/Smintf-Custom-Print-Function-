 /* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char* my_strdup(const char* original) {
	int original_len = 1;
	for(int j = 0; original[j] != '\0'; j++) {
		original_len++;
	}
	char* copy = malloc(original_len * sizeof(*copy));
	for(int i = 0; i < original_len; i++) {
		copy[i] = original[i];
	}
	return copy;
}

int main(int argc, char *argv[]) {
	char s[] = "abc\n";
	fputs(s, stdout);  // Should print "abc" followed by a newline ('\n')

	char* t = my_strdup(s);
	fputs(t, stdout);  // Should print "abc" followed by a newline ('\n')
	free(t);

	return EXIT_SUCCESS;
}

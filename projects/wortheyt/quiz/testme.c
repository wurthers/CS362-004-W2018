#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const int STRSIZE = 5;

char inputChar() {

	char c;
	char *pool = "[({ ax})]";

	c = pool[rand() % strlen(pool)]; // Test with only state-defining characters
	// c = (char) (rand() % 94) + 32;		// Test with all printable ASCII characters

	return c;
}

char* inputString()
{

	char c;
	char *temp = malloc(sizeof(char) * 16);

	char *pool = "rest";

	int i;

	for (i = 0; i < STRSIZE; i++){			// Limit to length of target string
		c = pool[rand() % strlen(pool)]; // Test with only letters in target string
		// c = (char) (rand() % 26) + 97;		// Test with all lowercase letters
		temp[i] = c;
	}

	temp[i] = '\0';
	return temp;
}

void testme()
{
	int tcCount = 0;
	int state = 0;
	while (1)
	{
		char c;
		char *s;
		tcCount++;
		c = inputChar();
		s = inputString();
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

		if (c == '[' && state == 0) state = 1;
		if (c == '(' && state == 1) state = 2;
		if (c == '{' && state == 2) state = 3;
		if (c == ' ' && state == 3) state = 4;
		if (c == 'a' && state == 4) state = 5;
		if (c == 'x' && state == 5) state = 6;
		if (c == '}' && state == 6) state = 7;
		if (c == ')' && state == 7) state = 8;
		if (c == ']' && state == 8) state = 9;
		if (s[0] == 'r' && s[1] == 'e'
			 && s[2] == 's' && s[3] == 'e'
			 && s[4] == 't' && s[5] == '\0'
			 && state == 9)
		{
			printf("error ");
			exit(200);
		}

	}
}


int main(int argc, char *argv[])
{
		srand(time(NULL));
		testme();
		return 0;
}

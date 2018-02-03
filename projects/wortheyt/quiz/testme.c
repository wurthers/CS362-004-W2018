#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const int STRSIZE = 5;

char inputChar() {

	char c;
	char *pool = "[({ ax})]";

	// c = pool[rand() % strlen(pool)];
	c = (char) (rand() % 94) + 32;

	return c;
}

int inputString(char* s)
{

	char c;
	char temp[16];

	char *pool = "rest";

	int i;

	for (i = 0; i < STRSIZE; i++){
		// c = pool[rand() % strlen(pool)];
		c = (char) (rand() % 26) + 97;
		temp[i] = c;
	}



	temp[i] = '\0';
	memcpy(s, temp, strlen(temp));

}

void testme()
{
	int tcCount = 0;
	int state = 0;
	while (1)
	{
		char c;
		char s[6] = {'\0'};
		tcCount++;
		c = inputChar();
		inputString(s);
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

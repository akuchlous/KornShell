#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const int TotalAlphabets = 26;

/* Least common multiple */
int LCM(int a, int b)
{
    int prime[] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23
    };
    int mult = 1;
    if ((a == 0) || (b == 0)) {
	return 1;
    }
    for (int i = 0; i <= 9; i++) {
	while (a % prime[i] == 0 && b % prime[i] == 0) {
	    a = a / prime[i];
	    b = b / prime[i];
	    mult = mult * prime[i];
	}
	while (a && (a % prime[i] == 0)) {
	    a = a / prime[i];
	    mult = mult * prime[i];
	}
	while (b && (b % prime[i] == 0)) {
	    b = b / prime[i];
	    mult = mult * prime[i];
	}
	if (1 == a && 1 == b)
	    break;
    }
    return mult;
}

/* given a random name , returns the unique characters in tha name */
int findUniqueCharacters(const char *firstName, const char *lastname)
{
    int array[26];
    bzero(array, 26 * sizeof(int));
    int nameLen = strlen(firstName);
    for (int i = 0; i < nameLen; i++) {
	array[toupper(firstName[0]) - 'A'] = 1;
    }
    nameLen = strlen(lastname);
    for (int i = 0; i < nameLen; i++) {
	array[toupper(lastname[0]) - 'A'] = 1;
    }
    int count = 0;
    for (int i = 0; i < 26; i++) {
	count += array[i];
    }
    return count;
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
	printf("Error :\n\t usage : a.out <first name> <last name>\n");
	return -1;
    }
    char *firstName = argv[1];
    char *lastName = (argc > 3) ? argv[3] : argv[2];

    // int uniqChar = findUniqueCharacters(firstName, lastName);
    // printf("Max Steps : %d\n", Cost(TotalAlphabets, uniqChar));
    printf("LCM : %d\n", LCM(atoi(firstName), atoi(lastName)));
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int TotalAlphabets = 26;
int subTreeCost[26][26];

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

/* 
  calculate cost of subproblem with total number of chararacters = charSpace
  and uniq characters = uniqSpace
*/

int CalculateSubTreeCost(int charSpace, int uniqSpace)
{
    int maxCost =  charSpace;
    if (charSpace == 0 || uniqSpace == 0) {
       return 1;
    }
    if (subTreeCost[charSpace-1][uniqSpace-1]) {
        return subTreeCost[charSpace-1][uniqSpace-1];
    }
    for (int i = charSpace-1; i >= 0; i--) {
	for (int j = uniqSpace; j >= 1; j--) {
	   int subCost = LCM (
	                 CalculateSubTreeCost(i,j),
			 CalculateSubTreeCost(charSpace-i, uniqSpace-j));
           maxCost = (maxCost>subCost)?maxCost:subCost;
	}
    }
    subTreeCost[charSpace-1][uniqSpace-1] = maxCost;
    return maxCost;
}

int distance(char C)
{
    int retVal = -1;
    if (C >= 'A' && C <= 'Z') {
	retVal = C - 'A';
    } else if (C >= 'a' && C <= 'z') {
	retVal = C - 'a';
    } else {
	printf("Error: cannot handle character %c\n", C);
    }
    return retVal;
}

/* given a random name , dins the unique characters in tha name */
/* accpts only A-Z */

int findUniqueCharacters(const char *firstName, const char *lastname)
{
    int array[26];
    bzero(array, 26 * sizeof(int));
    int nameLen = strlen(firstName);
    for (int i = 0; i < nameLen; i++) {
	int retVal = distance(firstName[i]);
	if (retVal == -1) {
	    return -1;
	}
	array[retVal] = 1;
    }
    nameLen = strlen(lastname);
    for (int i = 0; i < nameLen; i++) {
	int retVal = distance(lastname[i]);
	if (retVal == -1) {
	    return -1;
	}
	array[retVal] = 1;
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
    bzero(subTreeCost, 26 * 26 * sizeof(int));

    int uniqChar = findUniqueCharacters(firstName, lastName);

    if (-1 == uniqChar) {
	printf("Error :\n\t usage : a.out <first name> <last name>\n");
	printf("\t\t chracters can be only in range A-Z a-z\n");
	return -1;
    } else {
	printf("Max Steps : %d\n",
	       CalculateSubTreeCost(TotalAlphabets, uniqChar));
    }
}

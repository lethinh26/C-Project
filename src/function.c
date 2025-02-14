#include <string.h>
#include <stdio.h>
#include "../include/function.h"

int inputChoice() {
	int choice;
	printf(">> Enter the choice: ");
	scanf("%d", &choice);
	return choice;
}

char confirmExitOrBack() {
	char choice;
	printf(">> Go back(b)? or exit(0)?: ");
	fflush(stdin);
	scanf("%c", &choice);
	fflush(stdin);
	return choice;
}

void inputCharValue(char *input, int max, char *value) {
	char temp[max+1];
	do {
		printf("%s: ", input);
		fflush(stdin);

		fgets(temp, max+1, stdin);

		if (strcmp(temp, "\n") == 0) {
			printf("Error: Field required. Cannot be blank\n");
			continue;
		}

		temp[strcspn(temp, "\n")] = '\0';


		if (strlen(temp) == max) {
			printf("Error: Character limit exceeded\n");
			continue;
		}

		break;
	} while (1);
	strcpy(value, temp);
}

void inputIntValue(char *input, int *value) {
	int temp;
	do {
		printf("%s: ", input);
		fflush(stdin);
		scanf("%d", &temp);
		if (temp < 0) {
			printf("Error: Value cannot be less than 1\n");
			continue;
		}
		break;
	}while (1);
	*value = temp;
}

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/function.h"
#include "../include/category.h"
#include "../include/datatype.h"
#include "../include/product.h"

void workBinaryFile(const char *filePath, char *mode, void *data, int *current, int currentStruct) {
	FILE *fptr = fopen(filePath, mode);
	if (fptr == NULL) {
		printf("Loi mo file");
		return;
	}
	if (strcmp(mode, "wb") == 0) {
		fwrite(data, currentStruct, *current, fptr);
	}else {
		*current = fread(data, currentStruct, 100, fptr);
	}
	fclose(fptr);
}

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

void showAdminMenu() {
	while (1) {
		system("cls");
		printf("%20s\n", "ADMIN MENU");
		printf("==============================\n");
		printf("1. Manage Category\n");
		printf("2. Manage Product\n");
		printf("3. Exit\n");
		printf("==============================\n");
		int choice = inputChoice();
		switch (choice) {
			case 1:
				manageCategory();
				break;
			case 2:
				manageProduct();
				break;
			case 3:
				return;
			default:
				printf("Error: Invalid choice");
				break;
		}
	}
}

void loginAdmin() {
	char nameFile[10];
	char passFile[10];
	FILE *fptr = fopen("../data/accountAdmin.txt", "r");
	if (fptr == NULL) {
		printf("Loi mo file");
	}
	fgets(nameFile, 10, fptr);
	nameFile[strcspn(nameFile, "\n")] = '\0';
	fgets(passFile, 10, fptr);
	passFile[strcspn(passFile, "\n")] = '\0';

	while (1) {
		char temp[2];
		char username[10];
		char password[10];
		system("cls");
		printf("%18s\n", "ADMIN LOGIN");
		printf("==========================\n");
		inputCharValue("Username", sizeof(username), username);
		inputCharValue("Password", sizeof(password), password);
		printf("==========================\n\n");

		if (strcmp(username, nameFile) == 0 && strcmp(password, passFile) == 0) {
			printf("***Login Successful****\n");
			printf(">> Press [Enter] to go to the main menu");
			fgets(temp, 2, stdin);
			break;
		}
		printf("Error: username or password is incorrect\n");
		printf(">> Press [Enter] to retry");

		fgets(temp, 2, stdin);
	}
	showAdminMenu();
}

void loginUser() {
	while (1) {
		char temp[2];
		char username[10];
		char password[10];
		system("cls");
		printf("%18s\n", "USER LOGIN");
		printf("==========================\n");
		inputCharValue("Username", sizeof(username), username);
		inputCharValue("Password", sizeof(password), password);
		printf("==========================\n\n");

		int check = 0;
		for (int i = 0; i < currentUser; i++) {
			if (strcmp(dataUser[i].customerId, username) == 0) {
				if (strcmp(dataUser[i].password, password) == 0) {
					check = 1;
					break;
				}
			}
		}
		if (check) {
			printf("***Login Successful****\n");
			printf(">> Press [Enter] to go to the main menu");
			fgets(temp, 2, stdin);
			break;
		}

		printf("Error: username or password is incorrect\n");
		printf(">> Press [Enter] to retry");

		fgets(temp, 2, stdin);
	}
	manageUser();
}

void regUser() {
	while (1) {
		char temp[2];
		char password[sizeof(dataUser->password)];
		char username[sizeof(dataUser->customerId)];
		char nameDisplay[sizeof(dataUser->customerName)];
		char passwordConfirm[sizeof(dataUser->password)];

		system("cls");

		printf("%18s\n", "USER REGISTER");
		printf("==========================\n");
		inputCharValue("Username", sizeof(username), username);
		inputCharValue("Display Name", sizeof(nameDisplay), nameDisplay);
		inputCharValue("Password", sizeof(password), password);
		inputCharValue("Confirm your password", sizeof(passwordConfirm), passwordConfirm);
		printf("==========================\n\n");

		int check = 0;
		for (int i = 0; i < currentUser; i++) {
			if (strcmp(username, dataUser[i].customerName) == 0) {
				check = 1;
				break;
			}
		}
		if (check) {
			printf("Error: This username is already taken\n");
			printf(">> Press [Enter] to retry");
			fgets(temp, 2, stdin);
			continue;
		}

		if (strcmp(passwordConfirm, password) == 0) {
			strcpy(dataUser[currentUser].customerName, nameDisplay);
			strcpy(dataUser[currentUser].customerId, username);
			strcpy(dataUser[currentUser].password, password);
			currentUser++;

			workBinaryFile(fileUser, "wb", dataUser, &currentUser, sizeof(struct User));
			printf("***Register Successful****\n");
			printf(">> Press [Enter] to go to the main menu");
			fgets(temp, 2, stdin);
			break;
		}
		printf("Error: Passwords do not match\n");
		printf(">> Press [Enter] to retry");
		fgets(temp, 2, stdin);
	}
		manageUser();
}
void userMenu() {
	workBinaryFile(fileUser, "rb", dataUser, &currentUser, sizeof(struct User));
	while (1) {
		system("cls");
		printf("%25s\n", "User Authentication");
		printf("==============================\n");
		printf("1. Login\n");
		printf("2. Register\n");
		printf("3. Exit\n");
		printf("==============================\n");
		int choice = inputChoice();
		switch (choice) {
			case 1:
				loginUser();
				break;
			case 2:
				regUser();
				break;
			case 3:
				return;
			default:
				printf("Error: Invalid choice");
				break;
		}
	}
}

void showMainMenu() {
	while (1) {
		system("cls");
		printf("%20s\n", "ROLE");
		printf("==============================\n");
		printf("1. Admin\n");
		printf("2. User\n");
		printf("3. Exit\n");
		printf("==============================\n");
		int choice = inputChoice();
		switch (choice) {
			case 1:
				loginAdmin();
				break;
			case 2:
				userMenu();
				break;
			case 3:
				return;
			default:
				printf("Error: Invalid choice");
				break;
		}
	}
}
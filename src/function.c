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

void billList(int userPos, int page, int totalProduct, int isAdmin) {
	system("cls");
	char date[20] = "";
	sprintf(date, "%d%s%d%s%d", dataUser[userPos].order[page].date.day, "/" ,dataUser[userPos].order[page].date.month, "/" ,dataUser[userPos].order[page].date.year);
	printf("|==================================================|\n");
	printf("|%27s%23s|\n","RECEIPT", "");
	printf("|--------------------------------------------------|\n");
	printf("|%-35s%15s|\n","Order ID:",dataUser[userPos].order[page].orderId);
	printf("|%-35s%15s|\n","Customer ID:", dataUser[userPos].customerId);
	printf("|%-35s%15s|\n","Date:", date);
	printf("|--------------------------------------------------|\n");
	printf("|%-20s%-10s%-10s%-10s|\n", "Product", "Price", "Amount", "Total");
	printf("|--------------------------------------------------|\n");
	for (int i = 0; i < totalProduct; i++) {
		printf("|%-20s%-10d%-10d%-10d|\n", dataUser[userPos].order[page].product[i].productName, dataUser[userPos].order[page].product[i].price, dataUser[userPos].order[page].product[i].quantity, dataUser[userPos].order[page].product[i].quantity*dataUser[userPos].order[page].product[i].price);
	}
	printf("|--------------------------------------------------|\n");
	printf("|%-35s%15d|\n", "TOTAL:", dataUser[userPos].order[page].totalPrice);
	printf("|--------------------------------------------------|\n");
	printf("|%28s%22s|\n", "THANK YOU", "");
	printf("|==================================================|\n\n");
	if (isAdmin == 0) {
		printf("%-19s--PAGE %d/%d--\n\n", "", page+1, totalUserOrder);
	}
}

int switchPage(int *page) {
	do {
		printf("Press < to back, > to next, b for menu\n");
		printf("Enter your choice: ");

		char choice[2];
		fflush(stdin);
		fgets(choice, 2, stdin);
		choice[strcspn(choice, "\n")] = '\0';
		if (strcmp(choice, "<") == 0) {
			if (*page > 0) {
				(*page)--;
			}else {
				printf("You are on the first page\n");
			}
		}else if (strcmp(choice, ">") == 0) {
			if (*page < totalUserOrder-1) {
				(*page)++;
			}else {
				printf("You are on the last page\n");
			}
		}else if (strcmp(choice, "b") == 0) {
			return 1;
		}else {
			printf("Error: Invalid choice\n");
			continue;
		}
		break;
	} while (1);
	system("cls");
	return 0;
}

int inputChoice() {
	int choice;
	printf(">> Enter the choice: ");
	scanf("%d", &choice);
	return choice;
}

char confirmChoice(char *input) {
	char choice;
	printf(">> %s", input);
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
			printf("Error: Character limit exceeded (max: %d)\n", max-1);
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
		printf("3. View Bill List\n");
		printf("4. View Revenue\n");
		printf("5. Exit\n");
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
				menuOrder();
				break;
			case 4:
				showRevenue();
				break;
			case 5:
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
	int userPos = 0;
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
					userPos = i;
					totalUserOrder = dataUser[i].totalOrder;
					totalCart = dataUser[i].totalCart;
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

	manageUser(userPos);
}

void regUser() {
	int userPos = currentUser;
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
		if (username[strcspn(username, " ")] != strlen(username)) {
			printf("Error: Username cannot contain spaces\n");
			printf(">> Press [Enter] to retry");
			fgets(temp, 2, stdin);
			continue;
		}
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
			dataUser[currentUser].totalOrder = 0;

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
		manageUser(userPos);
}
void userMenu() {
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
	workBinaryFile(fileUser, "rb", dataUser, &currentUser, sizeof(struct User));
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
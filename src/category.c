#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/function.h"
#include "../include/category.h"
#include "../include/datatype.h"

void showCategory() {
	if (currentCate == 0) {
		printf("The category is empty!\n");
		return;
	}
	printf("|%-20s|%-10s|\n", "====================", "==========");
	printf("|%-20s|%-10s|\n", "Name", "ID");
	printf("|%-20s|%-10s|\n", "====================", "==========");
	for (int i = 0; i < currentCate; i++) {
		printf("|%-20s|%-10s|\n", dataCate[i].categoryName, dataCate[i].categoryId);
		printf("|%-20s|%-10s|\n", "--------------------", "----------");
	}
}

void infoCategory(int pos) {
	printf("%21s\n", "Category Information");
	printf("--------------------------\n");
	printf("Name: %s\n", dataCate[pos].categoryName);
	printf("ID: %s\n", dataCate[pos].categoryId);
	printf("--------------------------\n\n");
}

int findPosCategory() {
	while (1) {
		char id[sizeof(dataCate->categoryId)];
		inputCharValue("Enter the category ID", sizeof(dataCate->categoryId), id);

		for (int i = 0; i < currentCate; i++) {
			if (strcmp(dataCate[i].categoryId, id) == 0) {
				return i;
			}
		}
		printf("Error: ID not found\n");
	}
}

void addCategory() {
	char id[sizeof(dataCate->categoryId)];
	int check = 1;
	do {
		inputCharValue("Enter the category ID", sizeof(dataCate->categoryId), id);
		check = 0;
		for (int i = 0; i < currentCate; i ++) {
			if (strcmp(id, dataCate[i].categoryId) == 0) {
				printf("Error: This ID is already exists\n");
				check = 1;
			}
		}
	} while(check);
	strcpy(dataCate[currentCate].categoryId, id);

	inputCharValue("Enter the category name", sizeof(dataCate->categoryName), dataCate[currentCate].categoryName);

	(currentCate)++;
	workBinaryFile(fileCate, "wb", dataCate, &currentCate, sizeof(struct Category));
	printf("Category added successfully\n");
}

void editCategory() {
	char name[sizeof(dataCate->categoryName)];
	int pos = findPosCategory(dataCate, currentCate);
	infoCategory(pos);

	printf("\t **** Update The New Category ****\n");
	inputCharValue("Enter the new name (0 for skip)", sizeof(dataCate->categoryName), name);

	if (strcmp(name, "0") != 0) {
		strcpy(dataCate[pos].categoryName, name);
	}

	workBinaryFile(fileCate, "wb", dataCate, &currentCate, sizeof(struct Category));
	printf("Category Updated Successfully\n");
}

void deleteCategory() {
	int pos = findPosCategory(dataCate, currentCate);
	infoCategory(pos);
	do {
		char answer = confirmChoice("Confirm delete [Y/N]: ");
		if (answer == 'Y') {
			break;
		}else if (answer == 'N') {
			return;
		}
	}while (1);


	for (int i = pos; i < currentCate-1; i++) {
		dataCate[i] = dataCate[i+1];
	}
	(currentCate)--;
	workBinaryFile(fileCate, "wb", dataCate, &currentCate, sizeof(struct Category));
	printf("Category Deleted Successfully\n");
}

void findCategory() {
	char name[sizeof(dataCate->categoryName)];
	inputCharValue("Enter the category name", sizeof(dataCate->categoryName), name);

	int check = 1;
	for (int i = 0; i < currentCate; i++) {
		if (strstr(dataCate[i].categoryName, name) != NULL) {
			if (check) {
				printf("|%-20s|%-10s|\n", "====================", "==========");
				printf("|%-20s|%-10s|\n", "Name", "ID");
				printf("|%-20s|%-10s|\n", "====================", "==========");
			}
			printf("|%-20s|%-10s|\n", dataCate[i].categoryName, dataCate[i].categoryId);
			printf("|%-20s|%-10s|\n", "--------------------", "----------");
			check = 0;
		}
	}
	if (check) {
		printf("Error: Name not found\n");
	}
}

void ascendSortCate() {
	for (int i = 0; i < currentCate-1; i++) {
		for (int j = 0; j < currentCate-i-1; j++) {
			if (strcmp(dataCate[j].categoryName, dataCate[j+1].categoryName) > 0) {
				struct Category temp = dataCate[j];
				dataCate[j] = dataCate[j+1];
				dataCate[j+1] = temp;
			}
		}
	}
	printf("Category Sorted Successfully\n");
}

void descendSortCate() {
	for (int i = 0; i < currentCate-1; i++) {
		for (int j = 0; j < currentCate-i-1; j++) {
			if (strcmp(dataCate[j].categoryName, dataCate[j+1].categoryName) < 0) {
				struct Category temp = dataCate[j];
				dataCate[j] = dataCate[j+1];
				dataCate[j+1] = temp;
			}
		}
	}
	printf("Category Sorted Successfully\n");
}

void menuSortCate() {
	system("cls");
	printf("%20s\n", "SORT MENU");
	printf("==============================\n");
	printf("1. Sort Ascending\n");
	printf("2. Sort Descending\n");
	printf("==============================\n");
	int choice = inputChoice();
	switch (choice) {
		case 1:
			ascendSortCate();
			break;
		case 2:
			descendSortCate();
			break;
		default:
			printf("Error: Invalid Choice");
			break;
	}
}

void showCategoryMenu() {
	system("cls");
	printf("%20s\n", "CATEGORY MENU");
	printf("==============================\n");
	printf("1. Show all categories\n");
	printf("2. Add a new catgory\n");
	printf("3. Edit a category\n");
	printf("4. Delete a category\n");
	printf("5. Find a category\n");
	printf("6. Sort category\n");
	printf("7. Exit\n");
	printf("==============================\n");
}

void manageCategory() {
	workBinaryFile(fileCate, "rb", dataCate, &currentCate, sizeof(struct Category));
	while (1) {
		showCategoryMenu();
		int choice = inputChoice();
		switch (choice) {
			case 1:
				showCategory();
			break;
			case 2:
				addCategory();
			break;
			case 3:
				editCategory();
			break;
			case 4:
				deleteCategory();
			break;
			case 5:
				findCategory();
			break;
			case 6:
				menuSortCate();
			break;
			case 7:
				return;
			default:
				printf("Error: Invalid Choice");
			break;
		}
		while (1) {
			char answer = confirmChoice("Go back(b)? or exit(0)?: ");
			if (answer == '0') {
				return;
			}else if (answer == 'b') {
				break;
			}
		}
	}
}

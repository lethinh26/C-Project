#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/function.h"
#include "../include/product.h"
#include "../include/datatype.h"

struct Product dataProU[100];
struct Category dataCategoryU[100];
int currentCategoryU = 0;
int currentProU = 0;

void productFile(char *mode) {
	FILE *fptrPro = fopen("../data/product.bin", mode);
	FILE *fptrCate = fopen("../data/category.bin", "rb");
	if (fptrPro == NULL  || fptrCate == NULL) {
		printf("Loi mo file\n");
		return;
	}
	if (strcmp(mode, "wb") == 0) {
		fwrite(dataPro, sizeof(struct Product), currentPro, fptrPro);
	}else {
		currentPro = fread(dataPro, sizeof(struct Product), 100, fptrPro);
		currentCategory = fread(dataCategory, sizeof(struct Category), 100, fptrCate);
	}
	fclose(fptrPro);
	fclose(fptrCate);
}

void showProductUser() {
	if (currentPro == 0) {
		printf("The product is empty!");
		return;
	}
	printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "============", "============", "====================", "============", "============");
	printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "Product ID", "Category Name", "Product Name", "Quantity", "Price");
	printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "============", "============", "====================", "============", "============");
	for (int i = 0; i < currentPro; i++) {
		printf("|%-12s|%-12s|%-20s|%-12d|%-12d|\n", dataPro[i].productId, dataPro[i]., dataPro[i].productName, dataPro[i].quantity, dataPro[i].price);
		printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "------------", "------------", "--------------------", "------------", "------------");
	}
}

int findPosProduct() {
	while (1) {
		char id[sizeof(dataPro->productId)];
		inputCharValue("Enter the product ID: ", sizeof(id), id);

		for (int i = 0; i < currentPro; i++) {
			if (strcmp(id, dataPro[i].productId) == 0) {
				return i;
			}
		}
		printf("Error: Invalid ID\n");
	}

}

void infoProduct(int pos) {
	printf("%21s\n", "Category Information");
	printf("--------------------------\n");
	printf("Product ID: %s\n", dataPro[pos].productId);
	printf("Category ID: %s\n", dataPro[pos].categoryId);
	printf("Name: %s\n", dataPro[pos].productName);
	printf("Quantity: %d\n", dataPro[pos].quantity);
	printf("price: %d\n", dataPro[pos].price);
	printf("--------------------------\n\n");
}
void addProduct() {
	char productId[sizeof(dataPro->productId)];
	int check = 1;
	do {
		inputCharValue("Enter the product ID: ", sizeof(productId), productId);

		check = 0;
		for (int i = 0; i < currentPro; i ++) {
			if (strcmp(productId, dataPro[i].productId) == 0) {
				printf("Error: This ID is already exists\n");
				check = 1;
			}
		}
	} while(check);
	strcpy(dataPro[currentPro].productId, productId);

	char categoryId[sizeof(dataCategory->categoryId)];
	check = 1;
	do {
		inputCharValue("Enter the category ID: ", sizeof(categoryId), categoryId);

		check = 1;
		for (int i = 0; i < currentCategory; i ++) {
			if (strcmp(categoryId, dataCategory[i].categoryId) == 0) {
				check = 0;
				break;
			}
		}
		if (check) {
			printf("Error: Invalid ID\n");
		}
	} while(check);
	strcpy(dataPro[currentPro].categoryId, categoryId);

	inputCharValue("Enter the product name: ", sizeof(dataPro->productName), dataPro[currentPro].productName);
	inputIntValue("Enter the quantity", &dataPro[currentPro].quantity);
	inputIntValue("Enter the price", &dataPro[currentPro].price);

	(currentPro)++;
	productFile("wb");
	printf("Product added successfully\n");
}

void editProduct() {
	char categoryId[sizeof(dataCategory->categoryId)];
	char productName[sizeof(dataPro->productName)];
	int quantity;
	int price;

	int pos = findPosProduct(dataCategory, currentCategory);
	infoProduct(pos);

	printf("\t **** Update The New Category ****\n");
	int check = 1;
	do {
		inputCharValue("Enter the new category ID (0 for skip)", sizeof(categoryId), categoryId);

		if (strcmp(categoryId, "0") != 0) {
			for (int i = 0; i < currentCategory; i++) {
				if (strcmp(dataCategory[i].categoryId, categoryId) == 0) {
					strcpy(dataPro[pos].categoryId, categoryId);
					check = 0;
					break;
				}
			}
		} else if (strcmp(categoryId, "0") == 0) {
			check = 0;
		}
		if (check) {
			printf("Error: ID not found\n");
		}
	} while (check);

	inputCharValue("Enter the new product name (0 for skip)", sizeof(productName), productName);
	if (strcmp(productName, "0") != 0) {
		strcpy(dataPro[pos].productName, productName);
	}

	inputIntValue("Enter the new quantity (0 for skip)", &quantity);
	if (quantity != 0) {
		dataPro[pos].quantity = quantity;
	}

	inputIntValue("Enter the new price (0 for skip)", &price);
	if (price != 0) {
		dataPro[pos].price = price;
	}

	productFile("wb");
	printf("Product Updated Successfully\n");
}

void deleteProduct() {
	int pos = findPosProduct();
	infoProduct(pos);

	for (int i = pos; i < currentPro-1; i++) {
		dataPro[i] = dataPro[i+1];
	}
	currentPro--;
	productFile("wb");
	printf("Product Deleted Successfully\n");
}

void findProduct() {
	char name[sizeof(dataPro->productName)];
	inputCharValue("Enter the product name: ", sizeof(name), name);

	int check = 1;
	for (int i = 0; i < currentPro; i++) {
		if (strstr(dataPro[i].productName, name) != NULL) {
			if (check == 1) {
				printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "============", "============", "====================", "============", "============");
				printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "Product ID", "Category ID", "Product Name", "Quantity", "Price");
				printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "============", "============", "====================", "============", "============");
			}
			printf("|%-12s|%-12s|%-20s|%-12d|%-12d|\n", dataPro[i].productId, dataPro[i].categoryId, dataPro[i].productName, dataPro[i].quantity, dataPro[i].price);
			printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "------------", "------------", "--------------------", "------------", "------------");
			check = 0;
		}
	}
	if (check) {
		printf("Error: Name not found\n");
	}
}

void ascendSortPro() {
	for (int i = 0; i < currentPro-1; i++) {
		for (int j = 0; j < currentPro-i-1; j++) {
			if (dataPro[j].price > dataPro[j+1].price) {
				struct Product temp = dataPro[j];
				dataPro[j] = dataPro[j+1];
				dataPro[j+1] = temp;
			}
		}
	}
	printf("Product Sorted Successfully\n");
}

void descendSortPro() {
	for (int i = 0; i < currentPro-1; i++) {
		for (int j = 0; j < currentPro-i-1; j++) {
			if (dataPro[j].price < dataPro[j+1].price) {
				struct Product temp = dataPro[j];
				dataPro[j] = dataPro[j+1];
				dataPro[j+1] = temp;
			}
		}
	}
	printf("Product Sorted Successfully\n");
}

void menuSortPro() {
	system("cls");
	printf("%20s\n", "SORT MENU");
	printf("==============================\n");
	printf("1. Sort Ascending\n");
	printf("2. Sort Descending\n");
	printf("==============================\n");
	int choice = inputChoice();
	switch (choice) {
		case 1:
			ascendSortPro();
			break;
		case 2:
			descendSortPro();
			break;
		default:
			printf("Error: Invalid Choice\n");
			break;
	}
}

void nameFilter() {
	char name[sizeof(dataCategory->categoryName)];
	char id[10];
	inputCharValue("Enter the category name: ", sizeof(name), name);

	int checkCate = 1;
	for (int i = 0; i < currentCategory; i++) {
		if (strcmp(name, dataCategory[i].categoryName) == 0) {
			strcpy(id, dataCategory[i].categoryId);
			checkCate = 0;
			break;
		}
	}
	if (checkCate) {
		printf("Error: Category name not found\n");
		return;
	}

	int checkPro = 1;
	for (int i = 0; i < currentPro; i++) {
		if (strcmp(id, dataPro[i].categoryId) == 0) {
			if (checkPro) {
				printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "============", "============", "====================", "============", "============");
				printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "Product ID", "Category ID", "Product Name", "Quantity", "Price");
				printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "============", "============", "====================", "============", "============");
			}
			printf("|%-12s|%-12s|%-20s|%-12d|%-12d|\n", dataPro[i].productId, dataPro[i].categoryId, dataPro[i].productName, dataPro[i].quantity, dataPro[i].price);
			printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "------------", "------------", "--------------------", "------------", "------------");
			checkPro = 0;
		}
	}
	if (checkPro) {
		printf("This category has no products!\n");
	}
}
void priceFilter() {
	int min;
	int max;

	inputIntValue("Enter the min price", &min);
	inputIntValue("Enter the max price", &max);

	int check = 1;
	for (int i = 0; i < currentPro; i++) {
		if ((dataPro[i].price >= min) && (dataPro[i].price <= max)) {
			if (check) {
				printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "============", "============", "====================", "============", "============");
				printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "Product ID", "Category ID", "Product Name", "Quantity", "Price");
				printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "============", "============", "====================", "============", "============");
			}
			printf("|%-12s|%-12s|%-20s|%-12d|%-12d|\n", dataPro[i].productId, dataPro[i].categoryId, dataPro[i].productName, dataPro[i].quantity, dataPro[i].price);
			printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "------------", "------------", "--------------------", "------------", "------------");
			check = 0;
		}
	}
	if (check) {
		printf("There are no products priced between %d and %d\n", min, max);
	}
}
void showUserMenu() {
	printf("%20s\n", "USER MENU");
	printf("==============================\n");
	printf("1. Show all products\n");
	printf("2. Find product\n");
	printf("3. Sort product\n");
	printf("4. Filter product\n");
	printf("5. Buy product\n");
	printf("6. Exit\n");
	printf("==============================\n");
}

void menuFilter() {
	system("cls");
	printf("%20s\n", "Filter MENU");
	printf("==============================\n");
	printf("1. Filter by name\n");
	printf("2. Filter by price\n");
	printf("==============================\n");
	int choice = inputChoice();
	switch (choice) {
		case 1:
			nameFilter();
			break;
		case 2:
			priceFilter();
			break;
		default:
			printf("Error: Invalid Choice\n");
			break;
	}
}

void manageProduct() {
	productFile("rb");
	while (1) {
		system("cls");
		showProductMenu();
		int choice = inputChoice();
		switch (choice) {
			case 1:
				showProduct();
				break;
			case 2:
				addProduct();
				break;
			case 3:
				editProduct();
				break;
			case 4:
				deleteProduct();
				break;
			case 5:
				findProduct();
				break;
			case 6:
				menuSortPro();
				break;
			case 7:
				menuFilter();
				break;
			case 8:
				return;
			default:
				printf("Error: Invalid Choice\n");
			break;
		}
		while (1) {
			char answer = confirmExitOrBack();
			if (answer == '0') {
				return;
			}else if (answer == 'b') {
				break;
			}
		}
	}
}
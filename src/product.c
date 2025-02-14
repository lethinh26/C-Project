#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/function.h"
#include "../include/product.h"
#include "../include/datatype.h"

struct Product dataPro[100];
int currentPro = 0;
struct Category dataCategory[100];
int currentCategory = 0;

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

void showProduct() {
	if (currentPro == 0) {
		printf("The product is empty!");
		return;
	}
	printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "============", "============", "============", "============", "============");
	printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "Product ID", "Category ID", "Product Name", "Quantity", "Price");
	printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "============", "============", "============", "============", "============");
	for (int i = 0; i < currentPro; i++) {
		printf("|%-12s|%-12s|%-12s|%-12d|%-12d|\n", dataPro[i].productId, dataPro[i].categoryId, dataPro[i].productName, dataPro[i].quantity, dataPro[i].price);
		printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "------------", "------------", "------------", "------------", "------------");
	}
}

int findPosProduct() {
	while (1) {
		char id[10];
		printf("Enter the product ID: ");
		fflush(stdin);
		fgets(id, 10, stdin);
		id[strcspn(id, "\n")] = '\0';

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
	char productId[10];
	int check = 1;
	do {
		printf("Enter the product ID: ");
		fflush(stdin);
		fgets(productId, 10, stdin);
		productId[strcspn(productId, "\n")] = '\0';
		check = 0;
		for (int i = 0; i < currentPro; i ++) {
			if (strcmp(productId, dataPro[i].productId) == 0) {
				printf("Error: This ID is already exists\n");
				check = 1;
			}
		}
	} while(check);
	strcpy(dataPro[currentPro].productId, productId);

	char categoryId[10];
	check = 1;
	do {
		printf("Enter the Category ID: ");
		fflush(stdin);
		fgets(categoryId, 10, stdin);
		categoryId[strcspn(categoryId, "\n")] = '\0';
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

	printf("Enter the product name: ");
	fgets(dataPro[currentPro].productName, 10, stdin);
	dataPro[currentPro].productName[strcspn(dataPro[currentPro].productName, "\n")] = '\0';

	printf("Enter the quantity: ");
	scanf("%d", &dataPro[currentPro].quantity);

	printf("Enter the price: ");
	scanf("%d", &dataPro[currentPro].price);

	(currentPro)++;
	productFile("wb");
	printf("Product added successfully\n");
}

void editProduct() {
	char categoryId[10];
	char productName[20];
	int quantity;
	int price;

	int pos = findPosProduct(dataCategory, currentCategory);
	infoProduct(pos);

	printf("\t **** Update The New Category ****\n");
	int check = 1;
	do {
		printf("Enter the new category ID (0 for skip): ");
		fgets(categoryId, 10, stdin);
		categoryId[strcspn(categoryId, "\n")] = '\0';

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

	printf("Enter the new product name (0 for skip): ");
	fgets(productName, 20, stdin);
	productName[strcspn(productName, "\n")] = '\0';
	if (strcmp(productName, "0") != 0) {
		strcpy(dataPro[pos].productName, productName);
	}

	printf("Enter the new quantity (0 for skip): ");
	scanf("%d", &quantity);
	if (quantity != 0) {
		dataPro[pos].quantity = quantity;
	}

	fflush(stdin);
	printf("Enter the new price (0 for skip): ");
	scanf("%d", &price);
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
	char name[20];
	printf("Enter the name product: ");
	fflush(stdin);
	fgets(name, 20, stdin);
	name[strcspn(name, "\n")] = '\0';

	int check = 1;
	for (int i = 0; i < currentPro; i++) {
		if (strstr(dataPro[i].productName, name) != NULL) {
			if (check == 1) {
				printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "============", "============", "============", "============", "============");
				printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "Product ID", "Category ID", "Product Name", "Quantity", "Price");
				printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "============", "============", "============", "============", "============");
			}
			printf("|%-12s|%-12s|%-12s|%-12d|%-12d|\n", dataPro[i].productId, dataPro[i].categoryId, dataPro[i].productName, dataPro[i].quantity, dataPro[i].price);
			printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "------------", "------------", "------------", "------------", "------------");
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
	char name[20];
	char id[10];
	printf("Enter the category name: ");
	fflush(stdin);
	fgets(name, 20, stdin);
	name[strcspn(name, "\n")] = '\0';

	int checkCate = 1;
	for (int i = 0; i < currentCategory; i++) {
		if (strcmp(name, dataCategory[i].categoryName) == 0) {
			strcpy(id, dataCategory[i].categoryId);
			checkCate = 0;
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
				printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "============", "============", "============", "============", "============");
				printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "Product ID", "Category ID", "Product Name", "Quantity", "Price");
				printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "============", "============", "============", "============", "============");
			}
			printf("|%-12s|%-12s|%-12s|%-12d|%-12d|\n", dataPro[i].productId, dataPro[i].categoryId, dataPro[i].productName, dataPro[i].quantity, dataPro[i].price);
			printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "------------", "------------", "------------", "------------", "------------");
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
	fflush(stdin);
	printf("Enter the min price: ");
	scanf("%d", &min);
	printf("Enter the max price: ");
	scanf("%d", &max);

	int check = 1;
	for (int i = 0; i < currentPro; i++) {
		if ((dataPro[i].price >= min) && (dataPro[i].price <= max)) {
			if (check) {
				printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "============", "============", "============", "============", "============");
				printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "Product ID", "Category ID", "Product Name", "Quantity", "Price");
				printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "============", "============", "============", "============", "============");
			}
			printf("|%-12s|%-12s|%-12s|%-12d|%-12d|\n", dataPro[i].productId, dataPro[i].categoryId, dataPro[i].productName, dataPro[i].quantity, dataPro[i].price);
			printf("|%-12s|%-12s|%-12s|%-12s|%-12s|\n", "------------", "------------", "------------", "------------", "------------");
			check = 0;
		}
	}
	if (check) {
		printf("There are no products priced between %d and %d\n", min, max);
	}
}
void showProductMenu() {
	printf("%20s\n", "Product MENU");
	printf("==============================\n");
	printf("1. Show all products\n");
	printf("2. Add a new product\n");
	printf("3. Edit a product\n");
	printf("4. Delete a product\n");
	printf("5. Find product\n");
	printf("6. Sort product\n");
	printf("7. Filter product\n");
	printf("8. Exit\n");
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
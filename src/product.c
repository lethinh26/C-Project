#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/function.h"
#include "../include/product.h"
#include "../include/datatype.h"

void showProduct() {
	if (currentPro == 0) {
		printf("The product is empty!\n");
		return;
	}

	printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "============", "============", "====================", "============", "============");
	printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "Product ID", "Category ID", "Product Name", "Quantity", "Price");
	printf("|%-12s|%-12s|%-20s|%-12s|%-12s|\n", "============", "============", "====================", "============", "============");
	for (int i = 0; i < currentPro; i++) {
		printf("|%-12s|%-12s|%-20s|%-12d|%-12d|\n", dataPro[i].productId, dataPro[i].categoryId, dataPro[i].productName, dataPro[i].quantity, dataPro[i].price);
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

	char categoryId[sizeof(dataCate->categoryId)];
	check = 1;
	do {
		inputCharValue("Enter the category ID: ", sizeof(categoryId), categoryId);

		check = 1;
		for (int i = 0; i < currentCate; i ++) {
			if (strcmp(categoryId, dataCate[i].categoryId) == 0) {
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
	workBinaryFile(filePro, "wb", dataPro, &currentPro, sizeof(struct Product));
	//productFile("wb");
	printf("Product added successfully\n");
}

void editProduct() {
	char categoryId[sizeof(dataCate->categoryId)];
	char productName[sizeof(dataPro->productName)];
	int quantity;
	int price;

	int pos = findPosProduct(dataCate, currentCate);
	infoProduct(pos);

	printf("\t **** Update The New Category ****\n");
	int check = 1;
	do {
		inputCharValue("Enter the new category ID (0 for skip)", sizeof(categoryId), categoryId);

		if (strcmp(categoryId, "0") != 0) {
			for (int i = 0; i < currentCate; i++) {
				if (strcmp(dataCate[i].categoryId, categoryId) == 0) {
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
	workBinaryFile(filePro, "wb", dataPro, &currentPro, sizeof(struct Product));
	//productFile("wb");
	printf("Product Updated Successfully\n");
}

void deleteProduct() {
	int pos = findPosProduct();
	infoProduct(pos);
	do {
		char answer = confirmChoice("Confirm delete [Y/N]: ");
		if (answer == 'Y') {
			break;
		}else if (answer == 'N') {
			return;
		}
	}while (1);

	for (int i = pos; i < currentPro-1; i++) {
		dataPro[i] = dataPro[i+1];
	}
	currentPro--;
	workBinaryFile(filePro, "wb", dataPro, &currentPro, sizeof(struct Product));
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
	char name[sizeof(dataCate->categoryName)];
	char id[10];
	inputCharValue("Enter the category name: ", sizeof(name), name);

	int checkCate = 1;
	for (int i = 0; i < currentCate; i++) {
		if (strcmp(name, dataCate[i].categoryName) == 0) {
			strcpy(id, dataCate[i].categoryId);
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

void buyProduct(int userPos) {
	struct tm *tg;
	time_t t;
	time(&t);
	tg = localtime(&t);

	char idOrder[10] = "order00";
	sprintf(idOrder + strlen(idOrder), "%d", totalUserOrder+1);

	int check = 1;
	int totalPrice = 0;
	strcpy(dataUser[userPos].order[totalUserOrder].orderId, idOrder);
	dataUser[userPos].order[totalUserOrder].date.day = tg->tm_mday;
	dataUser[userPos].order[totalUserOrder].date.month = tg->tm_mon+1;
	dataUser[userPos].order[totalUserOrder].date.year = tg->tm_year+1900;
	for (int i = 0; i < totalCart; i++) {
		strcpy(dataUser[userPos].order[totalUserOrder].product[i].productId, dataUser[userPos].cart.product[i].productId);
		strcpy(dataUser[userPos].order[totalUserOrder].product[i].productName, dataUser[userPos].cart.product[i].productName);
		strcpy(dataUser[userPos].order[totalUserOrder].product[i].categoryId, dataUser[userPos].cart.product[i].categoryId);

		dataUser[userPos].order[totalUserOrder].product[i].price = dataUser[userPos].cart.product[i].price;
		dataUser[userPos].order[totalUserOrder].product[i].quantity = dataUser[userPos].cart.product[i].quantity;

		totalPrice += dataUser[userPos].cart.product[i].price * dataUser[userPos].cart.product[i].quantity;

		dataPro[i].quantity -= dataUser[userPos].cart.product[i].quantity;
		check = 0;
	}
	if (check) {
		printf("Error: ID not found\n");
	}else {
		dataUser[userPos].order[totalUserOrder].totalPrice = totalPrice;
		dataUser[userPos].order[totalUserOrder].amountProduct = totalCart;
		dataUser[userPos].totalCart = 0;
		totalCart = 0;
		totalUserOrder++;
		dataUser[userPos].totalOrder = totalUserOrder;
		workBinaryFile(fileUser, "wb", dataUser, &currentUser, sizeof(struct User));
		workBinaryFile(filePro, "wb", dataPro, &currentPro, sizeof(struct Product));
		printf("Purchase successful\n");
	}
}

void addCart(int userPos) {
	char id[10];
	int amount;
	inputCharValue("Enter the product ID to add to cart", sizeof(id), id);
	inputIntValue("Enter amount", &amount);
	int check = 1;
	for (int i = 0; i < currentPro; i++) {
		if (strcmp(id, dataPro[i].productId) == 0) {
			printf("%d", totalCart);
			strcpy(dataUser[userPos].cart.product[totalCart].productId, id);
			strcpy(dataUser[userPos].cart.product[totalCart].productName, dataPro[i].productName);
			strcpy(dataUser[userPos].cart.product[totalCart].categoryId, dataPro[i].categoryId);
			dataUser[userPos].cart.product[totalCart].price = dataPro[i].price;
			dataUser[userPos].cart.product[totalCart].quantity = amount;
			totalCart++;
			dataUser[userPos].totalCart = totalCart;
			workBinaryFile(fileUser, "wb", dataUser, &currentUser, sizeof(struct User));
			check = 0;
		}
	}
	if (check) {
		printf("Error: Product ID not found\n");
	}else {
		printf("Added to cart successfully\n");
	}
}

void removeCart(int userPos) {
	char id[10];
	inputCharValue("Enter the product ID to remove from cart", sizeof(id), id);
	int check = 1;
	for (int i = 0; i < totalCart; i++) {
		if (strcmp(id, dataUser[userPos].cart.product[i].productId) == 0) {
			do {
				char answer = confirmChoice("Confirm delete [Y/N]: ");
				if (answer == 'Y') {
					break;
				}else if (answer == 'N') {
					return;
				}
			}while (1);
			for (int j = i; j < totalCart-1; j++) {
				dataUser[userPos].cart.product[j] = dataUser[userPos].cart.product[j+1];
			}
			totalCart--;
			dataUser[userPos].totalCart = totalCart;
			workBinaryFile(fileUser, "wb", dataUser, &currentUser, sizeof(struct User));
			check = 0;
			break;
		}
	}
	if (check) {
		printf("Error: Product ID not found\n");
	}else {

		printf("Removed from cart successfully\n");
	}

}

void viewCart(int userPos) {
	if (totalCart == 0) {
		printf("Your cart is empty!\n");
		char temp[2];
		printf("Enter to go back: ");
		fflush(stdin);
		fgets(temp, 2, stdin);
		return;
	}
	printf("\t\t **Shopping Cart**\n");
	printf("=======================================================\n");
	printf("|%-10s|%-20s|%-10s|%-10s|\n", "Product ID", "Product Name", "Amount", "Price");
	printf("-------------------------------------------------------\n");
	for (int i = 0; i < totalCart; i++) {
		printf("|%-10s|%-20s|%-10d|%-10d|\n", dataUser[userPos].cart.product[i].productId, dataUser[userPos].cart.product[i].productName, dataUser[userPos].cart.product[i].quantity, dataUser[userPos].cart.product[i].price * dataUser[userPos].cart.product[i].quantity);
		printf("-------------------------------------------------------\n");
	}
	char choice[5];
	inputCharValue("Enter 'buy' to buy all, b to back", sizeof(choice), choice);
	if (strcmp(choice, "b") == 0) {
		return;
	}else if (strcmp(choice, "buy") == 0 ) {
		buyProduct(userPos);
	}
}
void bill(int userPos) {
	if (userPos == -1) {
		for (int i = 0; i < currentUser; i++) {
			if (dataUser[i].totalOrder > 0) {
				totalUserOrder += dataUser[i].totalOrder;
			}
		}
	}

	if (totalUserOrder == 0) {
		printf("No purchases yet\n");
		char temp[2];
		printf("Enter to go back: ");
		fflush(stdin);
		fgets(temp, 2, stdin);
		return;
	}
	if (userPos == -1) {
		do {
			system("cls");
			printf("\t\t **User Bill List**\n");
			printf("|=============================================|\n");
			printf("|%-15s|%-15s|%-13s|\n", "Order ID", "Customer ID", "Date");
			printf("|---------------------------------------------|\n");
			for (int i = 0; i < currentUser; i++) {
				if (dataUser[i].totalOrder > 0) {
					for (int j = 0; j < dataUser[i].totalOrder; j++) {
						char date[20];
						sprintf(date, "%d%s%d%s%d", dataUser[i].order[j].date.day, "/", dataUser[i].order[j].date.month, "/", dataUser[i].order[j].date.year);
						printf("|%-15s|%-15s|%-13s|\n", dataUser[i].order[j].orderId, dataUser[i].customerId, date);
						printf("|---------------------------------------------|\n");
					}
				}
			}
			printf("Enter order ID to view details, b for menu\n");
			char choice[10];
			inputCharValue("Enter your choice", 10, choice);
			if (strcmp(choice, "b") == 0) {
				return;
			}
			for (int i = 0; i < currentUser; i++) {
				for (int j = 0; j < dataUser[i].totalOrder; j++) {
					if (strcmp(choice, dataUser[i].order[j].orderId) == 0) {
						billList(i,0,dataUser[i].order[j].amountProduct, 1);
						char temp[2];
						printf(">> Enter to go back: ");
						fflush(stdin);
						fgets(temp, 2, stdin);
					}
				}
			}
			printf("=============================================");
		} while (1);

	}else {
		int page = 0;
		while (1) {
			billList(userPos, page, dataUser[userPos].order[page].amountProduct, 0);
			if (switchPage(&page)) {
				break;
			}
		}
	}
}

void findBill() {
	char id[sizeof(dataUser->order->orderId)];
	inputCharValue("Enter the order ID", sizeof(id), id);
	int check = 1;
	for (int i = 0; i < currentUser; i++) {
		for (int j = 0; j < dataUser[i].totalOrder; j++) {
			if (strcmp(id, dataUser[i].order[j].orderId) == 0) {
				billList(i,0,dataUser[i].order[j].amountProduct, 1);
				char temp[2];
				printf(">> Enter to go back: ");
				fflush(stdin);
				fgets(temp, 2, stdin);
				check = 0;
				break;
			}
		}
	}
	if (check) {
		printf("Error: Order ID not found\n");
		return;
	}
}
void showRevenue() {
	int day;
	int month;
	int year;
	int total = 0;
	inputIntValue("Enter the day", &day);
	inputIntValue("Enter the month", &month);
	inputIntValue("Enter the year", &year);

	for (int i = 0; i < currentUser; i++) {
		for (int j = 0; j < dataUser[i].totalOrder; j++) {
			if (dataUser[i].order[j].date.day == day && dataUser[i].order[j].date.month == month && dataUser[i].order[j].date.year == year) {
				total += dataUser[i].order[j].totalPrice;
			}
		}
	}
	printf("Total revenue for the day %d/%d/%d is: %d\n", day, month, year, total);
	char temp[2];
	printf(">> Enter to go back: ");
	fflush(stdin);
	fgets(temp, 2, stdin);
}


void showProductMenu() {
	printf("%20s\n", "PRODUCT MENU");
	printf("==============================\n");
	printf("1. Show all products\n");
	printf("2. Add a new product\n");
	printf("3. Edit a product\n");
	printf("4. Delete a product\n");
	printf("5. Find products\n");
	printf("6. Sort products\n");
	printf("7. Filter products\n");
	printf("8. Exit\n");
	printf("==============================\n");
}

void showProMenuUser(int userPos) {
	printf("%20s %30s\n", "USER MENU", dataUser[userPos].customerName);
	printf("%d", userPos);
	printf("==============================\n");
	printf("1. Show all products\n");
	printf("2. Find products\n");
	printf("3. Sort products\n");
	printf("4. Filter products\n");
	printf("5. Add item to cart\n");
	printf("6. Remove item from cart\n");
	printf("7. View cart\n");
	printf("8. View order history\n");
	printf("9. Exit\n");
	printf("==============================\n");
}

void menuOrder() {
	system("cls");
	printf("%20s\n", "ORDER MENU");
	printf("==============================\n");
	printf("1. Show all orders\n");
	printf("2. Find orders\n");
	printf("3. Exit\n");
	printf("==============================\n");
	int choice = inputChoice();
	switch (choice) {
		case 1:
			bill(-1);
			break;
		case 2:
			findBill();
			break;
		default:
			printf("Error: Invalid Choice\n");
			break;
	}
}

void menuFilter() {
	system("cls");
	printf("%20s\n", "Filter MENU");
	printf("==============================\n");
	printf("1. Filter by category name\n");
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
	workBinaryFile(filePro, "rb", dataPro, &currentPro, sizeof(struct Product));
	workBinaryFile(fileCate, "rb", dataCate, &currentCate, sizeof(struct Category));
	while (1) {
		system("cls");
		showProductMenu();
		int choice = inputChoice();
		switch (choice) {
			case 1:
				showProduct(0);
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
			char answer = confirmChoice("Go back(b)? or exit(0)?: ");
			if (answer == '0') {
				return;
			}else if (answer == 'b') {
				break;
			}
		}
	}
}

void manageUser(int userPos) {
	workBinaryFile(filePro, "rb", dataPro, &currentPro, sizeof(struct Product));
	workBinaryFile(fileCate, "rb", dataCate, &currentCate, sizeof(struct Category));
	while (1) {
		int confirm = 1;
		system("cls");
		printf("%d",totalUserOrder);
		showProMenuUser(userPos);
		int choice = inputChoice();
		switch (choice) {
			case 1:
				showProduct();
				break;
			case 2:
				findProduct();
				break;
			case 3:
				menuSortPro();
				break;
			case 4:
				menuFilter();
				break;
			case 5:
				addCart(userPos);
				break;
			case 6:
				removeCart(userPos);
				break;
			case 7:
				viewCart(userPos);
				confirm = 0;
				break;
			case 8:
				bill(userPos);
				confirm = 0;
				break;
			case 9:
				return;
			default:
				printf("Error: Invalid Choice\n");
				break;
		}
		if (confirm) {
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
}
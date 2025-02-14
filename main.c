#include <stdio.h>
#include <stdlib.h>
#include "./include/function.h"
#include "./include/category.h"
#include "./include/product.h"

int main() {
	while (1) {
		system("cls");
		printf("%20s\n", "MENU");
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
				return 0;
			default:
				printf("Error: Invalid choice");
			break;
		}
	}
}
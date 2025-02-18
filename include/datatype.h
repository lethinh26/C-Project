#ifndef DATATYPE_H
#define DATATYPE_H
#pragma once

struct Date {
	int day, month, year;
};

struct Category {
	char categoryName[20];
	char categoryId[10];
};

struct Product {
	char productId[10];
	char categoryId[10]; //
	char productName[20];
	int quantity;
	int price;
};

struct Order {
	char orderId[10];
	int totalPrice;
	int amountProduct;
	struct Date date;
	struct Product product[20];
};

struct Cart {
	struct Product product[20];
};

struct User {
	char customerId[10];
	char customerName[20];
	char password[20];
	int totalOrder;
	int totalCart;
	struct Cart cart;
	struct Order order[20];
};

extern const char *filePro;
extern const char *fileCate;
extern const char *fileUser;

extern struct Product dataPro[100];
extern struct User dataUser[100];
extern struct Category dataCate[100];

extern int currentCate;
extern int currentPro;
extern int currentUser;

extern int totalUserOrder;
extern int totalCart;


#endif

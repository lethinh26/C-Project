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
	char customerId[20];
	struct Date date;
	struct Product product;
};

extern const char *filePro;
extern const char *fileCate;
extern struct Product dataPro[100];
extern struct Category dataCate[100];
extern int currentCate;
extern int currentPro;

#endif

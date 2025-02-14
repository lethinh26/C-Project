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

#include <stdio.h>
#include <string.h>
const char *filePath = "./data/hello.bin";
struct Product {
	char productId[10];
	char categoryId[10];
	char productName[20];
	int quantity;
	int price;
};

void file(const char *filePath, int *count, struct data *data, const char *mode, int countStruct) {
	FILE *fptr = fopen(filePath, mode);
	if (fptr == NULL) {
		printf("Error opening file\n");
		return;
	}

	if (strcmp(mode, "wb") == 0) {
		fwrite(data, countStruct, *count, fptr);
	} else {
		*count = fread(data, countStruct, 100, fptr);
	}

	fclose(fptr);
}

int main() {
	struct Product data[] = {
		{"06436", "Hello", "Bruh", 10, 1}
	};

	int count = 1;
	file(filePath, &count, data, "wb", sizeof(struct Product));
	return 0;
}

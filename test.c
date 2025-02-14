#include <stdio.h>
#include <string.h>

struct Category {
	char categoryName[20];
	char categoryId[10];
};

int main() {
	struct Category data[2] = {"id001", "Hello"};
	printf("%llu", sizeof(data->categoryName));
}
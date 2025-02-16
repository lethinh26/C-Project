#include <stdio.h>
#include <stdlib.h>
#include "./include/function.h"
#include "./include/datatype.h"
struct Product dataPro[100];
struct Category dataCate[100];
int currentCate = 0;
int currentPro = 0;
const char *filePro = "../data/product.bin";
const char *fileCate = "../data/category.bin";

int main() {
	showLogin();
}
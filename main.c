#include <stdio.h>
#include <stdlib.h>
#include "./include/function.h"
#include "./include/datatype.h"
struct Product dataPro[100];
struct Category dataCate[100];
struct User dataUser[100];

int currentCate = 0;
int currentPro = 0;
int currentUser = 0;

const char *filePro = "../data/product.bin";
const char *fileCate = "../data/category.bin";
const char *fileUser = "../data/user.bin";


int main() {
	showMainMenu();
}
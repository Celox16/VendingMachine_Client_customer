#include <stdio.h>
#include <string.h>

#define DRINK_SIZE	5
#define MONEY_SIZE	5

struct drinkInfo {
	char name[20];
	int price;
	int count;
};

struct moneyInfo {
	int value;
	int count;
};

int moneyBuf[MONEY_SIZE];
int drinkBuf[DRINK_SIZE];

void SetInitial(drinkInfo initialDrink[], moneyInfo initialMoney[]) {
	//water
	strcpy(initialDrink[0].name, "water");
	initialDrink[0].price = 450;
	initialDrink[0].count = 3;

	//coffee
	strcpy(initialDrink[1].name, "coffee");
	initialDrink[1].price = 500;
	initialDrink[1].count = 3;

	//ion_drink
	strcpy(initialDrink[2].name, "ion_drink");
	initialDrink[2].price = 550;
	initialDrink[2].count = 3;

	//fine_coffee
	strcpy(initialDrink[3].name, "fine_coffee");
	initialDrink[3].price = 700;
	initialDrink[3].count = 3;

	//carbo_drink
	strcpy(initialDrink[4].name, "carbo_drink");
	initialDrink[4].price = 750;
	initialDrink[4].count = 3;

	initialMoney[0].value = 100000000;
	initialMoney[0].count = 5;

	initialMoney[1].value = 500;
	initialMoney[1].count = 5;

	initialMoney[2].value = 100;
	initialMoney[2].count = 5;

	initialMoney[3].value = 50;
	initialMoney[3].count = 5;

	initialMoney[4].value = 10;
	initialMoney[4].count = 5;
}

// select customer menu or admin menu
int PrintFirstMenu() {
	int selectFirstMenu;
	printf("\n");
	printf("===========================================================\n");
	printf("========1. 자판기 이용하기(사용자 전용) 2. 관리자 메뉴========\n");
	printf("===========================================================\n");

	scanf("%d", &selectFirstMenu);
	return selectFirstMenu;
}

// customer menu : insert moeney
int InsertCoin(moneyInfo clientMoney[]) {
	int insertCoinCount[MONEY_SIZE];
	int sumOfIsertedMoney = 0;
	printf("===========================================================\n");
	printf("동전을 투입해주세요\n");
OVER:
	for (int i = 0; i < MONEY_SIZE; i++) {
		printf("%d원 투입 갯수 : ", clientMoney[i].value);
		scanf("%d", &insertCoinCount[i]);
		sumOfIsertedMoney += clientMoney[i].value * insertCoinCount[i];
	}

	if (sumOfIsertedMoney >= 5000) {
		printf("투입한 돈이 너무 많습니다. 다시 투입해주세요.");
		goto OVER;
	}

	for (int i = 0; i < MONEY_SIZE; i++) {
		moneyBuf[i] = insertCoinCount[i];
	}
	printf("===========================================================\n\n");
	return sumOfIsertedMoney;
}

// customer menu : select drink
void SelectDrink(drinkInfo clientDrink[], int insertedMoney) {
	printf("===========================================================\n");
	printf("구매하고자 하는 음료를 골라주세요\n");
	for (int i = 0; i < DRINK_SIZE; i++) {
		if (clientDrink[i].price <= insertedMoney) {
			printf("%d. %s\t", clientDrink[i].name);
		}
	}
}
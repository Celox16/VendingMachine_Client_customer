#include <stdio.h>
#include <string.h>

// define size and struct
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

struct valuesForCustomer {
	int selectDrink;
	int drinkCount;
	int changeMoney;
};

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

	initialMoney[0].value = 1000;
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
	printf("==========1. 자판기사용\t2. 관리자메뉴\t3. 종료============\n");
	printf("===========================================================\n");
	printf("메뉴를 선택해주세요 : ");
	scanf("%d", &selectFirstMenu);
	return selectFirstMenu;
}

// customer menu : insert moeney
int InsertCoin(moneyInfo clientMoney[]) {
	int insertCoinCount[MONEY_SIZE];
	int sumOfIsertedMoney = 0;
	printf("===========================================================\n");
	printf("동전을 투입해주세요\n");
OVER_INSERT_MONEY:
	for (int i = 0; i < MONEY_SIZE; i++) {
		printf("%d원 투입 갯수 : ", clientMoney[i].value);
		scanf("%d", &insertCoinCount[i]);
		sumOfIsertedMoney += clientMoney[i].value * insertCoinCount[i];
		printf("현재 투입 금액 : %d\n", sumOfIsertedMoney);
	}

	if (sumOfIsertedMoney > 5000) {
		printf("투입한 돈이 너무 많습니다. 다시 투입해주세요.");
		sumOfIsertedMoney = 0;
		goto OVER_INSERT_MONEY;
	}
	printf("===========================================================\n\n");
	
	// inserted coin add to clientMoney
	for (int i = 0; i < MONEY_SIZE; i++) {
		clientMoney[i].count += insertCoinCount[i];
	}
	return sumOfIsertedMoney;
}

// customer menu : select drink
valuesForCustomer SelectDrink(drinkInfo clientDrink[], int insertedMoney) {
	valuesForCustomer buf;

	printf("===========================================================\n");
	printf("구매하고자 하는 음료를 골라주세요(가격, 남은 수량)\n");
	for (int i = 0; i < DRINK_SIZE; i++) {
		if (i%3==0) {
			printf("\n");
		}
		printf("%d. %s(%d, %d)\t ", i+1, clientDrink[i].name, clientDrink[i].price, clientDrink[i].count);
	}

	// select drink
	printf("\n입력 : ");
	scanf("%d", &buf.selectDrink);
	buf.selectDrink--;
	printf("===========================================================\n");

	printf("개수를 선택하세요 :");
DRINK_COUNT_OVER:
	scanf("%d", &buf.drinkCount);

	if (clientDrink[buf.selectDrink].price * buf.drinkCount > insertedMoney) {
		printf("금액이 부족합니다. 개수를 다시 입력해주세요(입력된 금액 %d원) : ", insertedMoney);
		goto DRINK_COUNT_OVER;
	}
	else if (clientDrink[buf.selectDrink].count < buf.drinkCount) {
		printf("음료 개수가 부족합니다. (남은재고 : %d개) 개수를 다시 입력해주세요 : ", clientDrink[buf.selectDrink].count);
		goto DRINK_COUNT_OVER;
	}
	else {
		buf.changeMoney = insertedMoney - clientDrink[buf.selectDrink].price * buf.drinkCount;
	}

	return buf;
}

// customer menu : get change money and modify clientMoney, clientDrink
void GetChangeAndModifyList(moneyInfo clientMoney[], drinkInfo clientDrink[], valuesForCustomer buf) {
	int changeMoneyCountBuf[MONEY_SIZE] = { 0 }; // separately change coin count

	for (int i = 0; i < MONEY_SIZE; i++) {
		if (buf.changeMoney == 0)
			break;
		else if (clientMoney[i].count == 0)
			continue;
		else if (buf.changeMoney >= clientMoney[i].value) {
			do {
				buf.changeMoney -= clientMoney[i].value;
				changeMoneyCountBuf[i]++;
			} while (buf.changeMoney >= clientMoney[i].value);
		}
	}

	if (buf.changeMoney != 0) {
		printf("잔돈이 부족합니다.\n");
	}
	else {
		printf("%s %d개 구매완료!\n", clientDrink[buf.selectDrink].name, buf.drinkCount);
		clientDrink[buf.selectDrink].count -= buf.drinkCount;
		for (int i = 0; i < MONEY_SIZE; i++) {
			clientMoney[i].count -= changeMoneyCountBuf[i];
			printf("%d원 %d개, ", clientMoney[i].value, changeMoneyCountBuf[i]);
		}
		printf("반환 완료\n");
	}
	printf("===========================================================\n\n\n");
}
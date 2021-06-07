#include <stdio.h>
#include <string.h>

int coin[6] = { 0 };

struct drinkInfo {
	char name[20];
	int price;
	int count;
};

drinkInfo list[5];

void SetInitialArray(int vending[]) {
	for (int i = 0; i < 12; i++) {
		vending[i] = 0;
	}
}

//void SetDrinkInfo() {	
//	strcpy(list[0].name, "water");
//	list[0].count = 3;
//	list[0].price = 450;
//
//	strcpy(list[1].name, "coffee");
//	list[1].count = 3;
//	list[1].price = 450;
//
//	strcpy(list[2].name, "ion_drink");
//	list[2].count = 3;
//	list[2].price = 450;
//
//	strcpy(list[3].name, "fine_coffee");
//	list[3].count = 3;
//	list[3].price = 450;
//
//	strcpy(list[4].name, "carbo_drink");
//	list[4].count = 3;
//	list[4].price = 450;
//}

// 사용자 전용인지 관리자 메뉴인지 확인하기
int PrintFirstMenu() {
	int selectFirstMenu;
	printf("===========================================================\n");
	printf("========1. 자판기 이용하기(사용자 전용) 2. 관리자 메뉴========\n");
	printf("===========================================================\n");
	scanf("%d", &selectFirstMenu);
	return selectFirstMenu;
}

// 사용자일 경우 먼저 동전 입력을 받는다.
int CustomerInsertCoin() {

	int insertedCoin = 0;
	
	printf("======투입할 동전을 개수를 입력하세요 (최대 5000원)===========\n");
	printf("5000원 : ");
	scanf("%d", &coin[0]);
	printf("1000원 : ");
	scanf("%d", &coin[1]);
	printf("500원 : ");
	scanf("%d", &coin[2]);
	printf("100원 : ");
	scanf("%d", &coin[3]);
	printf("50원 : ");
	scanf("%d", &coin[4]);
	printf("10원 : ");
	scanf("%d", &coin[5]);

	for (int i = 0; i < 6; i++) {
		insertedCoin += coin[i];
	}

	return insertedCoin;
}

// 입력된 돈의 합계에 따라서 구매가능한 물품을 보여준다.
int CustomerSelectDrink(int insertedCoin, drinkInfo list[]) {

	int selectDrink;
	
	printf("=====================select drink==========================\n");
	printf("===========================================================\n");
	printf("1. water  2. coffee  3. ion_drink  4. fine_coffee  5. carbo_drink/\n");
	for (int i = 0; i < 5; i++) {
		if (insertedCoin >= list[i].price)
			printf("    *    ");
		else
			printf("         ");
	}
	printf("\n");
	printf("===========================================================\n");
	
	return 0;
}

// 사용자가 음료를 선택하면 나머지 동전을 반환해준다.
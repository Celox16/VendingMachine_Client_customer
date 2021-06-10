#include <stdio.h>
#include <string.h>

#define BUFSIZE	512

#define DRINK_SIZE	5
#define MONEY_SIZE	5

// struct define, variables
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
	int selctDrink;
	int drinkCount;
	int changeMoney;
};

char password[BUFSIZE + 1] = "adminadmin!";

// print admin menu
int PrintAdminMenu() {
	int selectAdminMenu;

	printf("\n");
	printf("===========================================================\n");
	printf("========1. 음료재고 충전,\t2. 거스름돈 충전\t3. 수금========\n");
	printf("========4. 월별판매현황,\t5. 음료 이름 변경\t6. 비밀번호 변경========")
	printf("===========================================================\n");

	scanf("%d", &selectAdminMenu);
	return selectAdminMenu;
}

void ComparePassword() {

}

// recharge drink (add drink)
void RechargeDrink(drinkInfo clientDrink[]) {
	int selectDrink;
	int rechargeDrinkCount;
	printf("======================음료 재고 리스트======================\n");
	for (int i = 0; i < DRINK_SIZE, i++) {
		printf("%d. %s, 가격 : %d, 남은 수량 : %d\n", i, clientDrink[i].name, clientDrink[i].price, clientDrink[i].count);
	}
	printf("충전할 음료의 번호를 선택해주세요 : ");
	scanf("%d", &selectDrink);
	printf("충전할 음료의 수량을 입력해주세요 : ");
	scanf("%d", &rechargeDrinkCount);

	//modify (add to drink count in client drink)
	clientDrink[selectDrink].count += rechargeDrinkCount;
	printf("%s(%d개 충전, 총%d개\n", clientDrink[selectDrink].name, rechargeDrinkCount, clientDrink[selectDrink].count);

}

// recharge money (add coin)
void RechargeMoney() {

}

// collect money (sub coin)
void CollectMoney() {

}

void modifyDrinkInfo() {

}

void modifyPassword() {

}
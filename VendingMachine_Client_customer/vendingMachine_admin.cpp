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
	printf("========1. ������� ����,\t2. �Ž����� ����\t3. ����========\n");
	printf("========4. �����Ǹ���Ȳ,\t5. ���� �̸� ����\t6. ��й�ȣ ����========")
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
	printf("======================���� ��� ����Ʈ======================\n");
	for (int i = 0; i < DRINK_SIZE, i++) {
		printf("%d. %s, ���� : %d, ���� ���� : %d\n", i, clientDrink[i].name, clientDrink[i].price, clientDrink[i].count);
	}
	printf("������ ������ ��ȣ�� �������ּ��� : ");
	scanf("%d", &selectDrink);
	printf("������ ������ ������ �Է����ּ��� : ");
	scanf("%d", &rechargeDrinkCount);

	//modify (add to drink count in client drink)
	clientDrink[selectDrink].count += rechargeDrinkCount;
	printf("%s(%d�� ����, ��%d��\n", clientDrink[selectDrink].name, rechargeDrinkCount, clientDrink[selectDrink].count);

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
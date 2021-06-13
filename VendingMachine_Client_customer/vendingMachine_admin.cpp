#include <stdio.h>
#include <string.h>

#define BUFSIZE	1024

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

// print admin menu
int PrintAdminMenu() {
	int selectAdminMenu;

	printf("\n");
	printf("===========================================================\n");
	printf("1. 음료재고 충전,\t2. 거스름돈 충전\t3. 수금\n");
	printf("4. 음료정보 변경,\t5. 비밀번호 변경\t6. 매출현황\n");
	printf("===========================================================\n");

	scanf("%d", &selectAdminMenu);
	return selectAdminMenu;
}

int ComparePassword(char originPassword[], char enteredPassword[]) {
	int isSame;

	isSame = strcmp(originPassword, enteredPassword);

	return isSame;
}

// recharge drink (add drink)
void RechargeDrink(drinkInfo clientDrink[]) {
	int selectDrink;
	int rechargeDrinkCount;

	printf("======================음료 재고 리스트======================\n");
	for (int i = 0; i < DRINK_SIZE; i++) {
		printf("%d. %s, 가격 : %d, 남은 수량 : %d\n", i, clientDrink[i].name, clientDrink[i].price, clientDrink[i].count);
	}
	printf("충전할 음료의 번호를 선택해주세요 : ");
	scanf("%d", &selectDrink);
	printf("충전할 음료의 수량을 입력해주세요 : ");
	scanf("%d", &rechargeDrinkCount);

	//modify (add to drink count in client drink)
	clientDrink[selectDrink].count += rechargeDrinkCount;
	printf("%s(%d개 충전, 총%d개)\n", clientDrink[selectDrink].name, rechargeDrinkCount, clientDrink[selectDrink].count);

}

// recharge money (add coin)
void RechargeMoney(moneyInfo clientMoney[]) {
	int selectMoneyValue;
	int rechargeMoneyCount;
	int isCorrect;

	printf("======================화폐 재고 리스트======================\n");
	for (int i = 0; i < MONEY_SIZE; i++) {
		printf("%d원 %d개\n", clientMoney[i].value, clientMoney[i].count);
	}
	printf("충전할 얼마짜리를 충전하시겠습니까? : ");
	scanf("%d", &selectMoneyValue);
	// add exception error code
	printf("몇개를 충전하시겠습니까? : ");
	scanf("%d", &rechargeMoneyCount);

	for (int i = 0; i < MONEY_SIZE; i++) {
		if (clientMoney[i].value == selectMoneyValue) {
			clientMoney[i].count += rechargeMoneyCount;
		}
	}
	printf("===========================================================\n");
}

// collect money (sub coin)
void CollectMoney(moneyInfo clientMoney[]) {
	int collectMoneyCount[MONEY_SIZE];
	int sumCollectedMoney = 0;

	printf("======================화폐 재고 리스트======================\n");
	printf("수금할 화폐의 개수를 입력해주세요\n");
	for (int i = 0; i < MONEY_SIZE; i++) {
		printf("%d원 (현재 %d개, 총%d원) : ", clientMoney[i].value, clientMoney[i].count, clientMoney[i].value * clientMoney[i].count);
		while (1) {
			scanf("%d", &collectMoneyCount[i]);
			if (collectMoneyCount[i] <= clientMoney[i].count)
				break;
			printf("입력개수 초과! 다시 입력해주세요 : ");
		}
	}
	for (int i = 0; i < MONEY_SIZE; i++) {
		sumCollectedMoney += clientMoney[i].value * collectMoneyCount[i];
		clientMoney[i].count -= collectMoneyCount[i];
		printf("%d원 %d개, ", clientMoney[i].value, collectMoneyCount[i]);
	}
	printf("수금 완료, 총 %d원 수금\n", sumCollectedMoney);
	printf("===========================================================\n");
}

// modify drink price or name
void ModifyDrinkInfo(drinkInfo clientDrink[]) {
	int selectModify;
	char drinkName[BUFSIZE + 1];
	int len = 0;
	int modifyDrinkPrice = 0;

	printf("======================음료 정보 리스트======================\n");
	for (int i = 0; i < DRINK_SIZE; i++) {
		printf("음료 이름 : %s, 음료 가격 : %d\n", clientDrink[i].name, clientDrink[i].price);
	}
	printf("===========================================================\n");

	printf("수정할 음료의 이름을 입력해주세요 : ");

	fflush(stdin);
	rewind(stdin);
	// edit the entered name
	fgets(drinkName, BUFSIZE + 1, stdin);
	len = strlen(drinkName);
	if (drinkName[len - 1] == '\n') drinkName[len - 1] = '\0';

	// search drink
	for (int i = 0; i < MONEY_SIZE; i++) {
		if (!strcmp(clientDrink[i].name, drinkName)) {
			printf("음료이름 : %s, 가격 : %d\n1. 음료이름 수정, 2. 음료가격 수정 : ", clientDrink[i].name, clientDrink[i].price);
			scanf("%d", &selectModify);
			if (selectModify == 1) {
				printf("수정할 음료의 이름을 정해주세요 : ");

				fflush(stdin);
				rewind(stdin);
				// edit the entered name
				fgets(drinkName, BUFSIZE + 1, stdin);
				len = strlen(drinkName);
				if (drinkName[len - 1] == '\n') drinkName[len - 1] = '\0';

				// copy drink name
				strcpy(clientDrink[i].name, drinkName);
				break;
			}
			else if (selectModify == 2) {
				printf("수정할 음료의 가격을 정해주세요 : ");

				scanf("%d", &modifyDrinkPrice);
				clientDrink[i].price = modifyDrinkPrice;
			}
			else
				printf("검색결과가 없습니다.\n");
		}
		else
			continue;
	}
	printf("===========================================================\n");
}

// modify password
void ModifyPassword(char originPassword[BUFSIZE+1]) {
	char newPassword[BUFSIZE + 1];
	int len;
	
	printf("수정하고자 하는 비밀번호를 입력해주세요. : ");
	while (1) {
		fflush(stdin);
		rewind(stdin);
		fgets(newPassword, BUFSIZE + 1, stdin);
		len = strlen(newPassword);
		if (newPassword[len - 1] == '\n') newPassword[len - 1] = '\0';

		if (strlen(newPassword) < 8) {
			printf("비밀번호의 길이가 너무 짧습니다. 다시 입력해주세요 : ");
			continue;
		}
		
		for (int i = 0; i < strlen(newPassword); i++) {
			if (newPassword[i]<80||(newPassword[i]>89&& newPassword[i]<97)||
				(newPassword[i]>122|| newPassword[i]<97)) { // ASCII code special characters
				goto OUT;
			}
		}
		printf("비밀번호에 특수문자를 최소1개 이상 추가해주세요. : ");
	}
OUT:
	strcpy(originPassword, newPassword);
}
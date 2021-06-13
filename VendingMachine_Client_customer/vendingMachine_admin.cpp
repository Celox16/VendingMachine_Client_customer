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
	printf("1. ������� ����,\t2. �Ž����� ����\t3. ����\n");
	printf("4. �������� ����,\t5. ��й�ȣ ����\t6. ������Ȳ\n");
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

	printf("======================���� ��� ����Ʈ======================\n");
	for (int i = 0; i < DRINK_SIZE; i++) {
		printf("%d. %s, ���� : %d, ���� ���� : %d\n", i, clientDrink[i].name, clientDrink[i].price, clientDrink[i].count);
	}
	printf("������ ������ ��ȣ�� �������ּ��� : ");
	scanf("%d", &selectDrink);
	printf("������ ������ ������ �Է����ּ��� : ");
	scanf("%d", &rechargeDrinkCount);

	//modify (add to drink count in client drink)
	clientDrink[selectDrink].count += rechargeDrinkCount;
	printf("%s(%d�� ����, ��%d��)\n", clientDrink[selectDrink].name, rechargeDrinkCount, clientDrink[selectDrink].count);

}

// recharge money (add coin)
void RechargeMoney(moneyInfo clientMoney[]) {
	int selectMoneyValue;
	int rechargeMoneyCount;
	int isCorrect;

	printf("======================ȭ�� ��� ����Ʈ======================\n");
	for (int i = 0; i < MONEY_SIZE; i++) {
		printf("%d�� %d��\n", clientMoney[i].value, clientMoney[i].count);
	}
	printf("������ ��¥���� �����Ͻðڽ��ϱ�? : ");
	scanf("%d", &selectMoneyValue);
	// add exception error code
	printf("��� �����Ͻðڽ��ϱ�? : ");
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

	printf("======================ȭ�� ��� ����Ʈ======================\n");
	printf("������ ȭ���� ������ �Է����ּ���\n");
	for (int i = 0; i < MONEY_SIZE; i++) {
		printf("%d�� (���� %d��, ��%d��) : ", clientMoney[i].value, clientMoney[i].count, clientMoney[i].value * clientMoney[i].count);
		while (1) {
			scanf("%d", &collectMoneyCount[i]);
			if (collectMoneyCount[i] <= clientMoney[i].count)
				break;
			printf("�Է°��� �ʰ�! �ٽ� �Է����ּ��� : ");
		}
	}
	for (int i = 0; i < MONEY_SIZE; i++) {
		sumCollectedMoney += clientMoney[i].value * collectMoneyCount[i];
		clientMoney[i].count -= collectMoneyCount[i];
		printf("%d�� %d��, ", clientMoney[i].value, collectMoneyCount[i]);
	}
	printf("���� �Ϸ�, �� %d�� ����\n", sumCollectedMoney);
	printf("===========================================================\n");
}

// modify drink price or name
void ModifyDrinkInfo(drinkInfo clientDrink[]) {
	int selectModify;
	char drinkName[BUFSIZE + 1];
	int len = 0;
	int modifyDrinkPrice = 0;

	printf("======================���� ���� ����Ʈ======================\n");
	for (int i = 0; i < DRINK_SIZE; i++) {
		printf("���� �̸� : %s, ���� ���� : %d\n", clientDrink[i].name, clientDrink[i].price);
	}
	printf("===========================================================\n");

	printf("������ ������ �̸��� �Է����ּ��� : ");

	fflush(stdin);
	rewind(stdin);
	// edit the entered name
	fgets(drinkName, BUFSIZE + 1, stdin);
	len = strlen(drinkName);
	if (drinkName[len - 1] == '\n') drinkName[len - 1] = '\0';

	// search drink
	for (int i = 0; i < MONEY_SIZE; i++) {
		if (!strcmp(clientDrink[i].name, drinkName)) {
			printf("�����̸� : %s, ���� : %d\n1. �����̸� ����, 2. ���ᰡ�� ���� : ", clientDrink[i].name, clientDrink[i].price);
			scanf("%d", &selectModify);
			if (selectModify == 1) {
				printf("������ ������ �̸��� �����ּ��� : ");

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
				printf("������ ������ ������ �����ּ��� : ");

				scanf("%d", &modifyDrinkPrice);
				clientDrink[i].price = modifyDrinkPrice;
			}
			else
				printf("�˻������ �����ϴ�.\n");
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
	
	printf("�����ϰ��� �ϴ� ��й�ȣ�� �Է����ּ���. : ");
	while (1) {
		fflush(stdin);
		rewind(stdin);
		fgets(newPassword, BUFSIZE + 1, stdin);
		len = strlen(newPassword);
		if (newPassword[len - 1] == '\n') newPassword[len - 1] = '\0';

		if (strlen(newPassword) < 8) {
			printf("��й�ȣ�� ���̰� �ʹ� ª���ϴ�. �ٽ� �Է����ּ��� : ");
			continue;
		}
		
		for (int i = 0; i < strlen(newPassword); i++) {
			if (newPassword[i]<80||(newPassword[i]>89&& newPassword[i]<97)||
				(newPassword[i]>122|| newPassword[i]<97)) { // ASCII code special characters
				goto OUT;
			}
		}
		printf("��й�ȣ�� Ư�����ڸ� �ּ�1�� �̻� �߰����ּ���. : ");
	}
OUT:
	strcpy(originPassword, newPassword);
}
#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERIP	"127.0.0.1"
#define SERVERPORT	9000
#define BUFSIZE		1024

#define DRINK_SIZE	5
#define MONEY_SIZE	5

// struct define
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

drinkInfo clientDrink[DRINK_SIZE];
moneyInfo clientMoney[MONEY_SIZE];
char originPassword[BUFSIZE + 1] = "adminadmin!";
char enteredPassword[BUFSIZE + 1];

// function define - customer menu
extern void SetInitial(drinkInfo initialDrink[], moneyInfo initalMoney[]);
extern int PrintFirstMenu();
extern int InsertCoin(moneyInfo clientMoney[]);
extern valuesForCustomer SelectDrink(drinkInfo clientDrink[], int insertedMoney);
extern void GetChangeAndModifyList(moneyInfo clientMoney[], drinkInfo clientDrink[], valuesForCustomer buf);

// function define - admin menu
extern int ComparePassword(char originPassword[], char enteredPassword[]);
extern int PrintAdminMenu();
extern void RechargeDrink(drinkInfo clientDrink[]);
extern void RechargeMoney(moneyInfo clientMoney[]);
extern void CollectMoney(moneyInfo clientMoney[]);
extern void ModifyDrinkInfo(drinkInfo clientDrink[]);
extern void ModifyPassword(char originPassword[BUFSIZE + 1]);

// 소켓 함수 오류 출력후 종료
void err_quit(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

//소켓 함수 오류 출력
void err_display(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[ % s] % s", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

int recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}

int main(int argc, char* argv[])
{
	int retval; // retval
	int selectFristMenu; // judgement customer or admin
	int selectAdminMenu; // to select in admin menu
	int insertedMoney; // sum of inserted money
	int changeMoney;	// after purchase change money
	int selectDrink;	// select drink
	valuesForCustomer customerValue;	// return values

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket() - drink data
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connet()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connet()");

	// 데이터 통신에 사용할 변수
	int len;

	// set initial client data
	SetInitial(clientDrink, clientMoney);

	// 서버와 데이터 통신
	while (1) {
		// print menu
		selectFristMenu = PrintFirstMenu();
		if (selectFristMenu == 1) { // customer
			// send client inital drink data
			retval = send(sock, (char*)clientDrink, sizeof(drinkInfo) * DRINK_SIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("send drink data");
				break;
			}

			// receive server initial drink data
			retval = recvn(sock, (char*)clientDrink, sizeof(drinkInfo) * DRINK_SIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("receive drink data");
				break;
			}
			else if (retval == 0)
				break;

			// send client initial money data
			retval = send(sock, (char*)clientMoney, sizeof(moneyInfo) * MONEY_SIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("send money data");
				break;
			}
			else if (retval == 0)
				break;

			// receive server intial money data
			retval = recvn(sock, (char*)clientMoney, sizeof(moneyInfo) * MONEY_SIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("receive money data");
				break;
			}
			else if (retval == 0)
				break;

			// client logic
			insertedMoney = InsertCoin(clientMoney); // insert money
			customerValue = SelectDrink(clientDrink, insertedMoney); // select drink and get change money
			GetChangeAndModifyList(clientMoney, clientDrink, customerValue); // get change and modify money, drink array
		}
		else if (selectFristMenu == 2) { // admin
			// send client inital drink data
			retval = send(sock, (char*)clientDrink, sizeof(drinkInfo) * DRINK_SIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("send drink data");
				break;
			}

			// receive server initial drink data
			retval = recvn(sock, (char*)clientDrink, sizeof(drinkInfo) * DRINK_SIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("receive drink data");
				break;
			}
			else if (retval == 0)
				break;

			// send client initial money data
			retval = send(sock, (char*)clientMoney, sizeof(moneyInfo) * MONEY_SIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("send money data");
				break;
			}
			else if (retval == 0)
				break;

			// receive server intial money data
			retval = recvn(sock, (char*)clientMoney, sizeof(moneyInfo) * MONEY_SIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("receive money data");
				break;
			}
			else if (retval == 0)
				break;

			// start to admin logic
			// enter admin password
			printf("비밀번호 입력 : ");
			fflush(stdin);
			rewind(stdin);
			fgets(enteredPassword, BUFSIZE + 1, stdin);
			len = strlen(enteredPassword);
			if (enteredPassword[len - 1] == '\n') enteredPassword[len - 1] = '\0';
			if (!ComparePassword(originPassword, enteredPassword)) {
				selectAdminMenu = PrintAdminMenu();
				switch (selectAdminMenu)
				{
				case 1:
					RechargeDrink(clientDrink);
					break;
				case 2:
					RechargeMoney(clientMoney);
					break;
				case 3:
					CollectMoney(clientMoney);
					break;
				case 4:
					ModifyDrinkInfo(clientDrink);
					break;
				case 5:
					ModifyPassword(originPassword);
					break;
				default:
					break;
				}
			}
			else {
				printf("비밀번호가 일치하지 않습니다. ");
			}
		}
		else { // exit
			break;
		}

		// end to clinet logic

		// resend drink and money list

		// send modified clientDrink data
		retval = send(sock, (char*)&clientDrink, sizeof(drinkInfo) * DRINK_SIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send drink data");
			break;
		}

		// receive modified clientDrink data
		retval = recvn(sock, (char*)&clientDrink, sizeof(drinkInfo) * DRINK_SIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("receive drink data");
			break;
		}
		else if (retval == 0)
			break;

		// send modified clientMoney data
		retval = send(sock, (char*)&clientMoney, sizeof(moneyInfo) * MONEY_SIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send drink data");
			break;
		}

		// recevie modified clientMoney data
		retval = recvn(sock, (char*)&clientMoney, sizeof(moneyInfo) * MONEY_SIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("receive drink data");
			break;
		}
		else if (retval == 0)
			break;
	}

	//closesocket()
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}
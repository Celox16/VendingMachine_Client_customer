#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERIP	"127.0.0.1"
#define SERVERPORT	9000
#define BUFSIZE		1024

#define DRINK_SIZE	5
#define MONEY_SIZE	5

// variable define
struct drinkInfo {
	char name[20];
	int price;
	int count;
};

struct moneyInfo {
	int value;
	int count;
};

struct returnValue {
	int selctDrink;
	int drinkCount;
	int changeMoney;
};

drinkInfo clientDrink[DRINK_SIZE];
moneyInfo clientMoney[MONEY_SIZE];

// function define
extern void SetInitial(drinkInfo initialDrink[], moneyInfo initalMoney[]);
extern int PrintFirstMenu();
extern int InsertCoin(moneyInfo clientMoney[]);
extern returnValue SelectDrink(drinkInfo clientDrink[], int insertedMoney);
extern void GetChangeAndModifyList(moneyInfo clientMoney[], drinkInfo clientDrink[], returnValue buf);

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
	int retval; // drink retval
	int selectFristMenu; // judgement customer or admin
	int insertedMoney; // sum of inserted money
	int changeMoney;	// after purchase chane money
	int selectDrink;	// select drink
	returnValue buf;	// return values

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
	//int buf[BUFSIZE + 1];
	int len;

	// set initial client data
	SetInitial(clientDrink, clientMoney);

	// 서버와 데이터 통신
	while (1) {
		// 데이터 입력
		//printf("\n[보낼 데이터] ");
		
		// send client inital drink data
		retval = send(sock, (char*)clientDrink, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send drink data");
			break;
		}
		printf("send\n");

		// receive server initial drink data
		retval = recvn(sock, (char*)clientDrink, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("receive drink data");
			break;
		}
		else if (retval == 0)
			break;
		printf("recv\n");

		printf("%s %d %d\n", clientDrink[0].name, clientDrink[0].price, clientDrink[0].count);

		// send client initial money data
		retval = send(sock, (char*)clientMoney, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send money data");
			break;
		}
		else if (retval == 0)
			break;
		printf("send2\n");

		printf("value = %d, count = %d\n", clientMoney[0].value, clientMoney[0].count);

		// receive server intial money data
		retval = recvn(sock, (char*)clientMoney, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("receive money data");
			break;
		}
		else if (retval == 0)
			break;
		printf("recv2\n");

		printf("value = %d, count = %d\n", clientMoney[0].value, clientMoney[0].count);

		// end to initial setting

		// start vending machine client logic

		// print menu
		selectFristMenu = PrintFirstMenu();
		if (selectFristMenu == 1) { // customer
			insertedMoney = InsertCoin(clientMoney); // insert money
			buf = SelectDrink(clientDrink, insertedMoney); // select drink and get change money
			GetChangeAndModifyList(clientMoney, clientDrink, buf); // get change and modify money, drink array
		}
		else if (selectFristMenu == 2) {
			//////////////////////
			// send modified clientDrink data
			retval = send(sock, (char*)clientDrink, BUFSIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("send drink data");
				break;
			}
			printf("after client logic send\n");

			// recevie modified clientDrink data
			retval = recvn(sock, (char*)clientDrink, BUFSIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("receive drink data");
				break;
			}
			else if (retval == 0)
				break;
			printf("after client logic recv\n");

			// send modified clientMoney data
			retval = send(sock, (char*)clientMoney, BUFSIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("send drink data");
				break;
			}
			printf("after client logic send2\n");

			// recevie modified clientMoney data
			retval = recvn(sock, (char*)clientMoney, BUFSIZE, 0);
			if (retval == SOCKET_ERROR) {
				err_display("receive drink data");
				break;
			}
			else if (retval == 0)
				break;
			printf("after client logic recv2\n");
			//////////////////////
			break;
		}
		else { // admin

		}

		// end to clinet logic

		// re send drink and money list

		// send modified clientDrink data
		retval = send(sock, (char*)clientDrink, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send drink data");
			break;
		}
		printf("after client logic send\n");

		// recevie modified clientDrink data
		retval = recvn(sock, (char*)clientDrink, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("receive drink data");
			break;
		}
		else if (retval == 0)
			break;
		printf("after client logic recv\n");

		// send modified clientMoney data
		retval = send(sock, (char*)clientMoney, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send drink data");
			break;
		}
		printf("after client logic send2\n");

		// recevie modified clientMoney data
		retval = recvn(sock, (char*)clientMoney, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("receive drink data");
			break;
		}
		else if (retval == 0)
			break;
		printf("after client logic recv2\n");
	}

	//closesocket()
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}
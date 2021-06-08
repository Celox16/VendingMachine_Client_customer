#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERIP "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE 512

////////////variable define/////////////
struct drinkInfo {
	char name[20];
	int price;
	int count;
};

struct moneyInfo {
	int value;
	int count;
};

extern drinkInfo list[5];
char drinkCount[5];
////////////////////////////////////////

///////////function define//////////////
extern int PrintFirstMenu();
extern void SetInitialArray(int vending[]);
extern void SetInitialStruct(drinkInfo buf_[]);
extern void SetInitialMoney(moneyInfo money[]);
////////////////////////////////////////

// ���� �Լ� ���� ����� ���� laptop
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

//���� �Լ� ���� ���
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
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
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

	// ������ ��ſ� ����� ����
	int buf[BUFSIZE + 1];
	int len;

	///////////////////if array is struct array?//////////////////////
	drinkInfo drink[BUFSIZE + 1];
	moneyInfo money[BUFSIZE + 1];
	//////////////////////////////////////////////////////////////////

	// ������ ������ ���
	while (1) {
		// ������ �Է�
		printf("\n[���� ������] ");
		
		//if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
		//	break;

		// '\n'���� ����
		//len = strlen(buf);
		//if (buf[len - 1] == '\n')
		//	buf[len - 1] = '\0';
		//if (strlen(buf) == 0)
		//	break;

		// ������ ������
		//retval = send(sock, (char*)&buf, strlen((char*)buf), 0);
		retval = send(sock, (char*)&drink, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			break;
		}
		printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� ���½��ϴ�.\n", retval);

		//retval = send(sock, (char*)&money, BUFSIZE, 0);

		// ������ �ޱ�
		retval = recvn(sock, (char*)&drink, retval, 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		// ���� ������ ���
		//buf_[retval].name = '\0';
		printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� �޾ҽ��ϴ�.\n", retval);
		//printf("[����������] %s\n", buf);
		printf("%d %d\n", drink[0].price, drink[1].price);


		///////////////one more!!////////////////
		SetInitialMoney(money);
		printf("\n=============================\n");
		retval = send(sock, (char*)&money, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("one more send");
			break;
		}

		retval = recvn(sock, (char*)&money, retval, 0);
		if (retval == SOCKET_ERROR) {
			err_display("one more receive err");
			break;
		}
		else if (retval == 0)
			break;

		printf("%d\n", money[0].value);
	}

	//closesocket()
	closesocket(sock);

	// ���� ����
	WSACleanup();
	return 0;
}
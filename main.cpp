#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma comment ( lib, "WSock32.lib" ) 

void ChatServer(void)
{
	SOCKET listen_s;
	SOCKET s;
	SOCKADDR_IN saddr;
	SOCKADDR_IN from;
	int fromlen;
	u_short uport;

	/*ポート番号の入力*/
	printf("使用するポート番号--> ");
	scanf_s("%hd", &uport);
	fflush(stdin);

	//int WASCleanup(void);
	
	//ソケッド関数
	//int socket(int add_family, int socket_type, int protocol);
	//bind関数
	//int bind(SOCKET, struct sockaddr*,sizeof(struct sockaddr));

	/*リスンソケットをオープン*/
	
	listen_s = socket(AF_INET,SOCK_STREAM,0);
	if (listen_s == INVALID_SOCKET)
	{
		printf("リスンソケットオープンエラー");
		//WASCleanup();
		return;

	}
	printf("リスンソケットをオープンしました\n");

	/*ソケットに名前をつける*/
	memset(&saddr, 0, sizeof(SOCKADDR_IN));

	/*SOCKADDR_IN型変数「saddr」の設定処理　*/
	memset(&saddr, 0, sizeof(SOCKADDR_IN));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(uport);
	saddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(listen_s,(struct sockaddr*)&saddr, sizeof(saddr)) == SOCKET_ERROR)
	{
		printf("bindエラー");
		closesocket(listen_s);
		return;
	}

	printf("bind成功");

	/*クライアントからの接続町の状態になる*/
	int listen(SOCKET, int);

	if (listen(listen_s,0) == SOCKET_ERROR)
	{
		printf("listenエラー");
		closesocket(listen_s);
		return;
	}
	printf("listen成功\n");
	
	/*接続を待機する*/
	printf("acceptで待機する");

	/*accept関数*/
	//int accept(SOCKET, struct sockaddr*, int*);

	fromlen = (int)sizeof(from);

	s = accept(listen_s,(SOCKADDR*)&from,&fromlen);/*SOCKADDR_IN型変数「from」を使ってaccept関数を実行　*/

	if (s == INVALID_SOCKET)
	{
		printf("acceptエラー\n");
		closesocket(listen_s);
		return;
	}

	printf("%sが接続してきました\n", inet_ntoa(from.sin_addr));
	printf("accept関数成功\n");
	/*リスン用のソケットはもう不要*/
	closesocket(listen_s);

	/*会話開始*/
	printf("会話開始\n");

	while (1)
	{
		int nRcv;

		char szBuf[1024];

		nRcv = recv(s, szBuf, sizeof(szBuf) - 1, 0);
		szBuf[nRcv] = '\0';

		printf("受信 --> %s\n", szBuf);
		printf("送信 --> ");

		scanf_s("%s", szBuf, 1024);
		fflush(stdin);

		send(s, szBuf, (int)strlen(szBuf), 0);



	}

	/*ソケットを閉じる*/
	closesocket(s);


}

int main()
{
	WSADATA wsaData;
	int mode;

	/* WinSock初期化 */
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		/* エラー */
		printf("WinSockの初期化に失敗しました\n");
		return 1;
	}

	/* サーバーか？クライアントか？ */
	printf("サーバーなら0を入力 クライアントなら1を入力 --> ");

	scanf_s("%d", &mode);

	fflush(stdin);

	if (mode == 0) {
		/* サーバーとして起動 */
		ChatServer();
	}
	
	/* WinSockの終了処理 */
	WSACleanup();

	return 0;

}
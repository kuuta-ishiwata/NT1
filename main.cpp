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

	/*�|�[�g�ԍ��̓���*/
	printf("�g�p����|�[�g�ԍ�--> ");
	scanf_s("%hd", &uport);
	fflush(stdin);

	//int WASCleanup(void);
	
	//�\�P�b�h�֐�
	//int socket(int add_family, int socket_type, int protocol);
	//bind�֐�
	//int bind(SOCKET, struct sockaddr*,sizeof(struct sockaddr));

	/*���X���\�P�b�g���I�[�v��*/
	
	listen_s = socket(AF_INET,SOCK_STREAM,0);
	if (listen_s == INVALID_SOCKET)
	{
		printf("���X���\�P�b�g�I�[�v���G���[");
		//WASCleanup();
		return;

	}
	printf("���X���\�P�b�g���I�[�v�����܂���\n");

	/*�\�P�b�g�ɖ��O������*/
	memset(&saddr, 0, sizeof(SOCKADDR_IN));

	/*SOCKADDR_IN�^�ϐ��usaddr�v�̐ݒ菈���@*/
	memset(&saddr, 0, sizeof(SOCKADDR_IN));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(uport);
	saddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(listen_s,(struct sockaddr*)&saddr, sizeof(saddr)) == SOCKET_ERROR)
	{
		printf("bind�G���[");
		closesocket(listen_s);
		return;
	}

	printf("bind����");

	/*�N���C�A���g����̐ڑ����̏�ԂɂȂ�*/
	int listen(SOCKET, int);

	if (listen(listen_s,0) == SOCKET_ERROR)
	{
		printf("listen�G���[");
		closesocket(listen_s);
		return;
	}
	printf("listen����\n");
	
	/*�ڑ���ҋ@����*/
	printf("accept�őҋ@����");

	/*accept�֐�*/
	//int accept(SOCKET, struct sockaddr*, int*);

	fromlen = (int)sizeof(from);

	s = accept(listen_s,(SOCKADDR*)&from,&fromlen);/*SOCKADDR_IN�^�ϐ��ufrom�v���g����accept�֐������s�@*/

	if (s == INVALID_SOCKET)
	{
		printf("accept�G���[\n");
		closesocket(listen_s);
		return;
	}

	printf("%s���ڑ����Ă��܂���\n", inet_ntoa(from.sin_addr));
	printf("accept�֐�����\n");
	/*���X���p�̃\�P�b�g�͂����s�v*/
	closesocket(listen_s);

	/*��b�J�n*/
	printf("��b�J�n\n");

	while (1)
	{
		int nRcv;

		char szBuf[1024];

		nRcv = recv(s, szBuf, sizeof(szBuf) - 1, 0);
		szBuf[nRcv] = '\0';

		printf("��M --> %s\n", szBuf);
		printf("���M --> ");

		scanf_s("%s", szBuf, 1024);
		fflush(stdin);

		send(s, szBuf, (int)strlen(szBuf), 0);



	}

	/*�\�P�b�g�����*/
	closesocket(s);


}

int main()
{
	WSADATA wsaData;
	int mode;

	/* WinSock������ */
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		/* �G���[ */
		printf("WinSock�̏������Ɏ��s���܂���\n");
		return 1;
	}

	/* �T�[�o�[���H�N���C�A���g���H */
	printf("�T�[�o�[�Ȃ�0����� �N���C�A���g�Ȃ�1����� --> ");

	scanf_s("%d", &mode);

	fflush(stdin);

	if (mode == 0) {
		/* �T�[�o�[�Ƃ��ċN�� */
		ChatServer();
	}
	
	/* WinSock�̏I������ */
	WSACleanup();

	return 0;

}
//아이디 길이 제한??
/*
Student ID : 20123345
Name : Kim Jung Min
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

#define MAX 10000
#define none "none"
#define noarg "\nnoArg"
#define version "1.0"
#define msSize 1024
#define MAXHEADER 100
#define MAXUSER 30
#define portnum 10005

struct INFO{
	char ID[10];
	char IP[16];
	int PORT;
}INFO;

void initDis();
void waitingDis(struct INFO list[], char ID[10]);
void chatDis(char* ID);
void outputLine(char name[]);
void requestForServer(int sock, char requestType[], char requestId[]);//로그인 서버에 리퀘스트메시지를 보내는 함수
void requestForUser(int sock, char requestId[], char requestType[], struct INFO* list, char messege[]); //유저간 리퀘스트메시지를 보내는 함수
void responseForUser(int sock, char responseType[], char error[]);	//유저간 리스폰스메시지를 받는 함수
char* responseForServer(int sock, char requestId[], int *isOK);
void StringToInfo(struct INFO* info,char string[]);
////
//char **my_addrs(int *addrtype);
//

int readUserResponse(int sock);
int readUserRequest(int sock, struct INFO* chatList, int sockList[], char myId[], fd_set* myMask, int* fd_max, int* isOnChat, char* otherUserID);

// 사용자의 입력대기후 입력을 엔터로 완료하면 사용자가 입력한 스트링이 com인자에 입력한 명령어가 있으면 filter 캐릭터값 이후 스트링을 반환함. 없으면 "none" 반환(com2는 대문자도 가능하기위해)
char* waitCommand(char* message ,char com[], char com2[], char filter[]);

//int peertcpSocket = -1;	// peer socket

//char myID[10];

int main(int argc, char **argv) {
	
  //int tcpServ_sock;
	//
	int user_sock, wait_sock, invite_sock;
	int sockList[MAXUSER]= {-1,};
	int noServerHostp = 0;
	struct sockaddr_in server, waitUser, inviteUser, remote;
	char ID[10] = {};
	char IP[16] = {};
	char serverBody[MAX] = {};
	struct INFO info[MAXUSER], chatList[MAXUSER];
	int isOnChat = 0;
	fd_set rmask, mask;
	int maxfd, nfound;

	//////////////////
//	struct in_addr in;
//   char **addr;
//   int type;

//	addr=my_addrs(&type);
//	memcpy(&in.s_addr, *addr, sizeof (in.s_addr));
	//
  
//  struct sockaddr_in tcpServer_addr;
//  struct sockaddr_in tcpClient_addr;
//  struct sockaddr_in newTcp_addr;

//  int clnt_len;
	
  //fd_set reads, temps;
  //int fd_max;

  //char command[1024];


  //char *tcpport = NULL;
  //char *userid = NULL;

// NEED TO ADD SOME VARIABLES 
	//
  struct hostent *serverHostp;
	//

  //char cpyCommand[1024];
  //char messege[BUFSIZ];
  //char *filterCommand[3] = {};
  //char *connectTcpport = NULL;
  //int isConnect = -1;
  //int bytesread;
  //int newSock;
  //int c;

//  if(argc != 3){
//	printf("Usage : %s <tcpport> <userid>\n", argv[0]);
//	exit(1);
//  }
	int a;
	for(a=0; a<MAXUSER; a++)
	{
		strcpy(info[a].ID,"");
		strcpy(info[a].IP,"");
		strcpy(chatList[a].ID,"");
		strcpy(chatList[a].IP,"");
		sockList[a] = -1;
	}

	//1. 초기 접속 화면
	initDis();
	

	// NEED TO CREATE A SOCKET FOR TCP SERVER
//  tcpport = argv[1];
//  userid = argv[2];

//로그인 명령어로 로그인 서버에 커넥션이 성공 할 때 까지 루프를 돈다.
	while(1){
		char loginCommand[MAX] = {};
		char* conInfo[3] = {};
		char message[MAX] = {};
		int isOK=0;
	
		outputLine("");

		fgets(message,sizeof(message),stdin);
		fflush(stdin);
		fflush(stdout);
		if(message[0] == '\n')
			continue;

		//입력한 문자열이 @login,@LOGIN으로 시작할때 까지 무한루프
		while(!strcmp((strcpy(loginCommand,waitCommand(message ,"@login", "@LOGIN"," \t"))),none))
		{
			if(strcmp((strcpy(loginCommand,waitCommand(message ,"@quit", "@QUIT"," \t"))),none))
				exit(1);
			outputLine("");
			fgets(message,sizeof(message),stdin);
			fflush(stdin);
			fflush(stdout);
			if(message[0] == '\n')
				continue;
		}

		//@login or @LOGIN을 제외한 문자열의 형식이 string/string/string 일 경우
		if((strcmp(loginCommand, noarg))&&((conInfo[0] = strtok(loginCommand,"/")) && (conInfo[1] = strtok(NULL, "/")) && (conInfo[2] = strtok(NULL,"/")) && (strlen(conInfo[0]) <= 9)))
		{
			//로그인 서버와 연결할 소켓을 연다.
			if((user_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
			{
				perror("socket error.");
				exit(1);
			}

			//커넥션을 위한 준비
			memset((void *) &server, 0, sizeof (server));
			server.sin_family = AF_INET;
			server.sin_port = htons((u_short)atoi(conInfo[2]));

			//입력한 <SERVERIP>부분이 도메인일 경우
			if((serverHostp = gethostbyname(conInfo[1])) != 0)
			{
				memcpy((void *) &server.sin_addr, serverHostp->h_addr, serverHostp->h_length);
			}
			//입력한 <SERVERIP>부분이 도메인이 아닐 경우
			else
			{
				server.sin_addr.s_addr = inet_addr(conInfo[1]);
			}
	
			//커넥션을 한다. 실패할 경우 에러 출력.
			if (connect(user_sock, (struct sockaddr *)&server, sizeof (server)) < 0) {
				(void) close(user_sock);
				perror("connect error for login server. plese check input value.");
			}
			//커넥션을 성공할 경우 루프를 빠져나옴.
			else
			{
				//로그인 서버에 리퀘스트 메세지 전송.
				strcpy(ID, conInfo[0]);
				requestForServer(user_sock, "LOGIN", ID);
				//break;
				//리스폰스 받는 함수 넣고 이게 완료되면 루프탈출, 아니면 루프돌게 짜기
				strcpy(serverBody,responseForServer(user_sock, ID, &isOK));
				if(!isOK)
				{
					fflush(stdout);
					printf("error : %s.", serverBody);
					fflush(stdout);
				}
				else
				{
					StringToInfo(info,serverBody);	//서버에서 받아온 아이디리스트를 INFO구조체에 입력
					break;
				}
			}
		}
		else if((conInfo[0])&&(strlen(conInfo[0]) > 9)){
			printf("ID size must be short than 10.\n");
			fflush(stdout);
		}
		else
		{
			printf("Usage : @login(@LOGIN) <ID>/<SERVERIP>/<PORT>\n");
			fflush(stdout);
		}
	}

	for(a=0; a<MAXUSER; a++)
	{
		if(!strcmp(info[a].ID, ID))
		{
			strcpy(IP, info[a].IP);
			break;
		}
	}
	//채팅방 초대에 응할 소켓을 만든다.
	if((wait_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		perror("socket error\n");
		exit(0);
	}

	//소켓과 바인딩 작업
	memset((void *) &waitUser, 0, sizeof(waitUser));
	waitUser.sin_family = AF_INET;
	waitUser.sin_addr.s_addr = inet_addr(IP);
	waitUser.sin_port = htons((u_short)portnum);

	//printf("%s\n",  IP);////////////////////////////////////////
	//fflush(stdout);//////////////////////////////////////

	if(bind(wait_sock,(struct sockaddr *)&waitUser,sizeof(waitUser)) < 0)
	{
		perror("binding error\n");
		exit(0);
	}

	//소켓의 리슨 작업
	if(listen(wait_sock, SOMAXCONN) < 0)
	{
		perror("listen error\n");
		exit(0);
	}

	//셀렉트 함수 사용을 위한 mask 초기
	FD_ZERO(&mask);
	
	// set the mask
	FD_SET(fileno(stdin), &mask);
	FD_SET(wait_sock, &mask);
	maxfd = wait_sock;

	//로그인후 대기화면 루프(셀렉트 함수 사용 루프)
	while(1){
		char message[MAX] = {};
		char command[MAX] = {};
		int addrlen;

		if(isOnChat)
			;//chatDis();
		else
			waitingDis(info, ID);	//채팅 대기방(연결 가능한 유저 아이디리스트 출력 화면)화면 출력
		rmask = mask;
		nfound = select(maxfd + 1, &rmask, (fd_set *)0, (fd_set *)0, NULL);
		
		if(FD_ISSET(fileno(stdin), &rmask))
		{
			fgets(message,sizeof(message),stdin);
			fflush(stdin);
			fflush(stdout);

			if(message[0] == '\n')
				continue;

			FD_CLR(fileno(stdin), &rmask);
			//printf("%s\n",info[0].ID);
			//fflush(stdout);

			if(strcmp((strcpy(command,waitCommand(message ,"@invite", "@INVITE"," \t"))),none))
			{
				if(	(strcmp(command, noarg)) && (command != NULL))
				{
					int a, b;
					int existId = 0;

					if(!strcmp(command, ID))
					{
						printf("No invite me!!");
						printf("\nInsert anyKey to continue.\n");
						fflush(stdout);
						getchar();
						fflush(stdin);
						continue;
					}
	
					for(a=0; a< MAXUSER; a++)
					{
						if(!strcmp(info[a].ID, command))
						{
							existId=1;
							for(b=0; b<MAXUSER; b++)
							{
								if(sockList[b]<0)
									break;
							}
							//초대할 사용자와 연결하기 위한 소켓을 연다.
							if((sockList[b] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
							{
								perror("socket error.");
								exit(1);
							}

							//커넥션을 위한 준비
							memset((void *) &inviteUser, 0, sizeof (inviteUser));
							inviteUser.sin_family = AF_INET;
							inviteUser.sin_port = htons((u_short)portnum);
							inviteUser.sin_addr.s_addr = inet_addr(info[a].IP);

							//printf("%s\n",info[a].IP);/////////////////////////////////////////////////////////////////////////////////////////
							//fflush(stdout);////////////////////////////////////////////////////////////////////////////////////////////
	
							//커넥션을 한다. 실패할 경우 에러 출력.
							if (connect(sockList[b], (struct sockaddr *)&inviteUser, sizeof (inviteUser)) < 0) {
								(void) close(sockList[b]);
								sockList[b]=-1;
								perror("connect error for other user. plese check other user id.");
								printf("\nInsert anyKey to continue.\n");
								fflush(stdout);
								getchar();
								fflush(stdin);
								break;
							}

							//int e;
							//for(e=0; e<MAXUSER; e++)
							//	if(strcmp(chatList[e].ID,""))
							//		printf("%s/%s/%d\n",chatList[e].ID,chatList[e].IP,chatList[e].PORT);

							//fflush(stdout);//////////////?<<<<><><><><><><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
							//커넥션 성공한 경우 리퀘스트 메시지 입력
							requestForUser(sockList[b], ID, "INVITE", chatList, "");

							//printf("send request\n");///////////////////////////////////////////////////////
							//sockList select처리 필요
							if(readUserResponse(sockList[b]))///////////////////////////////////---------------------------------------------------------------
							{
								int c;
								FD_SET(sockList[b], &mask);
								if(maxfd < sockList[b])
									maxfd = sockList[b];

								for(c=0; c< MAXUSER; c++)
								{
									if(!strcmp(chatList[c].ID,""))
									{
										strcpy(chatList[c].ID, info[a].ID);
										strcpy(chatList[c].IP, info[a].IP);
										chatList[c].PORT = info[a].PORT;
										break;
									}
								}
								if(!isOnChat)
								{
									chatDis(ID);
									isOnChat = 1;
								}
							}
							else
							{
								if (close(sockList[b]))
								{
									perror("close socket error.");
									exit(1);
								}
								sockList[b]=-1;
							}
							//방연결안대면 소켓 닫고 -1 처리
							break;
						}
					}

					//해당 유저아이디가없을경우
					if(!existId)
					{
						printf("No such user id.\n");
						printf("\nInsert anyKey to continue.\n");
						fflush(stdout);
						getchar();
						fflush(stdin);
					}
				}
				else
				{
					printf("Usage : @invite(@INVITE) <ID>\n");
					fflush(stdout);
				}
			}

			else if(strcmp((strcpy(command,waitCommand(message ,"@userlist", "@USERLIST"," \t"))),none))
			{
				//printf("zz\n");
				int isOK = 0;
				requestForServer(user_sock, "RENEW", ID);
				strcpy(serverBody,responseForServer(user_sock, ID, &isOK));//////////////////////////////////////////////
				if(!isOK)
				{
					printf("error : %s.", serverBody);
					fflush(stdout);
				}
				else
				{
					StringToInfo(info,serverBody);	//서버에서 받아온 아이디리스트를 INFO구조체에 입력
					int aa=0;
					if(isOnChat)
					{
						printf("*********************ID LIST*********************\n");
						while(1)
						{
							if((aa>=MAXUSER)||(!strcmp(info[aa].ID,"")))
								break;
							printf("%s/%s/%d\n",info[aa].ID, info[aa].IP, info[aa].PORT);
							aa++;
						}
						printf("*************************************************\n\n");
						fflush(stdout);
					}
				}
			}

			else if(strcmp((strcpy(command,waitCommand(message ,"@quit", "@QUIT"," \t"))),none))
			{
				close(wait_sock);
				exit(1);
			}

			else if(isOnChat) //채팅방 내에서 일반적인 채팅
			{
				int a;
				char chatMs[MAX] = {};
				sprintf(chatMs, "%s> %s\n",ID, message);
				for(a=0; a<MAXUSER; a++)
				{
					if(sockList[a]>=0)
					{
						//printf("what??%d\n",a);
						//fflush(stdout);
						requestForUser(sockList[a], ID, "CHAT", chatList, chatMs);
					}
				}
			}
		}
		else if(FD_ISSET(wait_sock, &rmask))/////누군가 커넥션 요청을 할 경우(invite, must)
		{
			int a, isMax=1;
			char otherUserID[10] = {};

			//printf("in wait_sock\n");///////////////////////////////////////////////////////////////////////////////////////////////
				//fflush(stdout);

			FD_CLR(wait_sock, &rmask);
			for(a=0; a<MAXUSER; a++)
			{
				if(sockList[a] < 0)
				{
					isMax = 0;
					break;
				}
			}
			
			if(!isMax)
			{
				sockList[a] = accept(wait_sock, (struct sockaddr *)&remote, &addrlen);//////////
				//printf("0x%x\n",remote.sin_addr.s_addr);
				//fflush(stdout);
				
				if(sockList[a] < 0)
				{
					(void)close(wait_sock);
					perror("Accept error.\n");
					exit(0);
				}
				//char* temp = NULL;
				//printf("in accept\n");///////////////////////////////////////////////////////////////////////////////////////////////<<<<<<<<<<<<<<<<<<<<
				//fflush(stdout);
				if(readUserRequest(sockList[a], chatList, sockList, ID, &mask, &maxfd, &isOnChat, otherUserID))//성공한 메시지일 경우
				{
					int isOK = 0;
					requestForServer(user_sock, "RENEW", ID);
					strcpy(serverBody,responseForServer(user_sock, ID, &isOK));//////////////////////////////////////////////
					if(!isOK)
					{
						printf("error : %s.", serverBody);
						fflush(stdout);
					}
					else
					{
						StringToInfo(info,serverBody);	//서버에서 받아온 아이디리스트를 INFO구조체에 입력
					}
					
					//temp = inet_ntoa(remote.sin_addr);
					int b, x;
					for(b=0; b<MAXUSER; b++)
					{
						if(!strcmp(chatList[b].ID,""))
						{
							for(x=0; x<MAXUSER; x++)
							{
								if(!strcmp(info[x].ID,otherUserID))
								{
									strcpy(chatList[b].ID, info[x].ID);
									strcpy(chatList[b].IP, info[x].IP);
									chatList[b].PORT = portnum;
									break;
								}
							}
							//strcpy(chatList[b].IP, inet_ntoa(remote.sin_addr.s_addr));

							FD_SET(sockList[a], &mask);
							if(maxfd < sockList[a])
								maxfd = sockList[a];

							break;
						}
					}
				}
				else//실패한 메시지일경우
				{
					if (close(sockList[a]))
					{
						//perror("close socket");
						//exit(1);
					}
					sockList[a] = -1;
				}
			}
			else
			{
				printf("So MAX!!\n");
				fflush(stdout);
				continue;//
			}
		}
		else//이 부분은 sockList로 셀렉트 체크 구현
		{
			int a;
			for(a=0; a<MAXUSER; a++)
			{
				if(FD_ISSET(sockList[a], &rmask))
				{
					FD_CLR(sockList[a],&rmask);
					readUserRequest(sockList[a], chatList, sockList, ID, &mask, &maxfd, &isOnChat, chatList[a].ID);
					break;
				}
			}
		}///////////////////////////////////////여기까지 완
	//printf("%s",info[0].ID);
	}


//  if((tcpServ_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
//  {
//  	perror("socket error\n");
//  	exit(0);
//  }
	return 0;
}//main End

void initDis() {
	system("clear");
	printf("input @login(@LOGIN) <ID>/<SERVERIP>/<PORT> to login to server.\n");
	fflush(stdout);
}

void waitingDis(struct INFO list[], char ID[10]) {
	int a=0;
	system("clear");
	printf("*********************ID LIST*********************\n");
	while(1)
	{
		if((a>=MAXUSER)||(!strcmp(list[a].ID,"")))
			break;

		printf("%s/%s/%d\n",list[a].ID, list[a].IP, list[a].PORT);
		a++;
	}
	printf("*************************************************\n\n");
	printf("-Insert next instruction to connect to chatting room or do other working.\n");
	printf("1. @invite(@INVITE) <ID> : invite <ID> user for yor chatting room.\n");
	printf("2. @userlist(@USERLIST) : refresh ID list connecting to server.\n");
	printf("3. @quit(@QUIT) : finish this program.\n");
	fflush(stdout);
	outputLine(ID);
}

void chatDis(char* ID) {
system("clear");
printf("----------------------Welcome New Chatting Room----------------------\n");
//outputLine(ID);

}

// 사용자의 입력대기후 입력을 엔터로 완료하면 사용자가 입력한 스트링이 com인자에 입력한 명령어가 있으면 filter 캐릭터값 이후 스트링을 반환함. 없으면 "none" 반환(com2는 대문자도 가능하기위해)
char* waitCommand(char* message ,char com[], char com2[], char filter[]){
	char cpyms2[MAX] = {};
	char cpyms[MAX] = {};
	char* f[2];
	//fgets(message,sizeof(message),stdin);
	//fflush(stdin);
	//fflush(stdout);
	strcpy(cpyms, message);
	cpyms[strlen(cpyms)-1] = '\0';
	strcpy(cpyms2, cpyms);
	f[0] = strtok(cpyms, filter);
	f[1] = strtok(NULL, filter);
	//printf("%s\n",cpyms);
	//fflush(stdout);

	if((strcmp(f[0],com)&&strcmp(f[0],com2))&&(strcmp(cpyms2,com)&&strcmp(cpyms2,com2)))
		return none;
	else if(!(strcmp(cpyms2,com)&&strcmp(cpyms2,com2)) || f[1]==NULL)
		return noarg;
	else
		return f[1];
}

void outputLine(char name[]){
	printf("\n%s> ",name);
	fflush(stdout);
}

void requestForServer(int sock, char requestType[], char requestId[]){
	char format[msSize] = {};
	sprintf(format, "%s %s\r\nID: %s\r\n\r\n", requestType, version, requestId);
	fflush(stdin);
	fflush(stdout);
	//printf("%s %d",format, sizeof(format));

	if(write(sock, format, sizeof(format)) < 0)
	{
		perror("write fail for login server.\n");
		exit(0);
	}
	//printf("ok?\n");
}

void requestForUser(int sock, char requestId[], char requestType[], struct INFO* list, char messege[]){
	char totalMessege[MAX] = {};
	char format[msSize] = {};
	int bodyLen = 0;
	//int isBody = 1;
	char bodyLine[MAX] = {};
	int a;
	int msLen = 0;
	int repeat = 0;

	if(strcmp(requestType,"CHAT"))
	{
		for(a=0; a<MAXUSER; a++)
		{
			if(strcmp(list[a].ID,""))
			{
				char token[MAX] = {};
				sprintf(token,"%s/%s/%d ", list[a].ID, list[a].IP, list[a].PORT);
				strcat(bodyLine,token);///error??			
			}
		}
	}
	else
	{
		strcpy(bodyLine, messege);
	}

	if(bodyLine[0] == '\0')
	{
		sprintf(totalMessege, "%s %s\r\nID: %s\r\nContent-Length: 0\r\n\r\n", requestType, version, requestId);
	}
	else
	{
		bodyLen = strlen(bodyLine);
		sprintf(totalMessege, "%s %s\r\nID: %s\r\nContent-Length: %d\r\n\r\n%s\r\n\r\n", requestType, version, requestId, bodyLen, bodyLine);
	}

	msLen = strlen(totalMessege);

	repeat = msLen/msSize;
	msLen -= repeat*msSize;
	if(msLen>0)
		repeat++;
	//printf("%s %d",format, sizeof(format));

	for(a=0; a<repeat; a++)
	{
		char wToken[msSize+1]= {};
		int len = 0;
		strncpy(wToken, &(totalMessege[a*msSize]), msSize);
		len = strlen(wToken);

		if(len>msSize)
			len = msSize;

		if(write(sock, wToken, len) < 0)
		{
			perror("write fail for other user.\n");
			exit(0);
		}
	}
}

char* responseForServer(int sock, char requestId[], int *isOK){
	int bytesread;
	int totalLen=0;
	char format[msSize+1] = {};
	char totalBody[MAX] = {};
	bytesread = read(sock, format, sizeof(format) - 1);
	format[bytesread] = '\0';
	//printf("%s",format);
	//fflush(stdout);
	if(bytesread<=0)
	{
		printf("Login server has been closed or Network error.\n");
		fflush(stdout);

		if (close(sock))
		{
			perror("close socket");
			//exit(1);
		}
		exit(1);
	}
	//format[bytesread] = '\0';
	//strtok 관련 함수로 메시지를 어케 분류할건지... 헤더와 바디를 어케 구분할것이며... 커서처럼 움직일 수 있는 함수 없나?
	char* headerLine[MAXHEADER] = {};
	char* nextLine = 0;
	char* bodyLine = 0;
	char* serverVersion = 0;
	int a, b, headerNum, isBody = 0;

	char* resHeader = 0;
	//int isOK = 0;

	//printf("%s\n",format);
	headerLine[0] = strtok(format, "\n");
	
	for(a=1; a<MAXHEADER; a++)
	{
		if(!strcmp((nextLine = strtok(NULL, "\n")),"\r"))
		{
			headerNum = a;
			bodyLine = strtok(NULL, "\n");
			//bodyLine = strtok(NULL, "\r");
			//printf("%s",bodyLine);
			fflush(stdout);
			if(bodyLine!=NULL)
			{
				isBody = 1;
				strtok(NULL,"\r\n");
			}
			break;
		}
		else
		{
			headerLine[a] = nextLine;
			//strtok(NULL,"\r");
			//printf("%s\n",headerLine[1]);//
			//fflush(stdout);
		}
	}//헤더와 바디 분류

	//헤더의 길이
	for(b=0; b<headerNum; b++)
	{
		totalLen += (strlen(headerLine[b]) + 1);
	}
	
	//맨 처음 헤더(1.0 OK...) : 응답헤더
	serverVersion = strtok(headerLine[0], " ");
	resHeader = strtok(NULL, " ");
	//printf("resHeader: %s\n",resHeader);
	//fflush(stdout);

	if(!strcmp(resHeader,"OK\r"))
	{
		*isOK=1;
		for(a=1; a<headerNum; a++)
		{
			char* header = NULL;
			header = strtok(headerLine[a], " ");
			//printf("%s\n",header);//////////////////////////////////////////////////////////////////
			//fflush(stdout);////////////////////////////////////////////////
			if(!strcmp(header,"Content-Length:"))
			{
				char* byte;
				int Byte;
				byte = strtok(NULL, " \r");
				//printf("zz\n");
				//printf("%s\n",byte);//
				//fflush(stdout);//
				Byte = atoi(byte);
				totalLen += (Byte+6);
				//printf("%d\n",Byte);//
				//fflush(stdout);//
				//printf("%s",bodyLine);
				//fflush(stdout);
				strcpy(totalBody, bodyLine);
				if(totalLen>1024)
				{
					int repeat = totalLen/1024;
					int b;
					int totalBit = 1024;
					totalLen %= 1024;
					if(totalLen == 0)
						repeat--;
					for(b=0; b<repeat; b++)
					{
						char add[msSize+1] = {};
						bytesread = read(sock, add, sizeof(add) - 1);
						add[bytesread] = '\0';
						totalBit += bytesread;
						strcat(totalBody, add);
						//여기까지 바디받음
					}
				}
			}
		}

	//strcmp(myID,requestId);
	//printf("%s\n",totalBody);//
	//fflush(stdout);//
	return totalBody;
	}
	else if(!strcmp(resHeader,"ERROR\r"))
	{
		*isOK=0;
		return bodyLine;
	}
	else
	{
		perror("Response Header Error.\n");
		exit(1);
	}
}

void responseForUser(int sock, char responseType[], char error[]){
	char messege[msSize] = {};

	if(strcmp(responseType,"ERROR"))
	{
		sprintf(messege,"%s %s\r\nContent-Length: 0\r\n\r\n", version, responseType);
	}
	else
	{
		sprintf(messege,"%s %s\r\nContent-Length: %d\r\n\r\n%s\r\n\r\n", version, responseType, strlen(error), error);
	}

	if(write(sock, messege, sizeof(messege)) < 0)
	{
		perror("write fail for other user.\n");
		exit(0);
	}	
}

//뭔가 실패시 0 반환 -> 커넥션해제해야함
int readUserRequest(int sock, struct INFO* chatList, int sockList[], char myId[], fd_set* myMask, int* fd_max, int* isOnChat, char* otherUserID){
	int bytesread;
	int totalLen=0;
	char format[msSize+1] = {};
	char totalBody[MAX] = {};
	bytesread = read(sock, format, sizeof(format) - 1);
	format[bytesread] = '\0';
	//printf("%s\n",format);/////////////////////////////////////////////////////////////////////
	//fflush(stdout);/////////////////////////////////////////////////////////////////////
	//printf("%s",format);///////////////////////////////////////////////////////
	//printf("%s",format);
	//fflush(stdout);
	if(bytesread<=0)
	{
		int a;
		if(*isOnChat)
		{
			printf("Exit One User.\n");
			fflush(stdout);
			for(a=0; a<MAXUSER; a++)
			{
				if(!strcmp(chatList[a].ID,otherUserID))
					strcpy(chatList[a].ID,"");
			}
		}
		else
		{
			printf("Network error.\n");
			fflush(stdout);
			exit(1);
		}

		FD_CLR(sock , myMask);

		if (close(sock))
		{
			perror("close socket");
			exit(1);
		}

		for(a=0; a < MAXUSER; a++)
		{
			if(sockList[a]==sock)
			{
				sockList[a] = -1;
				break;
			}
		}
		return 0;
	}
	//format[bytesread] = '\0';
	//strtok 관련 함수로 메시지를 어케 분류할건지... 헤더와 바디를 어케 구분할것이며... 커서처럼 움직일 수 있는 함수 없나?
	char* headerLine[MAXHEADER] = {};
	char* nextLine = 0;
	char* bodyLine = 0;
	char* reqVersion = 0;
	int a, b, headerNum, isBody = 0;
	//char* otherUserID = NULL;

	char* reqHeader = 0;
	//int isOK = 0;

	//printf("zz\n");////////////////////////////////////////////////////////////////
	//printf("%s\n",format);
	headerLine[0] = strtok(format, "\n");
	
	for(a=1; a<MAXHEADER; a++)
	{
		if(!strcmp((nextLine = strtok(NULL, "\n")),"\r"))
		{
			headerNum = a;
			bodyLine = strtok(NULL, "\n");
			//bodyLine = strtok(NULL, "\r");
			//printf("%s",bodyLine);
			fflush(stdout);
			if(bodyLine!=NULL)
			{
				isBody = 1;
				strtok(NULL,"\r\n");
			}
			break;
		}
		else
		{
			headerLine[a] = nextLine;
			//strtok(NULL,"\r");
			//printf("%s\n",headerLine[1]);//
			//fflush(stdout);
		}
	}//헤더와 바디 분류
	//printf("after body and head\n");////////////////////////////////////////////////////////////////
	//헤더의 길이
	for(b=0; b<headerNum; b++)
	{
		totalLen += (strlen(headerLine[b]) + 1);
	}
	
	//맨 처음 헤더(1.0 OK...) : 응답헤더
	reqHeader = strtok(headerLine[0], " ");
	reqVersion = strtok(NULL, " ");
	//printf("resHeader: %s\n",resHeader);
	//fflush(stdout);
	//printf("before header check\n");////////////////////////////////////////////////////////////////
	//fflush(stdout);////////////////////////////////////////////
	for(a=1; a<headerNum; a++)
	{
		char* header = NULL;
		header = strtok(headerLine[a], " ");

		//printf("%s\n", header);////////////////////////////////////////////////////////////////11111111111111111111111111111111111111111111111111111111111111
		//fflush(stdout);////////////////////////////////////////////
		if(!strcmp(header,"Content-Length:"))
		{
			//printf("in Cont check\n");////////////////////////////////////////////////////////////////
			//fflush(stdout);////////////////////////////////////////////
			char* byte;
			int Byte;
			byte = strtok(NULL, " \r");

			//printf("point1\n");////////////////////////////////////////////////////////////////
			//fflush(stdout);////////////////////////////////////////////
			//printf("zz\n");
			//printf("%s\n",byte);//
			//fflush(stdout);//
			Byte = atoi(byte);
			totalLen += (Byte+6);
			//printf("point2\n");////////////////////////////////////////////////////////////////
			//fflush(stdout);////////////////////////////////////////////
			//printf("%d\n",Byte);//
			//fflush(stdout);//
			//printf("%s",bodyLine);
			//fflush(stdout);
			//printf("%s\n",bodyLine);/////////////////////////////////////////////////////////////
			//fflush(stdout);/////////////////////////////////////////////
			//int b;
			//for(b=0; b<MAXUSER; b++)
			//{
			//	if(bodyLine[b]=='\0')
			//	{
			//		totalBody[b]='\0';
			//		break;
			//	}
			//	totalBody[b] = bodyLine[b];
			//}
			if(isBody)
				strcpy(totalBody, bodyLine);
			//printf("point3\n");////////////////////////////////////////////////////////////////
			//fflush(stdout);////////////////////////////////////////////
			if(totalLen>1024)
			{
				int repeat = totalLen/1024;
				int b;
				int totalBit = 1024;
				totalLen %= 1024;
				if(totalLen == 0)
					repeat--;
				//printf("in ConLoof check\n");////////////////////////////////////////////////////////////////
				//fflush(stdout);////////////////////////////////////////////
				for(b=0; b<repeat; b++)
				{
					char add[msSize+1] = {};
					bytesread = read(sock, add, sizeof(add) - 1);
					add[bytesread] = '\0';
					totalBit += bytesread;
					strcat(totalBody, add);
					//여기까지 바디받음
				}
			}
			//printf("after Cont check\n");////////////////////////////////////////////////////////////////
			//fflush(stdout);////////////////////////////////////////////
		}
		else if(!strcmp(header, "ID:"))
		{
			char* tok;
			int f;
			tok = strtok(NULL, " \r");//////////////////////////수정바람
			for(f=0; f<10; f++)
			{
				if(tok[f]=='\0')
				{
					otherUserID[f]='\0';
					break;
				}
				otherUserID[f] = tok[f];
			}
			//printf("%sb\n",otherUserID);
			//fflush(stdout);
		}
		else
		{
			printf("%s\n",header);
			perror("Unknown Header Error.\n");
			fflush(stdout);
			exit(1);
		}
	}
	//printf("after header check\n");////////////////////////////////////////////////////////////////
	//fflush(stdout);/////////////////////////////////////////////////////////

	//printf("%s\n",reqHeader);
	if(!strcmp(reqHeader,"INVITE"))
	{
		//printf("in ifINVITE\n");///////////////////////////////////////////////
		if(*isOnChat)
		{
			responseForUser(sock, "ERROR", "This user already has been in chatting room.");

			FD_CLR(sock , myMask);

			int d;
			for(d=0; d<MAXUSER; d++)
			{
				if(sockList[d] == sock)
				{
					sockList[d]=-1;
					break;
				}
			}

			if (close(sock))
			{
				perror("close socket");
				exit(1);
			}
			return 0;
		}
		else	//리스트받아서 나머지 유저와 연결
		{
			int a;
			struct sockaddr_in inviteUser;
			responseForUser(sock, "OK", "");
			StringToInfo(chatList, totalBody);
			for(a=0; a< MAXUSER; a++)
			{
				if(strcmp(chatList[a].ID,""))
				{
					for(b=0; b<MAXUSER; b++)
					{
						if(sockList[b]<0)
							break;
					}
					//초대할 사용자와 연결하기 위한 소켓을 연다.
					if((sockList[b] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
					{
						perror("socket error.");
						exit(1);
					}

					//커넥션을 위한 준비
					memset((void *) &inviteUser, 0, sizeof (inviteUser));
					inviteUser.sin_family = AF_INET;
					inviteUser.sin_port = htons((u_short)portnum);
					inviteUser.sin_addr.s_addr = inet_addr(chatList[a].IP);
	
					//커넥션을 한다. 실패할 경우 에러 출력.
					if (connect(sockList[b], (struct sockaddr *)&inviteUser, sizeof (inviteUser)) < 0) {
						(void) close(sockList[b]);
						sockList[b]=-1;
						perror("connect error for chatting room.");
						exit(1);
					}
					//커넥션 성공한 경우 리퀘스트 메시지 입력
					requestForUser(sockList[b], myId, "MUST", chatList, "");
					//sockList select처리 필요
					//respons처리함수 나중에 넣을것
					readUserResponse(sockList[b]);
					FD_SET(sockList[b], &(*myMask));
					if((*fd_max) < sockList[b])
						(*fd_max) = sockList[b];
				}
			}
			if(*isOnChat == 0)
				chatDis(myId);
			*isOnChat = 1;
			//////////////////////////////////////////////////////////////////////////////////////////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			int z;
			char chatMs[MAX] = {};
			sprintf(chatMs, "*%s join in chatting room.\n",myId);
			for(z=0; z<MAXUSER; z++)
			{
				if(sockList[z]>=0)
				{
					//printf("what??%d\n",a);
					//fflush(stdout);
					requestForUser(sockList[z], myId, "CHAT", chatList, chatMs);
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////////>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		}
	//strcmp(myID,requestId);
	//printf("%s\n",totalBody);//
	//fflush(stdout);//
	return 1;
	}
	else if(!strcmp(reqHeader,"MUST"))
	{
		responseForUser(sock, "OK", "");
		if(isOnChat == 0)
				chatDis(myId);
		*isOnChat = 1;
		return 1;
	}
	else if(!strcmp(reqHeader,"CHAT"))
	{
		printf("%s\n",totalBody);
		fflush(stdout);
		//outputLine(myId);
		return 1;
	}
	else
	{
		perror("Unknown Header Error.\n");

		FD_CLR(sock , myMask);

		if (close(sock))
		{
			perror("close socket");
			exit(1);
		}
		exit(1);
		return 0;
	}
}

//뭔가 실패시 0 반환
int readUserResponse(int sock)
{
	int bytesread;
	int totalLen=0;
	char format[msSize+1] = {};
	char totalBody[MAX] = {};
	//printf("wait response\n",format);///////////////////////////////////////////////////////
	bytesread = read(sock, format, sizeof(format) - 1);

	format[bytesread] = '\0';
	//printf("%s",format);///////////////////////////////////////////////////////
	//printf("%s",format);
	//fflush(stdout);
	if(bytesread<=0)
	{
		printf("Other user has quited or Network error.\n");
		fflush(stdout);

		if (close(sock))
		{
			perror("close socket");
			//exit(1);
		}
		exit(1);
	}
	//format[bytesread] = '\0';
	//strtok 관련 함수로 메시지를 어케 분류할건지... 헤더와 바디를 어케 구분할것이며... 커서처럼 움직일 수 있는 함수 없나?
	char* headerLine[MAXHEADER] = {};
	char* nextLine = 0;
	char* bodyLine = 0;
	char* resVersion = 0;
	int a, b, headerNum, isBody = 0;
	//char* otherUserID = NULL;

	char* resHeader = 0;
	//int isOK = 0;

	//printf("%s\n",format);
	headerLine[0] = strtok(format, "\n");
	
	for(a=1; a<MAXHEADER; a++)
	{
		if(!strcmp((nextLine = strtok(NULL, "\n")),"\r"))
		{
			headerNum = a;
			bodyLine = strtok(NULL, "\n");
			//bodyLine = strtok(NULL, "\r");
			//printf("%s",bodyLine);
			fflush(stdout);
			if(bodyLine!=NULL)
			{
				isBody = 1;
				strtok(NULL,"\r\n");
			}
			break;
		}
		else
		{
			headerLine[a] = nextLine;
			//strtok(NULL,"\r");
			//printf("%s\n",headerLine[1]);//
			//fflush(stdout);
		}
	}//헤더와 바디 분류

	//맨 처음 헤더(1.0 OK...) : 응답헤더
	resVersion = strtok(headerLine[0], " ");
	resHeader = strtok(NULL, " \r");
	//printf("resHeader: %s\n",resHeader);
	//fflush(stdout);
	if(!strcmp(resHeader,"OK"))
	{
		return 1;
	}
	else if(!strcmp(resHeader,"ERROR"))
	{
		printf("Error : %s\n", bodyLine);
		printf("\nInsert anyKey to continue.\n");
		fflush(stdout);
		getchar();
		fflush(stdin);
		return 0;
	}
	else
	{
		perror("Unknown Header Error.\n");
		exit(1);
		return 0;
	}
}

void StringToInfo(struct INFO* info,char string[]){
	char* user[MAXUSER] = {};
	int a;
	int userNum = 0;
	
	for(a=0; a<MAXUSER; a++)
	{
		strcpy(info[a].ID,"");
	}

	user[0] = strtok(string," \r");
	//printf("%s",user[0]);
	if(user[0])
	{
		userNum = 1;
		for(a=1; a<MAXUSER+1; a++)//	ID/IP/PORT ID/IP/PORT ...\r
		{
			if((user[a] = strtok(NULL, " \r"))==NULL)
			{
				userNum = a;
				break;
			}
		}
	}
	//printf("%s",user[0]);
	//printf("%d",userNum);
	//printf("%s\n",(*info)[0].ID);
	fflush(stdout);
	for(a=0; a<userNum; a++)
	{
		strcpy(info[a].ID, strtok(user[a],"/"));
		//printf("%s",info[a].ID);
		//fflush(stdout);
		strcpy(info[a].IP, strtok(NULL,"/"));
		//printf("zz");
		//fflush(stdout);
		info[a].PORT = atoi(strtok(NULL,"/"));
		//printf("asd");
		//fflush(stdout);
	}
}


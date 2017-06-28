#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>

#define MAX 512

struct INFO{
	char ID[10];
	char IP[16]; // c_addr.sin_addr.s_addr;
	int PORT;
}INFO;

int numClient=-1; // 현재 접속자 수
int clientSock[30]; // 최대 접속자 수 
char quit[] = "quit";
int getMaxfd(int);

int  defaultPort = 5556;
char error[255] = "404 NOT FOUND"; // 에러 메세지

int main(int argc, char *argv[ ] )
{
	struct INFO info[30];
	struct hostent *hostp; // 도메인 -> IP변환
	int listenSock, sendSock;
	struct sockaddr_in s_addr, c_addr, send_addr;
	int len, i, n; // 인덱스 변수
	int j, k;
	char rcvBuffer[BUFSIZ], sbuf[BUFSIZ], tempBuffer[BUFSIZ];
	char* ptr = NULL; // 토큰을 위한 변수
	char* ptr2 = NULL; // 토큰을 위한 변수2
	char temp[1024]; // ID , IP , PORT복사를 위한 것
	char temp2[1024]; // ID IP PORT를 합치기 위해 필요한 것
	char* temp3; // 임시 IP저장
	int content_length=0; // 보내는 body 크기
	int maxfd;

	fd_set read_fds;   // 셋트

	//printf("StudentID : 20123417\nName : 조성룡\n");

	//display();
	fflush(stdout);
	fflush(stdout);
	 
	defaultPort = atoi(argv[1]);
	fflush(stdin);

	listenSock = socket(PF_INET, SOCK_STREAM, 0);  // 소켓 개설

	memset(&s_addr, 0, sizeof(s_addr));   // 초기화
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_port = htons(defaultPort);

	if(bind(listenSock, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) 
	{
		printf("Can not Bind\n");
		return -1;
	}  //  포트 바인드 실패 시 종료
		
	if(listen(listenSock, 5) == -1)
	{
		printf("listen Fail\n");
		return -1;
	}  //  타임 오버시 종료

	while(1) 
	{
		maxfd = getMaxfd(listenSock) + 1;
		FD_ZERO(&read_fds); // 초기화
		FD_SET(listenSock, &read_fds);  // 연결 전용 소켓 세트
		FD_SET(0, &read_fds);       // 키보드 입력 소켓 세트

		for(i = 0; i < numClient+1; i++)  // 연결 된 소켓 수 만큼 세트
			FD_SET(clientSock[i], &read_fds);
		printf("===============LIST===============\n");
		for(i = 0; i< numClient+1; i++)
		{
			printf("%s / %s \n" , info[i].ID , info[i].IP);
		}
		printf("==================================\n\n");

		if(select(maxfd, &read_fds, NULL, NULL, NULL) < 0 ) 
		{
			printf("select error\n");
			exit(-1);
		}

		if(FD_ISSET(0, &read_fds)) // 만약 키보드 입력이 들어오면
		{
			// quit으로 서버종료
			if((n = read(0, sbuf, BUFSIZ)) > 0)
				if(strncmp(sbuf, quit, 4) == 0) // @quit 명령어
				{
					printf("Exit server.\n");
					break;
				}
		}

		if(FD_ISSET(listenSock, &read_fds)) // 소켓 요청이 들어오면
		{
			sendSock=accept(listenSock, (struct sockaddr *) &c_addr, &len);
			numClient++;
			clientSock[numClient] = sendSock;

			fflush(stdout);
			fflush(stdin);
			// 테스트용이므로 일단 주석처리
			// 여기에는 login id시에 id중복체크 및 id 리스트를 보내면 됨
			if((n=read(clientSock[numClient], rcvBuffer, sizeof(rcvBuffer)))>0) // request message 받음(login ID)
			{
				strcpy(tempBuffer , rcvBuffer);
				ptr = strtok(tempBuffer , "\r\n");
				if(strcmp(ptr , "login 1.0"))
				{
					ptr = strtok(NULL , "\r\n"); // ID: hoot
					ptr2 = strtok(ptr , " "); // ID: 
					ptr2 = strtok(NULL , " "); // hoot
					if(numClient == 0) // 첫 사용자
					{
							strcpy(info[numClient].ID , ptr2); // ID를 list에 넣는다.
							info[numClient].PORT = c_addr.sin_port; // PORT를 넣는다.
							temp3 = inet_ntoa(c_addr.sin_addr.s_addr); // IP를 넣는다. 바로 못넣기 때문에 매게체를 거쳐 넣는다.
							for(j=0 ; j<16; j++)
							{
								if(temp3[j] != NULL)
									info[numClient].IP[j] = temp3[j];
								else{
									info[numClient].IP[j] = NULL;
									break;
								}
							}
							//strcpy(info[numClient].IP , inet_ntoa(c_addr.sin_addr.s_addr));
							//sprintf(info[numClient].IP , "%s" , inet_ntoa(c_addr.sin_addr.s_addr));
							/*temp3 = inet_ntoa(c_addr.sin_addr.s_addr);
							strcpy(info[numClient].IP , temp3);
							//info[numClient].IP = inet_ntoa(c_addr.sin_addr.s_addr); // IP 저장, 다시 네트워크 주소로의 반환은
																					// inet_addr*/
							
							// list를 보내는 부분 //
							//strcpy(temp, "1.0 OK\r\nContent-Lenth: 64\r\n\r\n");
							for(i=0; i<numClient+1; i++)
							{
								sprintf(temp , "%s/%s/%d " , info[i].ID , info[i].IP , info[i].PORT);
							}
							content_length = strlen(temp);
							sprintf(sbuf, "1.0 OK\r\nContent-Length: %d\r\n\r\n%s\r\n\r\n", content_length, temp);
							write(clientSock[numClient], sbuf, sizeof(sbuf));
							FD_SET(clientSock[numClient] , &read_fds);
							system("clear");
							printf("Login message\n");
							printf("%s\n" , sbuf);
							
					}

					else if(numClient > 0)
					{
						for(i=0; i<numClient+1; i++) // ID중복여부 체크
						{
							// printf("%s\n" , ptr2); 디버깅용
							if(!(strcmp(info[i].ID , ptr2))) // 중복이면
							{
								sprintf(sbuf, "1.0 ERROR\r\nContent-Length: 0\r\n\r\nID overlap.\r\n\r\n");
								write(clientSock[numClient], sbuf, sizeof(sbuf));
								system("clear");
								printf("Error message\n");
								printf("%s\n" , sbuf);
								close(clientSock[numClient]); // 연결종료
								/*if(i != numClient-1)
									clientSock[i] = clientSock[numClient-1];*/
								numClient--;
								//printf("Connection Closed %d.\n" , c_addr.sin_port);
								// 나감 처리
								break;
							}
						}

						// 중복이 아니면
						strcpy(info[numClient].ID , ptr2); // ID를 list에 넣는다.
						info[numClient].PORT = c_addr.sin_port; // PORT를 넣는다.
						temp3 = inet_ntoa(c_addr.sin_addr.s_addr); // IP를 넣는다. 바로 못넣기 때문에 매게체를 거쳐 넣는다.
						for(j=0 ; j<16; j++) 
						{
							if(temp3[j] != NULL)
								info[numClient].IP[j] = temp3[j];
							else
							{
								info[numClient].IP[j] = NULL;
								break;
							}
						}
						//sprintf(info[numClient].IP , "%s" , inet_ntoa(c_addr.sin_addr.s_addr));
						//info[numClient].IP = inet_ntoa(c_addr.sin_addr.s_addr); // IP 저장, 다시 네트워크 주소로의 반환은
																						// inet_addr
						// list를 보내는 부분 //
						//strcpy(temp, "1.0 OK\r\nContent-Lenth: 64\r\n\r\n");
						for(i=0; i<numClient+1; i++)
						{
							sprintf(temp , "%s/%s/%d " , info[i].ID , info[i].IP , info[i].PORT);
							strcat(temp2 , temp);
						}
						content_length = strlen(temp2);
						fflush(stdout);
						fflush(stdin);
						sprintf(sbuf, "1.0 OK\r\nContent-Length: %d\r\n\r\n%s\r\n\r\n", content_length, temp2);
						write(clientSock[numClient], sbuf, sizeof(sbuf));
						FD_SET(clientSock[numClient] , &read_fds);
						printf("Login message\n");
						printf("%s\n" , sbuf);
					}
					for(i=0; i<1024; i++)
					{
						temp[i] = 0;
						temp2[i] = 0;
					}
					//printf("%s\n" , sbuf);
				}
					
				else // 연결 종료(login request 이상하게 받으면)
				{
					//login 실패시 메세지//
					//printf("Connection Closed from host %s, port %d, socket %d.\n",defaultIP, c_addr.sin_port, clientSock[i]);
					sprintf(sbuf, "1.0 ERROR\r\nContent-Length: 0\r\n\r\nlogin fail.\r\n\r\n");
					write(clientSock[numClient], sbuf, sizeof(sbuf));
					system("clear");
					printf("Error message\n");
					printf("%s\n" , sbuf);
					close(clientSock[numClient]);
					numClient--;
					/*if(i != numClient) // 끝의 내용을 중간으로 당겨옴
					{
						clientSock[i] = clientSock[numClient];
						strcpy(info[i].ID , info[numClient].ID);
						info[i].PORT = info[numClient].PORT;
						strcpy(info[i].IP , info[numClient].IP);
						numClient--;
					}
					else
					{
						clientSock[i] = -1;
						strcpy(info[i].ID , "");
						info[i].PORT = 0;
						strcpy(info[i].IP , "");
						numClient--;
					}
					close(clientSock[numClient+1]);
					printf("here2\n");*/
				}
			}

			// 연결 성공 시 접속 자 증가
		}

		// 갱신 메세지 즉, userlist가 들어오면~ //
		else 
		{
			for(i = 0; i < numClient+1; i++) 
			{
				if(FD_ISSET(clientSock[i], &read_fds)) // 메세지 요청이 들어오면
				{
					if((n=read(clientSock[i], rcvBuffer, sizeof(rcvBuffer)))>0)
					{
						//여기에 ID 리스트 보내면 됨 , 갱신 메세지가 왔을 때
						strcpy(tempBuffer , rcvBuffer);
						ptr = strtok(tempBuffer , "\r\n");
						if(strcmp(ptr , "renew 1.0"))
						{
							for(k=0; k<numClient+1; k++)
							{
								sprintf(temp , "%s/%s/%d " , info[k].ID , info[k].IP , info[k].PORT);
								strcat(temp2 , temp);
							}
							content_length = strlen(temp2);
							sprintf(sbuf, "1.0 OK\r\nContent-Length: %d\r\n\r\n%s\r\n\r\n", content_length, temp2);
							write(clientSock[i], sbuf, sizeof(sbuf));
							system("clear");
							printf("Renew message\n");
							printf("%s\n" , sbuf);
						}

						for(i=0; i<1024; i++) // 버퍼 초기화
						{
							temp[i] = 0;
							temp2[i] = 0;
						}
					}

					else 
					{
						//연결이 끊기면//
						//printf("Connection Closed from host %s, port %d, socket %d.\n",defaultIP, c_addr.sin_port, clientSock[i]);
						/*sprintf(sbuf, "1.0 ERROR\r\nContent-Lenth: 0\r\n\r\nlogin fail.\r\n\r\n");
						write(clientSock[numClient], sbuf, sizeof(sbuf));*/ //연결이 끊어졌으니 메세지를 보낼 필요가 없음
						if(i != numClient) // 끝의 내용을 중간으로 당겨옴
						{
							close(clientSock[i]);
							clientSock[i] = clientSock[numClient];
							FD_CLR(clientSock[numClient] , &read_fds); // 소켓이동에 따른 FD 변경
							strcpy(info[i].ID , info[numClient].ID);
							info[i].PORT = info[numClient].PORT;
							strcpy(info[i].IP , info[numClient].IP);
							numClient--;
						}
						else if(i == numClient)
						{
							close(clientSock[i]);
							FD_CLR(clientSock[i] , &read_fds); // 소켓이동에 따른 FD 변경
							clientSock[i] = -1;
							strcpy(info[i].ID , "");
							info[i].PORT = 0;
							strcpy(info[i].IP , "");
							numClient--;
						}

						fflush(stdout);
					}
				}
			}
		}
	// while end
	}

	return 0;
} // main end

int getMaxfd(int n)
{
	int max = n;
	int i;
	for(i = 0; i < numClient+1; i++) 
	{
		 if(clientSock[i] > max)
			 max = clientSock[i];
	}

	return max;
}

int display() 
{
	printf("Hi. Welcome to Login Server. \n");
	return 0;
}
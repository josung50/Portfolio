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

int numClient=-1; // ���� ������ ��
int clientSock[30]; // �ִ� ������ �� 
char quit[] = "quit";
int getMaxfd(int);

int  defaultPort = 5556;
char error[255] = "404 NOT FOUND"; // ���� �޼���

int main(int argc, char *argv[ ] )
{
	struct INFO info[30];
	struct hostent *hostp; // ������ -> IP��ȯ
	int listenSock, sendSock;
	struct sockaddr_in s_addr, c_addr, send_addr;
	int len, i, n; // �ε��� ����
	int j, k;
	char rcvBuffer[BUFSIZ], sbuf[BUFSIZ], tempBuffer[BUFSIZ];
	char* ptr = NULL; // ��ū�� ���� ����
	char* ptr2 = NULL; // ��ū�� ���� ����2
	char temp[1024]; // ID , IP , PORT���縦 ���� ��
	char temp2[1024]; // ID IP PORT�� ��ġ�� ���� �ʿ��� ��
	char* temp3; // �ӽ� IP����
	int content_length=0; // ������ body ũ��
	int maxfd;

	fd_set read_fds;   // ��Ʈ

	//printf("StudentID : 20123417\nName : ������\n");

	//display();
	fflush(stdout);
	fflush(stdout);
	 
	defaultPort = atoi(argv[1]);
	fflush(stdin);

	listenSock = socket(PF_INET, SOCK_STREAM, 0);  // ���� ����

	memset(&s_addr, 0, sizeof(s_addr));   // �ʱ�ȭ
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_port = htons(defaultPort);

	if(bind(listenSock, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) 
	{
		printf("Can not Bind\n");
		return -1;
	}  //  ��Ʈ ���ε� ���� �� ����
		
	if(listen(listenSock, 5) == -1)
	{
		printf("listen Fail\n");
		return -1;
	}  //  Ÿ�� ������ ����

	while(1) 
	{
		maxfd = getMaxfd(listenSock) + 1;
		FD_ZERO(&read_fds); // �ʱ�ȭ
		FD_SET(listenSock, &read_fds);  // ���� ���� ���� ��Ʈ
		FD_SET(0, &read_fds);       // Ű���� �Է� ���� ��Ʈ

		for(i = 0; i < numClient+1; i++)  // ���� �� ���� �� ��ŭ ��Ʈ
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

		if(FD_ISSET(0, &read_fds)) // ���� Ű���� �Է��� ������
		{
			// quit���� ��������
			if((n = read(0, sbuf, BUFSIZ)) > 0)
				if(strncmp(sbuf, quit, 4) == 0) // @quit ��ɾ�
				{
					printf("Exit server.\n");
					break;
				}
		}

		if(FD_ISSET(listenSock, &read_fds)) // ���� ��û�� ������
		{
			sendSock=accept(listenSock, (struct sockaddr *) &c_addr, &len);
			numClient++;
			clientSock[numClient] = sendSock;

			fflush(stdout);
			fflush(stdin);
			// �׽�Ʈ���̹Ƿ� �ϴ� �ּ�ó��
			// ���⿡�� login id�ÿ� id�ߺ�üũ �� id ����Ʈ�� ������ ��
			if((n=read(clientSock[numClient], rcvBuffer, sizeof(rcvBuffer)))>0) // request message ����(login ID)
			{
				strcpy(tempBuffer , rcvBuffer);
				ptr = strtok(tempBuffer , "\r\n");
				if(strcmp(ptr , "login 1.0"))
				{
					ptr = strtok(NULL , "\r\n"); // ID: hoot
					ptr2 = strtok(ptr , " "); // ID: 
					ptr2 = strtok(NULL , " "); // hoot
					if(numClient == 0) // ù �����
					{
							strcpy(info[numClient].ID , ptr2); // ID�� list�� �ִ´�.
							info[numClient].PORT = c_addr.sin_port; // PORT�� �ִ´�.
							temp3 = inet_ntoa(c_addr.sin_addr.s_addr); // IP�� �ִ´�. �ٷ� ���ֱ� ������ �Ű�ü�� ���� �ִ´�.
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
							//info[numClient].IP = inet_ntoa(c_addr.sin_addr.s_addr); // IP ����, �ٽ� ��Ʈ��ũ �ּҷ��� ��ȯ��
																					// inet_addr*/
							
							// list�� ������ �κ� //
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
						for(i=0; i<numClient+1; i++) // ID�ߺ����� üũ
						{
							// printf("%s\n" , ptr2); ������
							if(!(strcmp(info[i].ID , ptr2))) // �ߺ��̸�
							{
								sprintf(sbuf, "1.0 ERROR\r\nContent-Length: 0\r\n\r\nID overlap.\r\n\r\n");
								write(clientSock[numClient], sbuf, sizeof(sbuf));
								system("clear");
								printf("Error message\n");
								printf("%s\n" , sbuf);
								close(clientSock[numClient]); // ��������
								/*if(i != numClient-1)
									clientSock[i] = clientSock[numClient-1];*/
								numClient--;
								//printf("Connection Closed %d.\n" , c_addr.sin_port);
								// ���� ó��
								break;
							}
						}

						// �ߺ��� �ƴϸ�
						strcpy(info[numClient].ID , ptr2); // ID�� list�� �ִ´�.
						info[numClient].PORT = c_addr.sin_port; // PORT�� �ִ´�.
						temp3 = inet_ntoa(c_addr.sin_addr.s_addr); // IP�� �ִ´�. �ٷ� ���ֱ� ������ �Ű�ü�� ���� �ִ´�.
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
						//info[numClient].IP = inet_ntoa(c_addr.sin_addr.s_addr); // IP ����, �ٽ� ��Ʈ��ũ �ּҷ��� ��ȯ��
																						// inet_addr
						// list�� ������ �κ� //
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
					
				else // ���� ����(login request �̻��ϰ� ������)
				{
					//login ���н� �޼���//
					//printf("Connection Closed from host %s, port %d, socket %d.\n",defaultIP, c_addr.sin_port, clientSock[i]);
					sprintf(sbuf, "1.0 ERROR\r\nContent-Length: 0\r\n\r\nlogin fail.\r\n\r\n");
					write(clientSock[numClient], sbuf, sizeof(sbuf));
					system("clear");
					printf("Error message\n");
					printf("%s\n" , sbuf);
					close(clientSock[numClient]);
					numClient--;
					/*if(i != numClient) // ���� ������ �߰����� ��ܿ�
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

			// ���� ���� �� ���� �� ����
		}

		// ���� �޼��� ��, userlist�� ������~ //
		else 
		{
			for(i = 0; i < numClient+1; i++) 
			{
				if(FD_ISSET(clientSock[i], &read_fds)) // �޼��� ��û�� ������
				{
					if((n=read(clientSock[i], rcvBuffer, sizeof(rcvBuffer)))>0)
					{
						//���⿡ ID ����Ʈ ������ �� , ���� �޼����� ���� ��
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

						for(i=0; i<1024; i++) // ���� �ʱ�ȭ
						{
							temp[i] = 0;
							temp2[i] = 0;
						}
					}

					else 
					{
						//������ �����//
						//printf("Connection Closed from host %s, port %d, socket %d.\n",defaultIP, c_addr.sin_port, clientSock[i]);
						/*sprintf(sbuf, "1.0 ERROR\r\nContent-Lenth: 0\r\n\r\nlogin fail.\r\n\r\n");
						write(clientSock[numClient], sbuf, sizeof(sbuf));*/ //������ ���������� �޼����� ���� �ʿ䰡 ����
						if(i != numClient) // ���� ������ �߰����� ��ܿ�
						{
							close(clientSock[i]);
							clientSock[i] = clientSock[numClient];
							FD_CLR(clientSock[numClient] , &read_fds); // �����̵��� ���� FD ����
							strcpy(info[i].ID , info[numClient].ID);
							info[i].PORT = info[numClient].PORT;
							strcpy(info[i].IP , info[numClient].IP);
							numClient--;
						}
						else if(i == numClient)
						{
							close(clientSock[i]);
							FD_CLR(clientSock[i] , &read_fds); // �����̵��� ���� FD ����
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
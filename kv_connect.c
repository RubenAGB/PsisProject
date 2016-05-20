#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <arpa/inet.h>
#include <signal.h>

/*Um comentáriozinho para ver no que dá*/asdasdasda
int kv_connect(char * kv_server_ip, int kv_server_port)
{	
	int fd;
	struct sockaddr_in addr;
	struct in_addr *a;
					//IPv4		//TCP
	if((fd = socket(AF_INET, SOCK_STREAM,0)) < 0)
		return -1;

	a = (struct in_addr*) kv_server_ip;
	inet_aton(kv_server_ip, a);

	memset((void*)&addr, (int) '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr = *a;
	addr.sin_port = htons(kv_server_port);

	if(connect(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
		return -1;

	return fd;
}

void kv_close(int kv_descriptor)
{
	close(kv_descriptor);
	return;
}

int main (void)
{
	int fd;
	struct in_addr *a;
	struct hostent *h;

	if((h = gethostbyname("miguels-macbook-pro.local")) == NULL )//Aqui depois temos de mudar para ser possível em qualquer máquina
		exit(1);

	//Boy, este main serviu apenas para testar as funçoes que fiz... Por isso a cena do gethostbyname não precisas de alterar, so tens de dar o ip que queres à funcção, apenas pus isso para testar...

	a = (struct in_addr*)h->h_addr;
	printf("Host name:\t%s\nHost IP:\t%s\n", h->h_name, inet_ntoa(*a));

					//IP 		 //port
	if ((fd = kv_connect(inet_ntoa(*a), 9000)) < 0) //Falta a string de erro também
		exit(-1);

	kv_close(fd);
	
	exit(1);//Acrescentei só isto para tirar o warning de não retornar inteiro - okok
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 50200
#define BUFF_SIZE 1024

int main(void){
	int sock;
	struct sockaddr_in serv_addr;
	char buffer[BUFF_SIZE] = {0};
	char message[BUFF_SIZE];
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0){
		perror("Ошибка socket");
		exit(EXIT_FAILURE);
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	int result = inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
	if (result == 0){
		printf("\nНеверный формат IP-адреса\n");
		close(sock);
		exit(EXIT_FAILURE);
	} else if (result < 0){
		perror("\nОшибка inet_pton\n");
		close(sock);
		exit(EXIT_FAILURE);
	}
	
	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)){
		perror("\nОшибка connect\n");
		close(sock);
		exit(EXIT_FAILURE);
	}
	printf("\nПодключение к серверу завершено успешно\n");

return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 50200

int main(void){
	int server_fd;
	struct sockaddr_in address;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0) {
		perror("Ошибка создания сокета");
		exit(EXIT_FAILURE);
	}
	
	memset(&address, 0, sizeof(address));				//очистка структуры адреса от мусора в памяти
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;						
	address.sin_port = htons(PORT);
	
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("Ошибка bind");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Сокет успешно создан и привязан к порту %d!\n", PORT);
	
	if (listen(server_fd, 3) < 0) {
		perror("Ошибка listen");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Сервер успешно запущен. Ожидание подключений на порту %d...\n", PORT);
	
	int new_socket;
    	int addrlen = sizeof(address);

    	new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    	if (new_socket < 0) {
		perror("Ошибка accept");
		close(server_fd);
		exit(EXIT_FAILURE);
    	}
    	printf("Клиент успешно подключился.\n");
	
    	char buffer[1024];
    	
    	while (1) {
		memset(buffer, 0, sizeof(buffer));
		int bytes_read = read(new_socket, buffer, sizeof(buffer));
		
		if (bytes_read == 0) {
    			printf("Клиент отключился\n");
    			break;
		} else if (bytes_read < 0) {
    			perror("Ошибка чтения из сокета"); 
			break;
		}
		
		printf("Клиент прислал: %s", buffer);
		send(new_socket, buffer, strlen(buffer), 0);
    	}
    	
    	close(new_socket);
    	close(server_fd);
    	
	return 0;
}

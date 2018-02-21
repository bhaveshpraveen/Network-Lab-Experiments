# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <string.h>
# include <stdlib.h>


int main(){
	int udpSocket, nBytes;
	char buffer[1024];
	struct sockaddr_in serverAddr, clientAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size, client_addr_size;
	int i;

	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(6666);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

	bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	addr_size = sizeof(serverStorage);

	while(1){
		nBytes = recvfrom(udpSocket, buffer, 1024, 0, (struct sockaddr *) &serverStorage, &addr_size);
		printf("Client: %s\n", buffer);
		printf("Server: ");
		fgets(buffer, 1024, stdin);
		sendto(udpSocket, buffer, nBytes, 0, (struct sockaddr *) &serverStorage, addr_size);
	}
	return 0;


}

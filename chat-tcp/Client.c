/*
arg[0] = filename
arg[1] = ipaddress
arg[2] = portno
 */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h> // used for read, write operations
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h> // describes the hostent structure, used to store information about the host(hostname, protocols, etc)


void error(char *msg){
	perror(msg);
	exit(1);
}


int main(int argc, char *argv[]){
	if(argc < 3){
		fprintf(stderr,  "Ip Address and Host name are needed.\n");
		exit(1);
	}
	int sockfd, newsockfd, portno, n;
	char buffer[255];

	struct sockaddr_in serv_addr;
	struct hostent *server;
	socklen_t clilen;

	portno = atoi(argv[2]);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){ 
		error("Error opening socket.\n");
	}

	server = gethostbyname(argv[1]);
	if(server == NULL){
		fprintf(stderr, "No such host\n");
		exit(1);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server -> h_addr, (char *) &serv_addr.sin_addr.s_addr, server -> h_length); // transferring data from (*server).h_addr to serv_addr.sin_addr.s_addr
	serv_addr.sin_port = htons(portno);

	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		error("Error in Connect.\n");
	}

	while(1){
		bzero(buffer, 255);
		fgets(buffer, 255, stdin);
		n = write(sockfd, buffer, sizeof(buffer));

		if(n < 0)
			error("Error in Write.\n");

		bzero(buffer, 255);
		n = read(sockfd, buffer, 255);

		if(n < 0)
			error("Error in Read.\n");

		printf("Server: %s\n", buffer);
		
		
	}
	close(sockfd);
	return 0;

}


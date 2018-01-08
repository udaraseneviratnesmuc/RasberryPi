#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void dostuff(int sock);

void error(char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char const *argv[])
{
	int sockfd, newsockfd, portno, clilen, pid;
	struct sockaddr_in serv_addr, cli_addr;

	if (argc < 2)
	{
		fprintf(stderr, "Error ! No port provided\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd  < 0)
	{
		error("ERROR opening socket");
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		error("Error ! on binding");
	}

	listen(sockfd, 5);

	clilen = sizeof(cli_addr);

	while(1)
	{
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0)
		{
			error("ERROR on Accept");
		}

		pid = fork();

		if (pid < 0)
		{
			error("Error on forking");
		}

		if (pid == 0)
		{
			close(sockfd);
			dostuff(newsockfd);
			exit(0);
		}else{
			close(newsockfd);
		}
	}

	return 0;
}


void dostuff(int sock)
{
	char buffer[256];
	int n;

	bzero(buffer, 256);
	n = read(sock, buffer, 255);

	if (n < 0)
	{
		error("ERROR ! Reading from socket");
	}

	printf("Here is the message : %s\n", buffer);

	n = write(sock, "I got your message", 18);

	if (n < 0)
	{
		error("ERROR writing to socket");
	}
}


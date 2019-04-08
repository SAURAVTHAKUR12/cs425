#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


int main(int argc, char *argv[]){
  int clientSocket,i;
  char buffer[1024], filename[50];
  char *usr,*pass,*sname;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  usr=strtok(argv[1]," :");
  pass=strtok(NULL," @");
  sname=strtok(NULL," ");
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7893);
  serverAddr.sin_addr.s_addr = inet_addr(sname);
  
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
  //interaction between server and client test 1
  send(clientSocket,usr,sizeof(usr),0);
  bzero(buffer,1024);
  recv(clientSocket,buffer,1024,0);
  if (strcmp(buffer,"yes")==0)
  {  
  send(clientSocket,pass,sizeof(pass),0);
  bzero(buffer,1024);
  recv(clientSocket,buffer,1024,0);
  
  if (strcmp(buffer,"1")==0)
  {
   printf("hello %s\n",usr);
  }
  else
    {printf("Authentication failure!!!\n");
  return;}
  }
  printf("Enter the file to be downloaded\n");
  scanf("%s",filename);
  send(clientSocket,filename,50,0);
  bzero(buffer,1024);
  recv(clientSocket,buffer,1024,0);
  if(strcmp(buffer,"0")==0)
    printf("file not found\n");
  else if (strcmp(buffer,"1")==0)
  {
    printf("Downloading the file\n");
    FILE *fp;
    fp = fopen(filename, "ab");
    int bytesReceived = 0;
    bzero(buffer,1024);
    while((bytesReceived = recv(clientSocket, buffer,1024,0)) > 0)
    {
           
        fwrite(buffer, 1,bytesReceived,fp);
    }
    fclose(fp);
  }



  
  return 0;
}

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include<stdlib.h>

int main(){
  int welcomeSocket, newSocket,nread;
  char buffer[1024];
  char *usr,*pass,*fname,*fpass,*fusr;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
 
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7893);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  char b2[100];
  bzero(b2,100);
  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");
  addr_size = sizeof serverStorage;
  bzero(buffer,1024);
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
  recv(newSocket,buffer,1024,0);
  usr=buffer;
  send(newSocket,"yes",3,0);
  recv(newSocket,b2,100,0);
  pass=b2;
  int verify=0;
	FILE *fp;
       char filename[]="users.txt",line[200],search_string[]="12";
       fp=fopen(filename,"r");
        if(!fp)
        {
                perror("could not find the file");
                printf("could not find the file\n");
                exit(0);
        }
        while ( fgets ( line, 200, fp ) != NULL ) /* read a line */
        {
                fusr=strtok(line," ");          
                fpass=strtok(NULL," \n");
                if((strcmp(fusr,usr)==0)&&(strcmp(fpass,pass)==0))
                  verify=1;
        }
        fclose ( fp );
        if (verify==1)
        {send(newSocket,"1",1,0);
        }
        else
        send(newSocket,"0",1,0);
      bzero(buffer,1024);
      recv(newSocket,buffer,1024,0);
      FILE *fq;
      fq=fopen(buffer,"r");
      if(!fq)
      {
        send(newSocket,"0",1,0);
      }
      else
      { send(newSocket,"1",1,0); 
       while(1)
        {
            
            bzero(buffer,1024);
            int nread = fread(buffer,1,1024,fp);
                    

            
            if(nread > 0)
            {
                write(newSocket, buffer, nread);
            }

            if (nread < 1024)
            break;


        }
      }

  return 0;
}

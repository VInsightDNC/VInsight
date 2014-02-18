/*--------------------------------------------------------------------------------
* Copyright(c) 2013-2014. 
* Dependable Networking and Computing (DNC) Lab in Wayne State University. 
* All rights reserved.
*---------------------------------------------------------------------------------
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
* 
* 1. Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice, 
* this list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* 3. Neither the name of the DNC lab nor the names of its contributors may be used 
* to endorse or promote products derived from this software without specific prior 
* written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
* SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*--------------------------------------------------------------------------------
* Dependable Networking and Computing Lab
* Wayne State University
* Email: vinsight.dnc@gmail.com
*--------------------------------------------------------------------------------
* Name: server_side.c
* Function: allocate the experiment to the mobile platforms and also collect the experiment results
* Author: Yuehua Wang 
* Email: yuehua.research@gmail.com
*/

#include "config.h"

int main(int argc,char **argv)
{ 
  
  int server_sockfd,client_sockfd;
  int server_len;
//  int count=0;
  socklen_t client_len;
  char buffer[MAXSIZE];
  char filepath[50];
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;  
//  int count=0;
  bool flag = false;
  FILE *fp;

  //open file 



  while(1)
  {
 // sleep(1); 
  memset(filepath,'\0',sizeof(filepath));
  strcpy(filepath,FILEPATH_Sensing);

  fp = fopen(filepath,"a+b");

  if(fp == NULL)
  {
    perror("create the file error!\n");
    printf(" filepath:%s ",filepath);
    close(server_sockfd);
    exit(1);
  }
  fseek(fp,0,SEEK_END);
  
  server_sockfd = socket(AF_INET,SOCK_STREAM,0);

  if(server_sockfd <0)
  {
    perror("Creating socket error!\n");
    exit(1);
  }

  bzero(&server_address,sizeof(struct sockaddr_in));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(SERVPORT);
  server_len = sizeof(server_address);

  int opt = 1;
  setsockopt(server_sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));  
  
  if(bind(server_sockfd,(struct sockaddr *)&server_address,server_len) < 0)
  {
    perror("Bind error.");
    exit(1);
  } else
     printf("bind successful!\n");

  if(listen(server_sockfd,5) == -1)
  {
    printf("listen error!\n");
    exit(1);
  }

  client_len = sizeof(client_address);

  while(1)
  {
  // sleep(1);
  printf("server is waiting for connnection\n");

  if(flag == false)
  {
  client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);
  if(client_sockfd == -1)
  {
    printf("accept error!\n");
    close(client_sockfd);
    continue;
  }else
    flag= true;
   printf("connected!\n");
  }

//  count =0;
 
  while(1)
  {
     int totalcnt=0;
     int low;
  // sleep(1); 
     if(flag == false)
       break;

     while(totalcnt < MAXSIZE)
     {

      if(flag == false)
      break;
      
     // sleep(1);

      low=read(client_sockfd,&buffer[totalcnt],(MAXSIZE-totalcnt));
 
      struct sigaction action;
  
      sighandler_t hand;
       
     // printf("low: %d\n ",low);
  
      hand = signal(SIGPIPE, handler);
   
      if(hand  == SIG_ERR)
      {
          action.sa_handler =SIG_IGN;
          sigaction(SIGPIPE,&action,0); 
          printf("trying to reconnect1\n");       
          flag = false;
          fclose(fp);
          close(server_sockfd);
          close(client_sockfd);
          // msignal = false;
          goto redo;
      }
      if(low <0 )
      { 
          flag =false;
          fclose(fp);
          close(client_sockfd);
          close(server_sockfd);
          printf("disconnection\n");
          goto redo;
      }else if (low ==0)
      {
          fclose(fp);
          close(client_sockfd);
          close(server_sockfd);
          flag=false;
          printf("low==0\n");
        //  break;
          goto redo; 
      }else
      {
          totalcnt+=low;
       //   printf("totalcnt= %d\n",totalcnt);
      }
     }

   if(NULL == strstr(buffer,"heartbeat"))
   fwrite(buffer,1,MAXSIZE,fp);
   printf("buffer= %s", buffer); 
   }

  }
  redo:
   sleep(3) ;
  }
  return 0;
}


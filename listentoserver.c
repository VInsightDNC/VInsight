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
* Name: listentoserver.c 
* Function: listen to the server. If there is any command from the server, insert it to list.
* The system may check the system periodically. 
* Author: Yuehua Wang 
* Email: yuehua.research@gmail.com
*/

#include "config.h"

<<<<<<< HEAD

=======
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
void *listen_to_server(void* arg)
{
  printf("s-6 listen_to_server\n");

<<<<<<< HEAD
  msg *current=(msg *)arg;

  int sockfd,len;
  int total,subtotal;
  int result;
  int opt = 1;
  int type,port;
  char buffer[MAXSIZE];
  struct sockaddr_in address;
  int msg_length=MAXSIZE,sub_length;
  bool flag = false; //socket is on or not
  struct sigaction sa;
  char *sub;
  char path[30];
  char snum[30];
  FILE *fd;

  if(( sockfd = socket(AF_INET,SOCK_STREAM,0))== -1)
   {
      perror("socket create error!\n");
      sleep(2);
      goto end;
=======
  
  me_th_id=pthread_create(&me_thread,NULL,processing_messges,NULL);

  connect_to_server();
}


int connect_to_server(int argc,char **argv)
{
  int sockfd,len;
  int total;
  int result;
  char recvs[MAXSIZE];
  char filepath[50];
  struct sockaddr_in address;
  struct hostent *host;
  int filesize1=0, filesize2=0;
  bool flag = false; //socket is on or not
  total =0;
  FILE *fd;


  //Prepare socket creation & file open
  host = gethostbyname(argv[1]) ;

  while(1) //redo the whole thing again
  {

    sleep(1);

    if(( sockfd = socket(AF_INET,SOCK_STREAM,0))== -1)
   {
      perror("socket create error!\n");
      sleep(2);
      continue;
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
   }

    bzero(&address,sizeof(address));
    address.sin_family = AF_INET;
<<<<<<< HEAD
    address.sin_addr.s_addr= inet_addr(current->ip);
    address.sin_port = htons(current->port); 
  
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    //Connect, read file, and send over socket;
    //Reconnection if socket fails
    result = connect(sockfd,(struct sockaddr *)&address,sizeof(address));
  
    while(1)
    {
        sub_length=MAXSIZE;
        msg_length=MAXSIZE;

        total=0;
        subtotal=0;
        
        memset(buffer,'\0',sizeof(buffer));
 
        if (result == -1)
       {
         perror("client");
         close(sockfd);
         goto end;
       }   
  
       if (is_outputs_list_empty()==false)
       {
         //send the data to the server;
         msg *frs=get_output();          
      
         if (frs->type ==VI_NETWORK_STATUS || frs->type == VI_FILE_END || frs->type == VI_RESULT_END)
         {
             memset(buffer,'0',MSG_HEAD_LENGTH);
   
             //type
             memset(snum,'\0',sizeof(snum));
             sprintf(snum,"%d",frs->type);
             strncpy(buffer+2-strlen(snum),snum,strlen(snum));
             //length
             strncpy(buffer+14,"20",2*sizeof(char));
             //content
             strncpy(buffer+16,VI_NULL,4*sizeof(char));

             while(1)
             {
                 len=write(sockfd,buffer,strlen(buffer));

             
                 if( len == MSG_HEAD_LENGTH)
                 {
                     break;        
                 }
                 else
                 {
             //      report error
                   perror("write error");
                   flag = false;
                   break;
                 }

              }
             // remove the msg
            remove_output();

         }
         if (frs->type == VI_NEW_FILE || frs->type ==VI_NETWORK_STATUS)
         {
           
           DIR  *d;
           struct dirent *dir;


           job *ijob=get_job();
           d=opendir(ijob->output);

           if(d)
          {
             while((dir = readdir(d))!=NULL)
             {
            
               // printf("%s\n",dir->d_name);
           
               fd = fopen(dir->d_name,"rb");
              
               if (fd == NULL)
               {
                          
                 perror("file open error\n");
                 exit(2);
               }
             char head[MSG_HEAD_LENGTH];

             memset(buffer,'\0',sizeof(buffer));

             memset(buffer,'\0',MSG_HEAD_LENGTH);
             //type
             memset(snum,'\0',sizeof(snum));
             sprintf(snum,"%d",VI_FILE_NAME);
             strncpy(buffer+2-strlen(snum),snum,strlen(snum));
             //length
             sprintf(buffer+10,"%d",strlen(dir->d_name)+16);
             //content
             strncpy(buffer+16,dir->d_name,strlen(dir->d_name));
              
             while(1)
             {
                 len=write(sockfd,buffer,strlen(buffer));

             
                 if( len == MSG_HEAD_LENGTH)
                 {
                     break;        
                 }
                 else
                 {
             //      report error
                   perror("write error");
                   flag = false;
                   break;
                 }

              }

             memset(head,0,MSG_HEAD_LENGTH);
             //type
             memset(snum,'\0',sizeof(snum));
             sprintf(snum,"%d",VI_FILE_CONTENT);
             strncpy(head+2-strlen(snum),snum,strlen(snum));
             //length
             //content
             strncpy(head+16,dir->d_name,strlen(dir->d_name));
              
             while(!feof(fd))
              {
                
                  memset(buffer,'\0',sizeof(buffer));
                 
                  memcpy(buffer,head,strlen(head)+1);

                  fgets(buffer+strlen(buffer),MAXSIZE-strlen(buffer),fd);
                  
                  len=write(sockfd,buffer,strlen(buffer));
                  sa.sa_handler =SIG_IGN;
                  sigaction(SIGPIPE,&sa,0);
                  
                  if(len>=0)
                    total =total+strlen(buffer); 
                  else    
                 {
                   perror("write error");
                   close(sockfd);
                   flag = false;
                   goto end; 
                 }
              
            
                }

             }
 
               closedir(d);
          }
             // remove the msg
            remove_output();
         }
         continue;
       }
       else{
       fd =NULL;

       while(1)
       {
           total=total+subtotal;
           subtotal=0;

           if(msg_length > MAXSIZE  && msg_length-total < MAXSIZE)   subtotal= msg_length-total;
            
           if(flag == true) break;

           while(1)
           {
                      
               len=read(sockfd,&buffer[subtotal],(sub_length-subtotal));
        
               sa.sa_handler =SIG_IGN;
      
               sigaction(SIGPIPE,&sa,0);
       
      
               if(len>=0)
               {
                 subtotal=strlen(buffer); 
              
                  if(total>MSG_HEAD_LENGTH && sub_length == MAXSIZE && msg_length == MAXSIZE)
                 {
                    sub=substring(buffer,0,2);
                    type=atoi(sub);
                    free(sub);

                    sub=substring(buffer,10,6);
                    msg_length=atoi(sub);
                    free(sub);

                    memset(path,'\0',sizeof(path));
                    sub=substring(buffer,2,8);
                    snprintf(path,30,"%s%s",jobs_path,sub);

                    fd=fopen(path,"a+b");
                      
                 }

                  if( type == VI_EXPERIMENT && sub_length == subtotal && fd !=NULL)
                  {
                    fwrite(buffer+16,1,sub_length,fd);
                    break;
                  }

                  if(strstr(buffer, VI_HEARTBEAT)!=NULL)
                   {
                     flag =true;
                     break;
                   }
                 
              }
               else
              {
                if(strlen(buffer)>0 || strstr(buffer, VI_NULL) != NULL || strstr(buffer,VI_END)!=NULL )
                {
                   if(strstr(buffer,VI_NULL)==NULL)
                   {
                     flag = false;
                     
                     
                     fclose(fd);
                     break;
                   }else
                   {

                     break;
                   }
                 }
              }

           }
        }
       }
    }
    close(sockfd);     

    if(flag ==true)
    {
        generate_msg(type,IP,port,VI_NULL);
 
    }

   end:
    ;

}


void *processing_messages(void* arg)
{
  send_connection_msg();
=======
    address.sin_addr = *((struct in_addr *)host->h_addr);
    address.sin_port = htons(SERVPORT); 
  
    int opt = 1;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    len = sizeof(address);
 

    //Connect, read file, and send over socket;
    //Reconnection if socket fails
    while(1)
   {  

     //sleep(1);
   
     if (flag == false)
     {
         result = connect(sockfd,(struct sockaddr *)&address,len);
        
         if (result == -1)
         {
            perror("client");
            close(sockfd);
            break;
         }else
            flag =true;
     }

     // /*hz
     //open file and go to file-end
     if (filesize1 != 0)  fclose(fd);
    
     strcpy(filepath,FILEPATH_Sensing);
 
     fd = fopen(filepath,"rb");
 
     if (fd == NULL)
     {
         perror("file open error\n");
         exit(2);
     }
    
     fseek(fd,0,SEEK_END);
     //  */

     filesize2 = ftell(fd);
     
     printf("filesize = %d , %d\n",filesize2, filesize1);
   
     if(filesize2>filesize1) //new data to transmit
     {  
      
       fseek(fd,total,SEEK_SET);

       filesize1 =filesize2;
  
       while(!feof(fd))
       {
          int lenx;
         
          memset(recvs,'\0',sizeof(recvs));
      
          fgets(recvs,MAXSIZE,fd);
      
          lenx=write(sockfd,recvs,strlen(recvs));
      
          printf("buffer: %s  %d %d \n",recvs, strlen(recvs), lenx);
       
      
          struct sigaction sa;
      
          sa.sa_handler =SIG_IGN;
      
          sigaction(SIGPIPE,&sa,0);
       
      
          if(lenx>=0)
              total =total+strlen(recvs); 
          else
         {
             perror("write error");
             close(sockfd);
             flag = false;
         
             //hz: fclose(fd);
        
             goto redo; //hz break; //???
         }

         }
       }//new data to transmit
    else
  {
    printf("The end of file! Put the thread into sleep 5s\n");
  
    sleep(1);

  } //no new data to transmit

  } //finish tx new data; go back to wait

  redo:
  ;

  } //redo the whole thing again

  close(sockfd);


  return 0;

}

void *processing_messages(void* arg)
{
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757

  while(1)
  {
    if(is_messages_list_empty()==false)
    {
<<<<<<< HEAD
      
      handle_msgs();
    }
  }
}
/*
 * 
typedef struct MSG{
  int length;
  int type;   // message type
  char ip[16];
  int port;
  char text[MESSAGE_LENGTH];
  struct MSG *next;
} msg;
 * */
void  send_connection_msg()
{
   msg *item=malloc(sizeof(struct MSG));
   item->type=VI_CONNECTION;
   
   memcpy(item->ip,IP,sizeof(IP) );
   item->ip[sizeof(IP)]='\0';

   item->port=SERVPORT;
   item->next=NULL;

   memcpy(item->text,VI_NULL,sizeof(VI_NULL) );
   insert_msgs(item);
}

char* substring(char* str, int begin, int len) 
{ 
    if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
          return 0; 

   return strndup(str + begin, len); 
} 


//connect to server and send control&maintenance messages
void connect_to_server(msg *current)
{
  int sockfd,len;
  int total;
  int result;
  int opt = 1;
  int type,port;
  char buffer[MAXSIZE];
  struct sockaddr_in address;
  int msg_length=MAXSIZE;
  bool flag = false; //socket is on or not
  struct sigaction sa;
  char *sub;
  char snum[8];
  total =0;

    sleep(1);

    if(( sockfd = socket(AF_INET,SOCK_STREAM,0))== -1)
   {
      perror("socket create error!\n");
      sleep(2);
      return;
   }

    bzero(&address,sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr= inet_addr(current->ip);
    address.sin_port = htons(current->port); 
  
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    //Connect, read file, and send over socket;
    //Reconnection if socket fails
    result = connect(sockfd,(struct sockaddr *)&address,sizeof(address));
    memset(buffer,'\0',sizeof(buffer));

    if (result == -1)
    {
      perror("client");
      close(sockfd);
      return;
    }   
   // send the connection request
    memset(buffer,'0',20);
    //type
    memset(snum,'\0',sizeof(snum));
    sprintf(snum,"%d",current->type);
    strncpy(buffer+2-strlen(snum),snum,strlen(snum));
    //length
    strncpy(buffer+14,"20",2*sizeof(char));
    //content
    strncpy(buffer+16,VI_NULL,4*sizeof(char));

        
    len=write(sockfd,buffer,strlen(buffer));

        
    if(len==-1)
    {
      perror("ERR: Write error. Reconnection is need.");
      close(sockfd);
    }    
    
    memset(buffer,'\0',sizeof(buffer));
    while(1)
    {

         len=read(sockfd,&buffer[total],(msg_length-total));
        
         sa.sa_handler =SIG_IGN;
      
         sigaction(SIGPIPE,&sa,0);
       
      
         if(len>=0)
         {
              total=strlen(buffer); 
              
              if(total>MSG_HEAD_LENGTH && msg_length == MAXSIZE )
              {
                 sub=substring(buffer,0,2);
                 type=atoi(sub);
                 free(sub);

                 sub=substring(buffer,10,6);
                 msg_length=atoi(sub);
                 free(sub);

              }

              
              if(total == msg_length && type == VI_CONNECTION_SUCCESS)
              {
                 sub=substring(buffer,16,msg_length-16);  
                 port=atoi(sub);
                 free(sub);
                 flag= true;
                 break;
              }
         }
          else
         {
             perror("write error");
             flag = false;
             break;
         }

    }
  
    close(sockfd);     

    if(flag ==true)
    {
       generate_msg(type,IP,port,VI_NULL);
 
    }

}

void generate_msg(int type, char *addr_ip, int port, char *data)
{
   msg *item=malloc(sizeof(struct MSG));
   item->type=type;
   
   memcpy(item->ip,addr_ip,sizeof(IP) );
   item->ip[sizeof(IP)]='\0';

   memcpy(item->text,data,sizeof(data));
   item->port=port;
   item->next=NULL;

   insert_msgs(item);
}
void  handle_msgs()
{
   msg *current;
   
   get_message(current);

   int type=current->type;

   switch(type)
   {
     case  VI_CONNECTION:
          connect_to_server(current); 
          break;
     case VI_CONNECTION_SUCCESS:
          me_th_id=pthread_create(&me_thread,NULL,processing_messages,current);
          // wait for connection
          sleep(5);
          break;
     case  VI_EMERGENCY_STOP:
           terminate_all();
       break;
     case VI_EXPERIMENT_COMPLETE:
           is_experiment_running();
           break;
     case VI_NETWORK_AVAILABLE:
           data_transmission(current);
           break; 
     case VI_TRANSMISSION_FINISH:
          //remove the job from the list and update the datebase.
           delete_job();
    default:
           break;
   }

    // give some time for message processing
    sleep(5);
    remove_message();
    return;
}
=======
      get_message();
      
      handle();
    }
  }
}

>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757

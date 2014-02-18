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
* Function: this is an example of the server that listens to the mobile platform and replies them with experiment tasks and demand information. By combining different requirements, this file can /ichanged. 
* Author: Yuehua Wang 
* Email: yuehua.research@gmail.com
*/

#include "serverside.h"


pthread_mutex_t con_mutex= PTHREAD_MUTEX_INITIALIZER; // threads

pthread_mutex_t pro_mutex=PTHREAD_MUTEX_INITIALIZER; // data list

pthread_mutex_t msg_mutex=PTHREAD_MUTEX_INITIALIZER; // msg list

pthread_mutex_t input_mutex=PTHREAD_MUTEX_INITIALIZER; // input list

void *thread_init_func(void *arg)
{

  thread_set();

  struct sockaddr_in sub_address,client;
  struct sigaction sa;
  socklen_t length;
  int sub_sockfd;
  int len,total;
  int tid=*((int*)arg);
  int opt=1; 
  char buffer[MAXSIZE];
  char filepath[50];
  char *exp;
  char head[MSG_HEAD_LENGTH];
 
  int client_sockfd; 
  bool flag = false;
  FILE *fd;

  char snum[30];
  change_status(&tid);
  
  // experiment requires i.e., experiment description
  char *input=INPUT;

  fetch_socket(&client_sockfd,&tid);
  
  // subserver address initialization
  sub_sockfd = socket(AF_INET,SOCK_STREAM,0);
  
  if(server_sockfd <0)
  {
    perror("Creating socket error!\n");
    exit(1);
  }
  bzero(&server_address,sizeof(struct sockaddr_in));
  sub_address.sin_family = AF_INET;
  sub_address.sin_addr.s_addr = htonl(INADDR_ANY);
  sub_address.sin_port = htons(threads[tid].port);

  setsockopt(sub_sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));  
 
  // socket bind
  if(bind(sub_sockfd,(struct sockaddr *)&sub_address,length) < 0)
  {
    perror("Bind error.");
    exit(1);
  } else
     printf("INFO: Sever sider bind successful!\n INFO: Waiting for mobile platform connection. \n");


  // listen to the connection requests from the mobile platforms
  if(listen(sub_sockfd,1) == -1)
  {
    printf("listen error!\n");
    exit(1);
  }
  
  // wait for connection
  flag=false;

  int  val = accept(sub_sockfd,(struct sockaddr *)&client, &length);
  
  if(val == -1)
  {
    printf("accept error!\n");
    close(val);
    goto end;
  }

  threads[tid].cli_sockfd=val;
  printf("connected!\n");

  //allocate the new experiment to the client 
  while(1)
  {
  exp=get_new_input();

  memset(buffer,'0',MSG_HEAD_LENGTH);
  //type
  memset(snum,'\0',sizeof(snum));
  sprintf(snum,"%d",VI_EXPERIMENT);

  strncpy(buffer+2-strlen(snum),snum,strlen(snum));
  //length
  strncpy(buffer+14,"20",2*sizeof(char));
  //content

  if(exp !=NULL)
  {
    sprintf(buffer+16,"%s",exp);
    struct INPUTS  *din;
    din=new_input(exp);
    insert_inputs(din);
  
    //sprintf(buffer_16,"%s",VI_HEARTBEAT);

    while(1)
    {
      len=write(val,buffer,strlen(buffer));
             
       if( len> MSG_HEAD_LENGTH)
       {
         break;        
       }
       else
       {
          perror("write error");
          break;
       }
    }

    // send the experiment description to the mobile platform
      memset(head,0,MSG_HEAD_LENGTH);
      //type
      memset(snum,'0',sizeof(snum));
      sprintf(snum,"%d",VI_FILE_CONTENT);
      strncpy(head+2-strlen(snum),snum,strlen(snum));

      fd=fopen(exp,"a+b");
      
      while(!feof(fd))
      {

      memset(buffer,'\0',sizeof(buffer));
                 
      memcpy(buffer,head,strlen(head)+1);

      fgets(buffer+strlen(buffer),MAXSIZE-strlen(buffer),fd);
                  
      len=write(val,buffer,strlen(buffer));
      sa.sa_handler =SIG_IGN;
      sigaction(SIGPIPE,&sa,0);
                  
      if(len>=0)
        total =total+strlen(buffer); 
      else    
      {
        perror("write error");
        close(val);
        flag = false;
        goto end; 
      }
      }
      fclose(fd);
  }
   
   change_thread_status(&tid, VI_RUNNING);
   
   //listen to the mobile platform and send back the response
   while(threads[tid].status != VI_TRANSMISSION_FINISH)
   {
      int ex_thread_id;     
      
      ex_thread_id=pthread_create(&ex_thread[tid],NULL,listening,(void *)tid);
 
      sleep(HEARTBEAT_INTERVAL);

      while(1){
    
      pthread_mutex_lock(&con_mutex);

      if(threads[tid].status == VI_IDLE)
      {
          pthread_mutex_unlock(&con_mutex);
          pthread_cancel(ex_thread[tid]);
          break;
      }

      pthread_mutex_unlock(&con_mutex);
      sleep(HEARTBEAT_INTERVAL);
      }
      //heartbeat message

      memset(buffer,'0',MSG_HEAD_LENGTH);
      //type
      memset(snum,'\0',sizeof(snum));
      sprintf(snum,"%d",VI_EXPERIMENT);

      strncpy(buffer+2-strlen(snum),snum,strlen(snum));
      //length
      strncpy(buffer+14,"20",2*sizeof(char));
      //content
      sprintf(buffer+16,"%s",VI_HEARTBEAT);

       while(1)
      {
      len=write(val,buffer,strlen(buffer));
             
       if( len> MSG_HEAD_LENGTH)
       {
         break;        
       }
       else
       {
          perror("write error");
          break;
       }
      }
   }

   change_thread_status(&tid, VI_IDLE);
  
  }

 close(val);
end:
 ;
}
void *listening(void *arg)
{
  struct sigaction sa;
  int *tid=(int *)arg;
  int subtotal,total;
  int sub_length;
  int msg_length;
  int type;
  int count;
  int len;
  char buffer[MAXSIZE];
  char filepath[50];
  char *exp;
  char head[MSG_HEAD_LENGTH];
 
  char *sub;
  char snum[30];
  int client_sockfd;
  int sockfd;
  bool flag = false;
  FILE *fd;
  
  sockfd=threads[*tid].cli_sockfd;

  while(1)
  {
  
     len=read(sockfd,&buffer[subtotal],(sub_length-subtotal));

     change_thread_status(tid, VI_RUNNING);

     sa.sa_handler =SIG_IGN;
      
     sigaction(SIGPIPE,&sa,0);
       
      
      if(len>=0)
      {
         subtotal=strlen(buffer); 
              
         if(subtotal>MSG_HEAD_LENGTH)
         {
            sub=substring(buffer,0,2);
            type=atoi(sub);
            free(sub);

           count=0; 
           if( type == VI_NETWORK_STATUS)
           {
              while( check_network_status()!= false)
              {
                 if(count<100)
                 {
                   count++;
                   sleep(1);
                 }else
                 {
                   flag =true;
                   break;
                 }
              }
              if(flag == true)
              {
                flag=false;

                change_thread_status(tid, VI_IDLE);
                 
                continue;
              }else
              {

                //network available message

                 memset(buffer,'0',MSG_HEAD_LENGTH);
                //type
                  memset(snum,'\0',sizeof(snum));
                 sprintf(snum,"%d",VI_NETWORK_AVAILABLE);

                 strncpy(buffer+2-strlen(snum),snum,strlen(snum));
                 //length
                 strncpy(buffer+14,"20",2*sizeof(char));
                 //content
                 sprintf(buffer+16,"%s",VI_NULL);

                 while(1)
                 {
                   len=write(sockfd,buffer,strlen(buffer));
             
                   if( len> MSG_HEAD_LENGTH)
                   {
                      break;        
                    }
                   else
                    {
                      perror("write error");
                      break;
                    }
                }
              }// if flag ==true
           }

           if( type == VI_NEW_FILE )
           {
                 change_thread_status(tid, VI_TRANSMISSION);
                 fd=fopen(buffer+16,"a+b");
               
                 subtotal=0;
                 while(1)
                 {  len=read(sockfd,&buffer[subtotal],MAXSIZE-subtotal);


                    sa.sa_handler =SIG_IGN;
      
                    sigaction(SIGPIPE,&sa,0);
       
      
                   if(len>0)
                   {
                     
                      subtotal=subtotal+strlen(buffer); 
              
                      if(subtotal>MSG_HEAD_LENGTH)
                      {
                         sub=substring(buffer,0,2);
                         type=atoi(sub);
                         free(sub);
                       
                         if(type == VI_FILE_CONTENT)
                         { 
                          fwrite(buffer+16,1,strlen(buffer)-16,fd);
                          subtotal=0;
                         }else
                           if(type ==VI_FILE_END)
                           { 
                             fclose(fd);
                             break;
                           }
                      }
                   }else
                     break;
                 }
           }
          
           if( type == VI_TRANSMISSION_FINISH )
           {
             change_thread_status(tid, VI_IDLE);
           }
          
         }//subtotal>MSG_HEAD_LENGTH
       }// len >0
                      
     }
  }


bool check_network_status()
{
  bool flag =true;
  pthread_mutex_lock(&con_mutex);

  for(int i=0;i<MAXNUM;i++)
  {
    if(threads[i].status == VI_RUNNING || threads[i].status == VI_TRANSMISSION)
    {
      flag = false;
      break;
    }
  }
  pthread_mutex_unlock(&con_mutex);
  return flag;
}
void change_thread_status(int *id, int stat)
{
  pthread_mutex_lock(&con_mutex);

  threads[*id].status=stat;
  pthread_mutex_unlock(&con_mutex);
}
void  fetch_socket(int *socketfd, int *id)
{

  pthread_mutex_lock(&con_mutex);

  *socketfd=threads[*id].cli_sockfd;
  pthread_mutex_unlock(&con_mutex);

}
void  set_port(int count, int port)
{

  pthread_mutex_lock(&con_mutex);

  threads[count].port=port;
  pthread_mutex_unlock(&con_mutex);

}

void  change_status(int *id)
{

  pthread_mutex_lock(&con_mutex);

  threads[*id].flag=true;
  pthread_mutex_unlock(&con_mutex);
}
void listen_to_client()
{

  int opt = 1;
  int len; 
  char buffer[MAXSIZE];
  char snum[30];
  bool flag=false;

  
  // server address initialization
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

  setsockopt(server_sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));  
 
  // socket bind
  if(bind(server_sockfd,(struct sockaddr *)&server_address,length) < 0)
  {
    perror("Bind error.");
    exit(1);
  } else
     printf("INFO: Sever sider bind successful!\n INFO: Waiting for mobile platform connection. \n");

  // listen to the connection requests from the mobile platforms
  if(listen(server_sockfd,MAXNUM) == -1)
  {
    printf("listen error!\n");
    exit(1);
  }
  
   // check if there is any new requests
  while(1)
  {
      // wait for connection
      flag=false;
      find_idle_threads();

      if(count != INVALID)
      {
        threads[count].cli_sockfd = accept(server_sockfd,(struct sockaddr *)&(threads[count].cli_addr), &length);
  
         if(threads[count].cli_sockfd == -1)
         {
            printf("accept error!\n");
            close(threads[count].cli_sockfd);
            continue;
         }else
         {
           //rebuild the connection
           printf("connected!\n");
           set_port(count,SUB_PORT+count);  
           
           memset(buffer,'0',MSG_HEAD_LENGTH);
   
           //type
            memset(snum,'\0',sizeof(snum));
            sprintf(snum,"%d",VI_CONNECTION_SUCCESS);
            strncpy(buffer+2-strlen(snum),snum,strlen(snum));
           //length
            strncpy(buffer+14,"20",2*sizeof(char));
            //content
            sprintf(buffer+16,"%d",SUB_PORT+count);

             while(1)
             {
                 len=write(server_sockfd,buffer,strlen(buffer));

             
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
         }
        pthread_create(&threads[count].tid,NULL,&thread_init_func,(void *)count);
        // give the new thread some time 
        sleep(1);

        close(threads[count].cli_sockfd);
        
      }else
        sleep(10);
      
      sleep(1);
  }
}

void find_idle_threads()
{
  
 pthread_mutex_lock(&con_mutex);

 for(int i=0;i<MAXNUM;i++)
  {
    if(threads[i].flag == false)
    {
       count=i;
      
       pthread_mutex_unlock(&con_mutex);

       return;
    }

  }

  count =INVALID;

  pthread_mutex_unlock(&con_mutex);
}

void handler(int sigum)
{
   fprintf(stderr,"caught broken contection.\n");
}


void thread_set()
{
  
  int s;

  s = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
          
  if (s != 0)
  handle_error_en(s, "pthread_setcancelstate");
 
}

void setting()
{
  length=sizeof(server_address);
  count=0;
  
  pthread_mutex_lock(&con_mutex);
  for(int i=0;i<MAXNUM;i++)
  threads[i].flag=true;
  pthread_mutex_unlock(&con_mutex);

  msg_list_init(); 
  input_list_init();
}
/*--------------------------------------------------------------------------------
 * Main function
 *--------------------------------------------------------------------------------- */
int main(int argc,char **argv)
{ 
  
  setting();
  
  // lister to clients
  
  listen_to_client();

  atexit(cleanup);

}

void cleanup()
{
  printf("INFO: Close the server.\n");

  cleanup_threads();
}

void cleanup_threads()
{

  //destroy the mutexes
  pthread_mutex_destroy(&con_mutex);
  pthread_mutex_destroy(&pro_mutex);
  
  //stop the threads
 for(int i=0;i<MAXNUM;i++)
  pthread_cancel(threads[i].tid);

  pthread_cancel(pcthread);

}

void msg_list_init()
{

   msgs_list=malloc(sizeof(msgs_queue));
   msgs_list->head=NULL;
   msgs_list->tail=NULL;
}

void input_list_init()
{

   inputs_list=malloc(sizeof(inputs_queue));
   inputs_list->head=NULL;
   inputs_list->tail=NULL;
}

bool search_input(char *name)
{

  if(inputs_list->head == NULL)
    return false;
  input *temp=inputs_list->head;

  while(temp != NULL)
  {
     if (strcmp(temp->name,name)==0)
       return true;
     else
       temp=temp->next;
  }

  return false;
}
char *get_new_input()
{
    DIR  *d;
    struct dirent *dir;
    char *name;
    bool flag= false;

    d=opendir(INPUT);
    name=(char *)malloc(20*sizeof(char));
    pthread_mutex_lock(&input_mutex);
  
    if(d)
    {
      while((dir = readdir(d))!=NULL)
      {
       
        if(search_input(dir->d_name)==false)
          {
            memset(name,'\0',strlen(name));
            memcpy(name,dir->d_name,strlen(dir->d_name));
            flag=true;
            break;
          }
           
      }
    }
    
    pthread_mutex_unlock(&input_mutex);
  
    if(flag==true)
    {
      return name;
    }else
      return NULL;

}
void  handle_msgs()
{
   msg *current;
   
   get_message(current);

   int type=current->type;

   switch(type)
   {
     case  VI_CONNECTION:
       break;
     case VI_CONNECTION_SUCCESS:
       break;
     case VI_EXPERIMENT:
       break;
     case  VI_RESOURCE_STATUS:
       break;
     case  VI_EMERGENCY_STOP:
       break;
     case VI_EXPERIMENT_COMPLETE:
       break;
     case VI_NETWORK_STATUS:
       break;
     case VI_NETWORK_AVAILABLE:
       break;
     case VI_FILE_END:
       break;
     case VI_RESULT_END:
       break;
    case VI_NEW_FILE:
       break;
    default:
       break;
   }
}


void get_message(msg *current)
{

  pthread_mutex_lock(&msg_mutex);

  if(msgs_list->head == NULL)
    current=NULL;
  else
    current=msgs_list->head;

  pthread_mutex_unlock(&msg_mutex);
}
bool insert_inputs(input *item)
{
 
  pthread_mutex_lock(&input_mutex);
 
  if(item == NULL)
    return false;
  
  if(inputs_list->tail !=NULL)
    (inputs_list->tail)->next=item;

  inputs_list->tail=item;

  if(inputs_list->head == NULL)
    inputs_list->head=item;
  
  pthread_mutex_unlock(&input_mutex);
  return true;
}

input *new_input(char *name)
{
  input *item=(input *)malloc(sizeof(struct INPUTS));
  memset(item->name,'\0',strlen(item->name));
  memcpy(item->name,name,strlen(name));
  item->next=NULL;
  
  return item;
}
char* substring(char* str, int begin, int len) 
{ 
    if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
          return 0; 

   return strndup(str + begin, len); 
} 

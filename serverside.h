
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
* Name: serverside.h
* Function: contains the definition of the variables and functions 
* Author: Yuehua Wang 
* Email: yuehua.research@gmail.com
*/



#ifndef __severside_H__
#define __serverside_H__ 1

#include <stdio.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <curses.h>
#include <time.h>
#include <signal.h>
#include <sqlite3.h>
#include <fcntl.h>
#ifndef S_SPLINT_S
#include <unistd.h>
#endif /* S_SPLINT_S */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <dirent.h>


//********************************************************************************
// message type
//********************************************************************************
#define VI_CONNECTION 0
#define VI_CONNECTION_SUCCESS 1
#define VI_EXPERIMENT 2
#define VI_RESOURCE_STATUS 3
#define VI_EMERGENCY_STOP 4
#define VI_EXPERIMENT_COMPLETE 5
#define VI_NETWORK_STATUS 6
#define VI_NETWORK_AVAILABLE 7
#define VI_FILE_END 8
#define VI_RESULT_END 9
#define VI_NEW_FILE 10
#define VI_TRANSMISSION_FINISH 11
#define VI_FILE_NAME 12
#define VI_FILE_CONTENT 13
#define VI_IDLE 14
#define VI_RUNNING 15
#define VI_TRANSMISSION 16

#define VI_END "END"
#define VI_NULL "NULL"
#define VI_HEARTBEAT "heartbeat"

#define MAXSIZE 500
#define MAXNUM 50
#define INVALID 1000
#define SERVPORT 3111
#define SUB_PORT 4111
#define MESSAGE_LENGTH 1024
#define MSG_HEAD_LENGTH 16
#define HEARTBEAT_INTERVAL 120

#define INPUT "./input/"
#define RESULTS "./received_results/"
#define handle_error_en(en, msg)  do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)


struct sockaddr_in server_address;
int server_sockfd;
pthread_t pcthread;
int pc_pid;
int length;
int count;
typedef void (*sighandler_t)(int);

typedef struct thread{
    pthread_t tid; 
    struct sockaddr_in cli_addr;  
    int cli_sockfd;
    int port;
    bool flag;
    int status; //1 running //2 complete
} Thread;

typedef struct MSG{
  int length;
  int type;   // message type
  char ip[16];
  int port;
  char text[MESSAGE_LENGTH];
  struct MSG *next;
} msg;

typedef struct INPUTS{
  char name[20];
  struct INPUTS *next;
} input;

typedef struct {
  int length;
  int type;
  char exid[10];
  char text[MESSAGE_LENGTH];
} tcpmsg;

typedef struct {
  input *head;
  input *tail;
} inputs_queue;

typedef struct {
  msg *head;
  msg *tail;
}msgs_queue;

msgs_queue *msgs_list;
inputs_queue *inputs_list; 

Thread threads[MAXNUM];

pthread_t ex_thread[MAXNUM]; // listening threads

extern pthread_mutex_t con_mutex;
extern pthread_mutex_t pro_mutex;
extern pthread_mutex_t msg_mutex;
extern pthread_mutex_t input_mutex;

void *thread_init_func(void *arg);
void *listening(void *arg);
void thread_set();
void change_status(int *id);
void fetch_socket(int *socketfd, int *id);
void handler(int sigum);
void listen_to_client();
void *processing_requests(void *arg);
void find_idle_threads();
void cleanup();
void cleanup_threads();
void msg_list_init();
void input_list_init();
void handle_msgs();
void get_message(msg *current);

bool insert_inputs(input *item);
void change_thread_status(int *id, int stat);
input *new_input(char *name);
char *get_new_input();
void  set_port(int count, int port);
char* substring(char* str, int begin, int len); 
bool check_network_status();
#endif

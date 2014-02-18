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
* Name: config.h
* Function: 
* Author: Yuehua Wang 
* Email: yuehua.research@gmail.com
*/


#ifndef __config_H__
#define __config_H__ 1

#include <stdio.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
<<<<<<< HEAD
#include <stdint.h>
=======
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
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
<<<<<<< HEAD
#include <dirent.h>
=======

#include "./lib/client/oml2/omlc.h"

>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
//********************************************************************************
// gps
//********************************************************************************

#include "include/gpsd_config.h"
#include "include/gps.h"
#include "include/gpsdclient.h"
#include "include/revision.h"
<<<<<<< HEAD
#include "include/client/oml2/omlc.h"
#define OML_FROM_MAN
//********************************************************************************
// job data base
//********************************************************************************

#define JOB_DB "jobs.db"

//********************************************************************************
// normal computing operation
//********************************************************************************

=======


//********************************************************************************
// job data base
//********************************************************************************
#define JOB_DB "jobs.db"
//********************************************************************************
// normal computing operation
//********************************************************************************
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
#define MIN(a,b)      ((a<b)?(a):(b))
#define MAX(a,b)      ((a>b)?(a):(b))
#define ABS(x)        ((x>0)?(x):(-x))


//********************************************************************************
// datatype rename
//********************************************************************************
<<<<<<< HEAD

=======
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
typedef unsigned char  uint8;                  
typedef signed   char  int8;                    
typedef unsigned int   uint16;                   
typedef signed   int   int16;                       
typedef unsigned long  uint32;                     
typedef signed   long  int32;                     

<<<<<<< HEAD
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
//********************************************************************************
// experiment engine
//********************************************************************************

=======

//********************************************************************************
// experiment engine
//********************************************************************************
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
#define NORMAL_EXPERIMENT 0
#define EARLIEST 1 //level 2 is reserved for extension
#define MAINTENANCE 3 //level 4 is reserved for extension
#define EMERGENCY_STOP 5
<<<<<<< HEAD
#define ENTITY_NUM 4

#define MESSAGE_LENGTH 1024
#define NOT_EXIST 0
#define OPEN_EMPTY 3
#define LOG_LENGTH 100
#define MSG_HEAD_LENGTH 16
#define handle_error_en(en, msg)  do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

typedef struct MSG{
  int length;
  int type;   // message type
  char ip[16];
  unsigned short port;
  char text[MESSAGE_LENGTH];
  struct MSG *next;
} msg;


typedef struct {
  int length;
  int type;
  char exid[10];
  char text[MESSAGE_LENGTH];
} tcpmsg;

typedef struct {
  long int second;
  int millis;
} vtime;

typedef struct VNODE{
int x;
int y;
int oml;
int type;
char ip[16];
unsigned short port;
struct VNODE *next;
} vnode;

typedef struct VRECE {
  vnode *head;
  vnode *tail;
}vreceivers;

typedef struct DATA{
  char *path;
  struct DATA *next;
}vdata;

typedef struct JOB{ //create for every experiment commands received from the  on the OMF server
=======

#define ENTITY_NUM 4

#define handle_error_en(en, msg)  do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)




pthread_t entities[ENTITY_NUM];
pthread_t ex_thread;
pthread_t trans_thread;
/*
pthread_t th_resource; //resource_manager
pthread_t th_experiment; //experiment_controller
pthread_t th_collection; //data_collection
pthread_t th_transmission; //data_transmission
pthread_t th_health; //health_monitoring
pthread_t th_listener; // listen_to_server
*/
int th_id[ENTITY_NUM];
int ex_th_id;
int ex_trans_id;
/*
int res_id;
int exp_id;
int col_id;
int tra_id;
int hea_id;
int lis_id;
*/
extern pthread_mutex_t ex_jobs_mutex; // experiment job list
extern pthread_mutex_t sys_task_mutex; // system task list sorted by the priority 
extern pthread_mutex_t data_mutex; // data list

pthread_cond_t count_thread; // num of threads

void start_engine();
void wait_for_termination();

void *resource_manager(void *arg);
void *experiment_controller(void *arg);
void *health_monitoring(void *arg);
void *listen_to_server(void *arg);
void *data_collection(void *arg);
void *data_transmission(void *arg);

typedef struct job job; // add a type alias 'job' in the global name space 
typedef struct jobs_linked_queue jobs_queue;
typedef struct time_sys vtime;
typedef struct node vnode;
typedef struct receiver_linked_queue vreceivers;

struct time_sys{
  long int second;
  int millis;
};

struct node{
int x;
int y;
int type;
char ip[15];
int port;
vnode *next;
};

struct job { //create for every experiment commands received from the  on the OMF server
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
  int id;
  int type;
  int priority;
  int status; 
  int waiter;
  char name[10];
  vtime start_time;
  vtime end_time;
  bool mode[3]; // mode[0]:gps; mode[1]:wimax dongle; mode[2]:openxc;
  char *des_path;
  char *output;
  vnode *sender;
  vreceivers *receivers;
<<<<<<< HEAD
  struct JOB *next;
}job;

typedef struct {
  job *head;
  job *tail;
} jobs_queue;


typedef struct {
  msg *head;
  msg *tail;
}msgs_queue;

typedef struct {
  vdata *head;
  vdata *tail;
}datas_queue;

jobs_queue *jobs_list;
msgs_queue *msgs_list;
msgs_queue *outputs_list;
datas_queue *datas_list;

pthread_cond_t count_thread; // num of threads

pthread_t entities[ENTITY_NUM];
pthread_t ex_thread; // experiment execution thread
pthread_t trans_thread; // data transmission thread
pthread_t me_thread; // message processing thread

int th_id[ENTITY_NUM];
int ex_th_id;
int ex_trans_id;
int me_th_id;
int job_mode;
bool stop_flag;

extern pthread_mutex_t ex_jobs_mutex; // experiment job list
extern pthread_mutex_t sys_task_mutex; // system task list sorted by the priority 
extern pthread_mutex_t data_mutex; // data list
extern pthread_mutex_t msg_mutex; // message list

void cleanup_threads();
void clear_jobs();
void start_engine();
void wait_for_termination();
void *resource_manager(void *arg);
void *experiment_controller(void *arg);
void *health_monitoring(void *arg);
void *data_collection(void *arg);
void data_transmission(msg *current);
//********************************************************************************
// resource manager
//********************************************************************************

=======
  job *next;
};

struct jobs_linked_queue{
  job *head;
  job *tail;
};

struct receiver_linked_queue{
  vnode *head;
  vnode *tail;
};

jobs_queue *jobs_list;

struct thread_data{
  int sum;
  char *message;
};

bool stop_flag;
struct thread_data thread_data_array[6];

void cleanup_threads();
void clear_jobs();

//********************************************************************************
// resource manager
//********************************************************************************
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
#define OPEN_ERROR 1 //used to describe the state of device opening error 
#define OPEN_SUCCESS 2
#define BUF_SIZE 1000
#define GPS_LOG_PATH "gpslog.txt"
#define GPS_ERROR_MASSAGE  "gpsd:ERROR: device open failed:"
<<<<<<< HEAD
#define VI_END "END"
#define VI_NULL "NULL"
#define VI_HEARTBEAT "heartbeat"

=======
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757

static char *GPSLOG="gpslog.txt";
static char *OPENXCLOG="openxclog.txt";
static char *DONGLELOG="donglelog.txt";
static char *gps_error_message="gpsd:ERROR: device open failed:";
static char *openxc_error_message="Couldn't find a USB product";
static char *dongle_error_message="Connecting to 192.168.0.1:80";
<<<<<<< HEAD
static char *jobs_path="./received_jobs/";
=======

>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
bool reserve_flag;


void thread_set();
int db_table;
int db_jobs_num;
bool device_init();
void device_close();
bool gps_init();
bool openxc_init();
bool wimax_dongle_init();
bool device_config(job *item);
bool gps_config(job *item);
bool openxc_config(job *item);
bool gps_stop();
bool openxc_stop();
bool wimax_dongle_stop();
void database_init();
int check_status(char *filepath, char *error_message);
void set_jobid(job *item);
void insert_to_db(job *item);
void delete_all_db();
void update_db(job *item, int status);
void update_job_db();
void terminate_all();
<<<<<<< HEAD

=======
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
//********************************************************************************
// Experiment controller
//********************************************************************************

#define INVALID_CHAR "#"
#define END_CHAR "}"
#define EARLIEST 1
#define MAX_LENGTH 50
#define MODE_1 1 //openxc sensing
#define MODE_2 2 //wimax measurement
#define MODE_3 3 //hybrid
#define PROCESSING 0
#define SUBMITTED 1
#define COMPLETED 2
#define FAILED 3

int jobs_num;
void jobs_list_init();
<<<<<<< HEAD
void msg_list_init();
job *read_job();
job *get_job();
=======
job *read_job();
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
bool insert_jobs(job *item);
bool delete_job();
bool sorted_insert(job *item);
job *new_jobs(char *filepath);
void print_jobs_list();
bool check_description(char *filepath,const char *keyword[]);
void get_keyword_length(const char *keyword[], int *length);
char *get_value(char *buf,int beg,int end);
void receives_init(job *item);
bool insert_receivers(job *list,vnode *item);
void set_output(job *item);
bool execute_jobs();
bool check_job_list();
void experiment(job *item);
void maintenance(job *item);
void emergency_stop();

<<<<<<< HEAD
bool insert_msgs(msg *item);
msg *new_message(int type, char *ip, int port, char *buf);
bool is_messages_list_empty();
bool is_outputs_list_empty();
void outputs_list_init();
bool insert_outputs(msg *item);
bool is_data_list_empty();
void data_list_init();
void get_message(msg *current);
void clear_outputs();
void clear_msgs();
bool remove_output();
bool remove_message();
msg *get_output(); 
void get_message(msg *current);
=======

>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
//********************************************************************************
// Data collection 
//********************************************************************************

static enum deg_str_type deg_type = deg_dd;
static struct gps_data_t gpsdata;
static time_t status_timer;	/* Time of last state change. */
static float altfactor = METERS_TO_FEET;
static float speedfactor = MPS_TO_MPH;
static char *altunits = "ft";
static char *speedunits = "mph";
static struct fixsource_t source;

#ifdef TRUENORTH
static bool compass_flag = false;
#endif /* TRUENORTH */

/* pseudo-signals indicating reason for termination */
#define CGPS_QUIT	0	/* voluntary yterminastion */
#define GPS_GONE	-1	/* GPS device went away */
#define GPS_ERROR	-2	/* low-level failure in GPS read */
#define GPS_TIMEOUT	-3	/* low-level failure in GPS waiting */

void store_gps_data(job *item);
bool signal_status(job *item);
bool is_gps_ready();
void get_gps(struct gps_data_t *gpsdata, char *scr);
void die(int sig);

<<<<<<< HEAD
bool link_delay(job *item);
=======
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
//********************************************************************************
// Listen to server 
//********************************************************************************

<<<<<<< HEAD
#define MAXSIZE 500
#define IP "10.3.11.28"
#define SERVPORT 3111

void connect_to_server(msg *current);
void *processing_messages(void* arg);
void send_connection_msg();
void *listen_to_server(void *arg);
void handler(int s);
void handle_msgs();
void generate_msg(int type, char *addr_ip, int port, char *data);

char* substring(char* str, int begin, int len); 
//********************************************************************************
// Data transmission
//********************************************************************************

#define UN_OML 0
#define OML 1

=======
int connect_to_server(int argc,char **argv)
//********************************************************************************
// Data transmission
//********************************************************************************
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
typedef void (*sighandler_t)(int);

static int m_accuracy;
static int m_filesize;
static int m_filelength;
static int m_conlength;
static int m_interval;
static int m_sleep=10;
static int m_maxloop =20;

static OmlMPDef mp_def[] = {
      { "time_Int", OML_LONG_VALUE}, // OML_DOUBLE_VALUE },
      { "time_Flo", OML_LONG_VALUE},
      { "type", OML_UINT32_VALUE },
      { "value", OML_STRING_VALUE },
      { NULL, (OmlValueT)0 }
    };

static char *con[] = {"engine_speed",
              "vehicle_speed",
              "fuel_consumed_since_restart",
              "steering_wheel_angle",
              "odometer",
              "accelerator_pedal_position",
              "fuel_level",
              "fine_odometer_since_restart"};


static char *tar[] = {"eng_speed",
              "vehi_speed",
              "fuel_restart",
              "wheel_angle",
              "od_ometer",
              "pedal_pos",
              "fuel_level",
              "fine_odome"};

<<<<<<< HEAD
bool read_file(char *file_name);
int index_of_type(char *buf);
void initilization( char *arv[]);
void stringToDouble(char *po, long *intp, long *flop);
bool is_experiment_running();
void trans_mode(job *item);
void oml_data_trans(msg *current);
void normal_data_trans(msg *current);
int  oml_transmission(int argc, char **argv);
//********************************************************************************
// Health monitoring
//********************************************************************************

=======
void handler(int s);

bool read_file(char *file_name);
int index_of_type(char *buf);
void initilization(const char *arv[]);
double  stringToDouble(char *p);
//********************************************************************************
// Health monitoring
//********************************************************************************
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
#define HEARTBEAT_INTERVAL 120

bool heartbeat_existence();
bool check_all_entities();
bool check_all_devices();

//********************************************************************************
// GPS coordinates of the vertexes
//********************************************************************************
<<<<<<< HEAD

=======
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
#define LEFTTOP_X 42.36514
#define LEFTTOP_Y -83.085229
#define RIGHTBOTTOM_X 42.346778
#define RIGHTBOTTOM_Y -83.049352
#define NUM 8 // number of the blocks in the 2-D map

bool get_corrdinates(double x,double y, int  *vx, int *vy);
<<<<<<< HEAD

//********************************************************************************
// VInsight files
//********************************************************************************

=======
//********************************************************************************
// VInsight files
//********************************************************************************
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
#endif

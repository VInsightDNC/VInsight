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
* Name: resourcemanager.c
* Function: manage the resources belonging to this platform
* Author: Yuehua Wang 
* Email: yuehua.research@gmail.com
*/
#include "config.h"

<<<<<<< HEAD

pthread_mutex_t ex_jobs_mutex= PTHREAD_MUTEX_INITIALIZER; // experiment job list
pthread_mutex_t sys_task_mutex=PTHREAD_MUTEX_INITIALIZER; // system task list sorted by the priority 
pthread_mutex_t msg_mutex=PTHREAD_MUTEX_INITIALIZER; // msg list
pthread_mutex_t data_mutex=PTHREAD_MUTEX_INITIALIZER; // data list
=======
#define NOT_EXIST 0
#define OPEN_EMPTY 3
#define LOG_LENGTH 100
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757

void *resource_manager(void *arg)
{
  printf("s1-resource manager.\n");

  thread_set();

  device_init();
 
  while(1){

  pthread_mutex_lock(&sys_task_mutex);
    
  if(reserve_flag == true && jobs_num == 0){

      device_close();

      device_init();

      reserve_flag = false;

    }
    sleep(5);
    
    pthread_mutex_unlock(&sys_task_mutex);
  }
}

void thread_set()
{
  
  int s;

  s = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
          
  if (s != 0)
  handle_error_en(s, "pthread_setcancelstate");
 
}

int check_status(char *filepath, char *error_message)
{
  FILE *fp;
  char buf[200];
  int  num_lines=0;
  fp=fopen(filepath,"r");

  if(!fp)
    return NOT_EXIST;

  while(true)
  {
   if (fgets(buf,200,fp)!=NULL)
   { 
     num_lines++;
     
     if(strstr(buf,error_message)!=NULL)
     {
       fclose(fp);
       return OPEN_ERROR;
     }
     
     if(num_lines >=LOG_LENGTH)
       break;
     else
       continue;
   }
   else
    break;
     // return OPEN_ERROR;
  }
  fclose(fp);

  if(num_lines==0 )
    return OPEN_EMPTY;
  else
    return OPEN_SUCCESS;
}

void clean_log(char *filepath)
{
  int status;

  status=remove(filepath);

  /* show 
  if(0==status)
    printf("%s file deleted successfully.\n",filepath);
  else
    printf("unable to delete the file\n");
  */
}


bool gps_init()
{
  int status;

  bool flag=false;
 
 
  /*********************************GPS initialization**************************************************/
  //clean the gpslog first
  clean_log(GPSLOG);

  printf("this is device_init() functions. Please release the resources.\n");

  //execl("/bin/ls","ls","-al",NULL);
 
  //start the gpsd daemon service
  system("gnome-terminal -x bash -c 'sudo killall gpsd; sudo gpsd -Nn -D2 /dev/ttyACM0 2> >(tee  gpslog.txt) ' ");
  
  while(true)
  {
    status=check_status(GPSLOG,gps_error_message);
    switch(status)
    {
         case NOT_EXIST:
              sleep(5);           
              break;
         case OPEN_ERROR:
              printf("INFO:Experiment Engine is going to be terminated due to the device error.\n");
              printf("INFO:Password may be needed to conduct the close operation.\n");
              system("sudo killall gpsd");

              printf("INFO:GPSD has been closed.\n");
              flag=true;
              break;
         case OPEN_SUCCESS:
              flag=true;
              break;
         case OPEN_EMPTY:
              sleep(5);
              break;
         default:
              break;
   }
    if (true == flag)
      break;
  }

  if ( flag == true)
    return true;
  else
    return false;
}
bool openxc_init()
{
int status;

bool flag=false;

/*********************************Openxc initialization**************************************************/
clean_log(OPENXCLOG);

 system("gnome-terminal -x bash -c 'sudo openxc-dump 2> >(tee  openxclog.txt) ' ");

while(true)
{
  status=check_status(OPENXCLOG,openxc_error_message);
  switch(status)
  {
       case NOT_EXIST:
            sleep(5);           
            break;
       case OPEN_ERROR:
            printf("%s \n",openxc_error_message);
            printf("INFO:OPENXC device error.\n");
            flag=true;
            break;
       case OPEN_SUCCESS:
            flag=true;
            break;
       case OPEN_EMPTY:
            sleep(5);
            break;
       default:
            break;
 }
  if (true == flag)
    break;
}
// system("cat openxclog.txt");
/*********************************Finish Openxc initialization*******************************************/

  if ( flag == true)
    return true;
  else
    return false;
}
bool wimax_dongle_init()
{
  
  int status;

  bool flag=false;
 
  /*********************************Wimax dongle initialization**************************************************/
  

  clean_log(DONGLELOG);
 
  system("gnome-terminal -x bash -c 'wget --http-user=admin --http-password=EiAFKt8  http://192.168.0.1/cgi/cli?$@ -o donglelog.txt |cat donglelog.txt'");
  
  while(true)
  {
    status=check_status(DONGLELOG,dongle_error_message);
    switch(status)
    {
         case NOT_EXIST:
              sleep(5);           
              break;
         case OPEN_ERROR:
<<<<<<< HEAD
              printf("INFO: wimax dongle error. Please first check if it is attached.\n");
              sleep(5);
              system(" pkill wget");
              return false;
=======
              printf("INFO: wimax dongle error.\n");
              sleep(2);
              system(" pkill wget");
              flag=true;
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
              break;
         case OPEN_SUCCESS:
              flag=true;
              break;
         case OPEN_EMPTY:
              sleep(5);
              break;
         default:
              break;
   }
    if (true == flag)
      break;
  }
  /*********************************Finish wimax dongle initialization*******************************************/
  
  if ( flag == true)
    return true;
  else
    return false;
}
bool gps_config(job *item)
{
  char comd[200];
 
  clean_log(GPSLOG);

  system("gnome-terminal -x bash -c 'sudo killall gpsd; sudo gpsd -Nn -D2 /dev/ttyACM0 2> >(tee  gpslog.txt) ' ");
  // snprintf(comd,200,,item.output);
 
  // system(comd);
  
  return true;
}
bool openxc_config(job *item)
{
  char comd[200];

  clean_log(OPENXCLOG);

 sprintf(comd,"gnome-terminal -x bash -c 'sudo openxc-dump 2> >(tee  %s/openxc.txt) ' ",item->output);
 
  system(comd);
   
  return true;
}
bool signal_status(job *item)
{ 
  char comd[200];
 
  clean_log(DONGLELOG);
  
  snprintf(comd,200,"gnome-terminal -x bash -c 'wget --http-user=admin --http-password=EiAFKt8  http://192.168.0.1/cgi/cli?showPhyStatsRx -o %s/temp.txt; cat %s/temp.txt |grep  'RSSI (dBm)'| tee -a %s/wimax.txt; 'cat %s/temp.txt |grep  'CINR (dB)' | tee -a %s/wimax.txt;'",item->output,item->output,item->output,item->output,item->output);

  system(comd);
  
  return true;
}
<<<<<<< HEAD
bool link_delay(job *item)
{
  char comd[200];

  snprintf(comd,200,"gnome-terminal -x bash -c 'iperf -c %s -p 5001 -i 1 -t 10 |tee -a %s/linkdelay.txt ;ping %s -c 10 |grep rtt |tee -a %s/linkdelay.txt",IP, item->output,IP,item->output);

  system(comd);
}
=======

>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
bool gps_stop()
{
  
  system("sudo killall gpsd");
  return true;
}
bool openxc_stop()
{
  system("sudo pkill openxc");
  return true;
}
bool wimax_dongle_stop()
{
  system(" pkill wget");
  return true;
}


bool device_config(job *item)
{
  int index=0;
  // mode[0]:gps; mode[1]:wimax dongle; mode[2]:openxc;
  //configure gps
  if( item->mode[index]== true) 
  {
    if( gps_config(item)== false) return false;
  } 
  index++;

  //configure wimax dongle
  index++;

  //configure openxc
  if( item->mode[index]== true) 
  {
    if( openxc_config(item)== false) return false;
  } 
  
  return true;
}

bool device_init()
{
  //check the availability of the devices.  

 if( gps_init() == false) return false;
 if( openxc_init() == false) return false;
 if( wimax_dongle_init() == false) return false;

 return true;
}

void device_close()
{
  gps_stop();
  openxc_stop();
  wimax_dongle_stop();
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
  int i;
  for(i=0; i<argc; i++)
  {
    if (strstr(azColName[i],"count(*)")!=NULL )
    {
      if(*argv[i]==0)
        db_table=0;
      else
        db_table=1;
    }
    printf("callback_output: %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

void database_init()
{
  sqlite3 *db;
  int rc;
  char *sql;
  char *zErrMsg = 0;
  db_table=0;


  rc= sqlite3_open(JOB_DB, &db);

  // check if the table is exist
   sql= "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='JOBS'";

   rc=sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   sleep(1);

   if( rc != SQLITE_OK || db_table==0 ){
      if(rc!= SQLITE_OK){

       printf("SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
       }else
       { // Create SQL statement
       sql = "CREATE TABLE JOBS("  \
           "ID INT PRIMARY KEY     NOT NULL," \
           "TYPE INT," \
           "PRIORITY INT," \
           "STATUS  INT," \
           "WAITER INT," \
           "NAME CHAR(10)," \
           "STARTTIME_S TEXT," \
           "STARTTIME_M TEXT," \
           "ENDTIME_S TEXT," \
           "ENDTIME_M TEXT," \
           "DES_PATH TEXT," \
           "OUT_PUT TEXT);";
       // Execute SQL statement
       rc=sqlite3_exec(db, sql, callback, 0, &zErrMsg);
       }
   }

 sqlite3_close(db);
}

static int measure(void *NotUsed, int argc, char **argv, char **azColName)
{
  int i;
  for(i=0; i<argc; i++)
  {
    if (strstr(azColName[i],"count(*)")!=NULL )
    {
      db_jobs_num=atoi(argv[i]);
    }
    printf("measure_output: %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  return 0;
}
void set_jobid(job *item)
{

  sqlite3 *db;
  int rc;
  char *sql;
  char *zErrMsg = 0;
  db_jobs_num=0;
 

  rc= sqlite3_open(JOB_DB, &db);

  
  //check the number of jobs in the database
   
  sql= "SELECT count(*) FROM JOBS";

  rc=sqlite3_exec(db, sql, measure, 0, &zErrMsg);
 
  sleep(1);

  if( rc != SQLITE_OK ){

       printf("SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   }
 sqlite3_close(db);
 item->id = db_jobs_num;
}

void insert_to_db(job *item)
{

  sqlite3 *db;
  int rc;
  char sql[2000];
  char *zErrMsg = 0;

  rc= sqlite3_open(JOB_DB, &db);

  snprintf(sql,2000,  "INSERT INTO JOBS VALUES (%d,%d,%d,%d,%d,'%s','%ld','%d','%ld','%d','%s','%s')",item->id,item->type,item->priority,item->status,item->waiter,item->name,item->start_time.second,item->start_time.millis,item->end_time.second,item->end_time.millis,item->des_path,item->output);

  printf("%s\n",sql);

  rc=sqlite3_exec(db, sql, measure, 0, &zErrMsg);
 
  sleep(1);

  if( rc != SQLITE_OK ){

       printf("SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   }else
   {
     printf("successful!\n");
   }
 sqlite3_close(db);
}

void delete_all_db()
{

  sqlite3 *db;
  int rc;
  char *sql;
  char *zErrMsg = 0;

  rc= sqlite3_open(JOB_DB, &db);

  sql="DELETE FROM JOBS";

  printf("%s\n",sql);

  rc=sqlite3_exec(db, sql, measure, 0, &zErrMsg);
 
  sleep(1);

  if( rc != SQLITE_OK ){

       printf("SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   }else
   {
     printf("successful!\n");
   }
 sqlite3_close(db);
}

void update_db(job *item, int status)
{
  sqlite3 *db;
  int rc;
  char sql[2000];
  char *zErrMsg = 0;

  rc= sqlite3_open(JOB_DB, &db);

  snprintf(sql,200,"UPDATE JOBS set STATUS=%d where ID=%d;",status,item->id);

  printf("%s\n",sql);

  rc=sqlite3_exec(db, sql, measure, 0, &zErrMsg);
 
  sleep(1);

  if( rc != SQLITE_OK ){

       printf("SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   }else
   {
     printf("successful!\n");
   }
 sqlite3_close(db);
}

void  update_job_db(){
  sqlite3 *db;
  int rc;
  char *sql;
  char *zErrMsg = 0;

  rc= sqlite3_open(JOB_DB, &db);

  sql="UPDATE JOBS set STATUS=3 where STATUS=0;";

  printf("%s\n",sql);

  rc=sqlite3_exec(db, sql, measure, 0, &zErrMsg);
 
  sleep(1);

  if( rc != SQLITE_OK ){

       printf("SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   }else
   {
     printf("successful!\n");
   }
 sqlite3_close(db);
}

void terminate_all(){

// terminate all the devices
  gps_stop();
  openxc_stop();
  wimax_dongle_stop();
  
  sleep(5);
// terminate all the threads
  cleanup_threads();
  sleep(5);
// clear the database
  stop_flag = false;
  clear_jobs();
<<<<<<< HEAD
  clear_msgs();
  clear_outputs();
=======
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
  update_job_db();

}

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
* Name: experiment_controller
* Function: control the experiments, including deployment and  processing control.
* Author: Yuehua Wang 
* Email: yuehua.research@gmail.com
*/

#include "config.h"

<<<<<<< HEAD
=======
pthread_mutex_t ex_jobs_mutex= PTHREAD_MUTEX_INITIALIZER; // experiment job list
pthread_mutex_t sys_task_mutex=PTHREAD_MUTEX_INITIALIZER; // system task list sorted by the priority 
pthread_mutex_t data_mutex=PTHREAD_MUTEX_INITIALIZER; // data list
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757

void *experiment_controller(void* arg)
{

  printf("s-2 experiment_controller\n");

  thread_set();

  while(1)
  {
    if(execute_jobs()==false)
    {
      printf("ERROR: Experiment can not be started due to the device failure!\n");
      printf("ERROR: Please check the devices\n");
    }
     // have a short time rest, then execute the next job

      sleep(5);

  }
}

<<<<<<< HEAD
=======

void store_gps_data(job *item)
{
    FILE *fp;
  
    struct timeb tmb;
    
    char buf[200];

    char filepath[200];

    get_gps(&gpsdata,buf);

    sprintf(filepath,"%s/wimax.txt",item->output);

    fp=fopen(filepath,"a");

    if(!fp)
       return;
   
    ftime(&tmb);
  
    fprintf(fp," %ld.%d %s\n",tmb.time,tmb.millitm,buf);

    fclose(fp);
}
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
/*
#define NORMAL_EXPERIMENT 0
#define EARLIEST 1 //level 2 is reserved for extension
#define MAINTENACE 3 //level 4 is reserved for extension
#define EMERGENCY_STOP 5
 * */
bool check_job_list(int type)
{
  job *temp=NULL;
  
  if (jobs_list->head == NULL)
    return false;
  else
   temp=jobs_list->head;
  
  while(temp != NULL)
  {
     if (temp->priority == type) return true;
   
     temp=temp->next;
  }

  return false;
}
//append the job to the end of the list
bool insert_jobs(job *item)
{
 

  pthread_mutex_lock(&ex_jobs_mutex);
 
  if(item == NULL)
    return false;
  
  if(jobs_list->tail !=NULL)
    (jobs_list->tail)->next=item;

  jobs_list->tail=item;

  if(jobs_list->head == NULL)
    jobs_list->head=item;
  
  jobs_num++;

  pthread_mutex_unlock(&ex_jobs_mutex);
  return true;
}

<<<<<<< HEAD
//append the msg to the end of the list

bool insert_msgs(msg *item)
{
 
  pthread_mutex_lock(&msg_mutex);
 
  if(item == NULL)
    return false;
  
  if(msgs_list->tail !=NULL)
    (msgs_list->tail)->next=item;

  msgs_list->tail=item;

  if(msgs_list->head == NULL)
    msgs_list->head=item;
  
  pthread_mutex_unlock(&msg_mutex);
  return true;
}
bool insert_outputs(msg *item)
{
 
  pthread_mutex_lock(&data_mutex);
 
  if(item == NULL)
    return false;
  
  if(outputs_list->tail !=NULL)
    (outputs_list->tail)->next=item;

  outputs_list->tail=item;

  if(outputs_list->head == NULL)
    outputs_list->head=item;
  
  pthread_mutex_unlock(&data_mutex);
  return true;
}
=======
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
void set_output(job *item)
{
  char output[20];
  struct stat st={0};

  sprintf(output,"output/job%d",item->id);

  if (stat(output,&st)== -1)
  {
  mkdir(output,0700);
  }
  printf("%s %d\n",output,strlen(output));
  item->output=malloc(strlen(output));
  memcpy(item->output,output,strlen(output));
}


//insert the job into the list according to the priority and time
bool sorted_insert(job *item)
{
  job *current;

  if(item == NULL)
    return false;
  
  pthread_mutex_lock(&ex_jobs_mutex);
 
  set_jobid(item);
  // speical case for the head
  if((jobs_list->head == NULL) || (jobs_list->head->status != PROCESSING && jobs_list->head->priority < item->priority) ||(( jobs_list->head->status != PROCESSING) &&(jobs_list->head->priority == item->priority) && (jobs_list->head->start_time.second > item->start_time.second)))
  { 
    item->next=jobs_list->head;
    jobs_list->head=item;
  }else
  {
    // locate the node before the point of insertion
    current=jobs_list->head;

    while(current->next != NULL)
    {
      if(current->next->priority > item->priority)
      {
        current= current->next;
        continue;
      }
      if(current->next->start_time.second <= item->start_time.second)
      {
        current= current->next;
        continue;
      }
      break;
    } 
     item->next=current->next;
     current->next=item;

  }

  jobs_num++;

  set_output(item);  
  insert_to_db(item);
  pthread_mutex_unlock(&ex_jobs_mutex);
  return true;
}
<<<<<<< HEAD
void outputs_list_init()
{
   outputs_list=malloc(sizeof(msgs_queue));
   outputs_list->head=NULL;
   outputs_list->tail=NULL;
}
=======
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
void jobs_list_init()
{
   jobs_list=malloc(sizeof(jobs_queue));
   jobs_list->head=NULL;
   jobs_list->tail=NULL;
   jobs_num = 0;
}

<<<<<<< HEAD
void msg_list_init()
{

   msgs_list=malloc(sizeof(msgs_queue));
   msgs_list->head=NULL;
   msgs_list->tail=NULL;
}
=======
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757

void print_jobs_list()
{
  job *temp=NULL;
  if (jobs_list->head == NULL)
    return;
  else
   temp=jobs_list->head;
  
  while(temp != NULL)
  {  printf("JOBS_LIST:\n");
     printf("job.id=%d , start_time=%ld.%d, end_time =%ld.%d\n", temp->id, temp->start_time.second,temp->start_time.millis, temp->end_time.second,temp->end_time.millis);

     temp=temp->next;
  }
}
/*
 * 
struct job { //create for every experiment commands received from the  on the OMF server
  int id;
  int type;
  int priority;
  int status; 
  char namep[10];
  char start_time[10];
  char end_time[10];
  bool mode[3]; // mode[0]:gps; mode[1]:wimax dongle; mode[2]:openxc;
  char *des_path;
  char *output;
  job *next;
};
 **/

void get_keyword_length(const char *keyword[], int *length)
{


  const char *end="NULL";
  // measure the number of keywords
  for (int i=0;;i++)
  {
   if (strstr(keyword[i],end) == NULL)
   {
     (*length)++;
    // printf("%s %d\n",keyword[i],keyword_num);
   }
   else
     break;
  }
}

bool check_description(char *filepath,const char *keyword[]){
  
  int keyword_num=0;
  int size;
  const char *end="NULL";
  FILE *fp;
  int length=500;
  char buf[length];
  

  get_keyword_length(keyword, &keyword_num);
  
  size=keyword_num;
 
  bool flags[size];
  memset(flags,false, size*sizeof(bool));

// check if all the keywords are included in the experiment description
for(int i=0; i<keyword_num;i=i+2)
{
  fp=fopen(filepath,"r");

  if(!fp)
    return NULL;

  while(true)
  {
   if (fgets(buf,length,fp)!=NULL)
   { 
     
     if((strstr(buf,keyword[i])!=NULL) && (strstr(buf,keyword[i+1])!=NULL))
    { 

      flags[i]=true;
      flags[i+1]=true;
       
      break;
     }
     
   }
   else
     break;
  }
  fclose(fp);

}

 for (int i=0; i<size;i++)
 {
    if(flags[i]==false)
      return false;
 }

return true;
}
char *get_value(char *buf,int beg,int end)
{
  
   char *ptr,*tar;
  
   ptr=strchr(buf,beg);
   tar=strchr(ptr+sizeof(char),end);

   char *value=malloc((tar-ptr-1)/sizeof(char));
   memcpy(value,ptr+sizeof(char), (tar-ptr-1)/sizeof(char));
   
   return value;

}

//append the receiver to the end of the list
bool insert_receivers(job *list,vnode *item)
{

  if(item == NULL)
    return false;
  
  if(list->receivers->tail !=NULL)
    (list->receivers->tail)->next=item;

  list->receivers->tail=item;

  if(list->receivers->head == NULL)
    list->receivers->head=item;
  
  return true;
}
void receives_init(job *item)
{
  vreceivers *list=malloc(sizeof(vreceivers));
   list->head=NULL;
   list->tail=NULL;
   item->receivers=list;
}
<<<<<<< HEAD

/*--------------------------------------------------------------------------------
 * create a new job based on the experiment description
 *--------------------------------------------------------------------------------- */
=======
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
job *new_jobs(char *filepath)
{
   
  FILE *fp;
  int length=500;
  int keyword_num=0;
  char buf[length];
  char *ptr,*tar,*value;
  int sub_string='\'';
  int separate=',';
  job *new=NULL;
  
  const char *keyword[]={"defApplication","|app|","defGroup","|node|","whenAllUp","|node|","NULL"};
  char *app[]={"exid","start time","end time","mode", "NULL"};
<<<<<<< HEAD
  char *nodetype[]={"sender","receiver","mode","oml","IP","port","NULL"};
=======
  char *nodetype[]={"sender","receiver","mode","NULL"};
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
  
  // check if the job description is valid
  if(check_description(filepath,keyword)== false)
    return NULL;
  else
    new=malloc(sizeof(job));

  printf("successful!\n");
  
  // measure the length of the keyword 
  get_keyword_length(keyword, &keyword_num);

  int  num_lines=0;
  
  fp=fopen(filepath,"r");

  if(!fp)
    return NULL;
  //initial the fields 'des_path','next' and 'receives'
  new->des_path=(char *)malloc(strlen(filepath)+1);
 
  memcpy(new->des_path,filepath,strlen(filepath));
  new->des_path[strlen(filepath)]='\0';
  printf("%s %d %s %d\n", new->des_path,strlen(new->des_path),filepath,strlen(filepath));
  new->next=NULL;

  receives_init(new);
  while(true)
  {
   if (fgets(buf,length,fp)!=NULL)
   { 
     // skip to the next line if the invalid_char '#' is included.
     if(strstr(buf,INVALID_CHAR)==NULL)
    { 
     
      // check if this line defines the application    
      if((strstr(buf,keyword[0])!=NULL) && (strstr(buf,keyword[1])!=NULL))
       { 
         // read the application
          while(true)
          {
            if (fgets(buf,length,fp)!=NULL && strstr(buf,END_CHAR)==NULL)
             { 
                // skip to the next line if the invalid_char '#' is included.
              if(strstr(buf,INVALID_CHAR)==NULL)
             {
                  // get the name 
                  if( strstr(buf,app[0])!=NULL)
                  {
                    ptr=strchr(buf,separate);
                    tar=strchr(ptr+sizeof(char),separate);

                    char *name=malloc(strlen(app[0])+(tar-ptr-1)/sizeof(char));
                    memcpy(name,app[0],strlen(app[0]));
                    memcpy(name+strlen(app[0]),ptr+sizeof(char), (tar-ptr-1)/sizeof(char));
                    memcpy(new->name,name,strlen(name));
                    free(name);
                  }
                 
                  // get the start_time
                  if( strstr(buf,app[1])!=NULL)
                  {

                    value=get_value(buf,separate,separate);
                    long int v=atol(value);

                    if( v == EARLIEST)
                    {
                      //if the experiment prefers to the earliest time to execute,
                      //then set the start time to the current time and setthe propriety to 1 
                      
                       struct timeb tmb;

                       ftime(&tmb);
                       new->start_time.second=tmb.time;
                       new->start_time.millis=tmb.millitm;
                       new->priority=0;
                   
                    }else
                    {
                       new->start_time.second=v;
                       new->start_time.millis=0;
                       new->priority=0;  
                    }
                    free(value);
                  }

                  // get the end_time
                  if( strstr(buf,app[2])!=NULL)
                  {
                    value=get_value(buf,separate,separate);
                    long int v=atol(value);
                      
                    // set the endtime to the start_time plus the during time                   
                    new->end_time.second=new->start_time.second+v;
                    new->end_time.millis=new->start_time.millis;
                    free(value);
                  }

                  
                  // get the mode
                  if( strstr(buf,app[3])!=NULL)
                  {
                    value=get_value(buf,separate,separate);
                    int v=atoi(value);
                      
                    switch(v)
                    {
                      case MODE_1:
                        new->mode[2]=true;
                        break;
                      case MODE_2:
                        new->mode[0]=true;
                        new->mode[1]=true;
                        break;
                      case MODE_3:
                        memset(new->mode,true, 3*sizeof(bool));
                        break;
                      default:
                        break;
                    }
                   // printf("%d %d %d\n",new->mode[0],new->mode[1],new->mode[2]);
                    free(value);
                  }
             }
             }else
               break;
          }
         // finish application reading
       }
    
      if((strstr(buf,keyword[2])!=NULL) && (strstr(buf,keyword[3])!=NULL))
       { 
          if (strstr(buf,nodetype[0])!=NULL ||strstr(buf,nodetype[1])!=NULL)
          {
              vnode *node=malloc(sizeof(vnode));
              // read the coordinates, e.g., x,y
              // x
  
               value=get_value(buf,'[',separate);
               node->x=atoi(value);
               free(value);

               // y
               ptr=strchr(buf,'[');
               ptr=strchr(ptr+sizeof(char),separate);
               tar=strchr(ptr+sizeof(char),']');
               
               value=malloc((tar-ptr-1)/sizeof(char));
               memcpy(value,ptr+sizeof(char), (tar-ptr-1)/sizeof(char));
  
               node->y=atoi(value);
               free(value);
               node->next=NULL;

               if (strstr(buf,nodetype[0])!=NULL)
               {
                 new->sender=node;
              //   printf("x=%d,y=%d\n",new->sender->x, new->sender->y);
               }
               if (strstr(buf,nodetype[1])!=NULL)
               {
                 insert_receivers(new,node);           
               //  printf("x=%d,y=%d\n",node->x, node->y);
               }

               // read the node
               while(true)
               {
                  if (fgets(buf,length,fp)!=NULL && strstr(buf,END_CHAR)==NULL)
                   { 
<<<<<<< HEAD
                     // skip to the next line if the invalid_char '#' is included.
                     // mode
                     if(strstr(buf,INVALID_CHAR)==NULL && strstr(buf,nodetype[2])!=NULL)
=======
                      // skip to the next line if the invalid_char '#' is included.
                      if(strstr(buf,INVALID_CHAR)==NULL && strstr(buf,nodetype[2])!=NULL)
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
                      {
               
                        value=get_value(buf,'"','"');
                        node->type=atoi(value);
<<<<<<< HEAD
                        free(value);
                        break; 
                      }
                     // oml
                     if(strstr(buf,INVALID_CHAR)==NULL && strstr(buf,nodetype[3])!=NULL)
                      {
               
                        value=get_value(buf,'"','"');

                        if(strstr(value,"true")!=NULL)
                        {
                           node->oml=1;
                        }
                        else
                           node->oml=0;
                        
                        free(value);
                        break; 
                      }
                     // ip 
                     if(strstr(buf,INVALID_CHAR)==NULL && strstr(buf,nodetype[4])!=NULL)
                      {
               
                        value=get_value(buf,'"','"');

                        memcpy(node->ip,value,strlen(value));
                       
                        node->ip[strlen(value)]='\0';
                        
                        free(value);
                        break; 
                      }
                     // port
                     if(strstr(buf,INVALID_CHAR)==NULL && strstr(buf,nodetype[4])!=NULL)
                      {
               
                        value=get_value(buf,'"','"');

                        node->port=atoi(value); 
                        
=======
                 //       printf("%d\n",node->type);
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
                        free(value);
                        break; 
                      }
                   }
               } // finish node reading
              
          }
       }
    
      if((strstr(buf,keyword[4])!=NULL) && (strstr(buf,keyword[5])!=NULL))
       { 
       
         // read the event
          while(true)
          {
            if (fgets(buf,length,fp)!=NULL && strstr(buf,END_CHAR)==NULL)
             { 
                // skip to the next line if the invalid_char '#' is included.
              if(strstr(buf,INVALID_CHAR)==NULL && strstr(buf,"wait")!=NULL)
             {
                 value=get_value(buf,'t','\n');
                 new->waiter=atoi(value);
                // printf("%d\n",new->waiter);
                 break;
             }
             }
          }
         // finish the event reading
       }
     } // jump the invalid lines
   } // end if reading the end of the file
   else
         break;
     } //end while

  //change the status
  new->status=SUBMITTED;
  fclose(fp);
  return new;
}

job *read_job()
{
  pthread_mutex_lock(&ex_jobs_mutex);

  if(jobs_list->head == NULL)
    return NULL;
  job *temp=jobs_list->head;
  temp->status=PROCESSING;

  if(temp->priority <2)
    update_db(temp, PROCESSING);

  pthread_mutex_unlock(&ex_jobs_mutex);
  return temp;
}

<<<<<<< HEAD
job *get_job()
{
  pthread_mutex_lock(&ex_jobs_mutex);

  if(jobs_list->head == NULL)
    return NULL;
  job *temp=jobs_list->head;

  pthread_mutex_unlock(&ex_jobs_mutex);
  return temp;
}

void clear_outputs()
{
   
  if(outputs_list->head == NULL)
  {
    free(outputs_list);
    return;
  }

  msg *temp=outputs_list->head;
 
  msg *next;
  while(temp->next != NULL)
  {
    next=temp->next;
  
    free(temp);

    temp=next;
  }
  
  free(temp);
  free(outputs_list);

}
void clear_msgs()
{
   
  if(msgs_list->head == NULL)
  {
    free(msgs_list);
    return;
  }

  msg *temp=msgs_list->head;
 
  msg *next;
  while(temp->next != NULL)
  {
    next=temp->next;
  
    free(temp);

    temp=next;
  }
  
  free(temp);
  free(msgs_list);

}
=======

>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
void clear_jobs()
{
   
  if(jobs_list->head == NULL)
  {
    free(jobs_list);
    return;
  }

  job *temp=jobs_list->head;
 
  job *next;
  while(temp->next != NULL)
  {
    next=temp->next;
  
    free(temp);

    temp=next;
  }
  
  free(temp);
  free(jobs_list);
  
  jobs_num=0;

}

bool delete_job()
{
  pthread_mutex_lock(&ex_jobs_mutex);
 
  if(jobs_list->head == NULL)
    return false;
  job *temp=jobs_list->head;
  
  if(temp->next != NULL)
  jobs_list->head= (jobs_list->head)->next;
  
  if(temp->priority <2)
    update_db(temp, COMPLETED);
  
<<<<<<< HEAD
 
  trans_mode(temp);
  
=======
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
  free(temp);

  pthread_mutex_unlock(&ex_jobs_mutex);
  
  jobs_num--;
  
  if(jobs_num<0)
    jobs_num=0;

  return true;
}
<<<<<<< HEAD

bool remove_output()
{
  pthread_mutex_lock(&data_mutex);
 
  if(outputs_list->head == NULL)
    return false;
  msg *temp=outputs_list->head;
  
  if(temp->next != NULL)
  outputs_list->head= (outputs_list->head)->next;
  
  free(temp);

  pthread_mutex_unlock(&data_mutex);
  
  return true;
}
bool remove_message()
{
  pthread_mutex_lock(&msg_mutex);
 
  if(msgs_list->head == NULL)
    return false;
  msg *temp=msgs_list->head;
  
  if(temp->next != NULL)
  msgs_list->head= (msgs_list->head)->next;
  
  free(temp);

  pthread_mutex_unlock(&msg_mutex);
  
  return true;
}
=======
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
void experiment(job *item)
{
  // create a new thread for experiment execution 
  ex_th_id=pthread_create(&ex_thread,NULL,data_collection,(void *)item);

  long int duration=item->start_time.second-item->end_time.second;
 
  sleep(duration);

  device_close();

  pthread_cancel(ex_thread);
}
void maintenance(job *item)
{
  if( check_all_entities == false || check_all_devices == false)
  { 
    emergency_stop();
  }
}
void emergency_stop()
{
  // change the status of the stop_flag
  stop_flag =true;

  // wait the experiment engine to reset all the resources
  sleep(5);
}
/* for reference,
#define NORMAL_EXPERIMENT 0
#define EARLIEST 1 //level 2 is reserved for extension
#define MAINTENANCE 3 //level 4 is reserved for extension
#define EMERGENCY_STOP 5
#define PROCESSING 0
#define SUBMITTED 1
#define COMPLETED 2
#define FAILED 3
 * */
//read the job from the list and execute the job based on its type
bool execute_jobs()
{
   job *current;

   current=read_job();

   if(current != NULL)
   {
     switch(current->priority)
     {
       case NORMAL_EXPERIMENT:
       case EARLIEST:

        if(device_init()==false)
          return false;
         experiment(current);
         break;
       case MAINTENANCE:
         maintenance(current);
         break;
       case EMERGENCY_STOP:
         emergency_stop();
         return false;
         break;
         default:
         break;
     }
   }
<<<<<<< HEAD
   return true; 
}

bool is_messages_list_empty()
{

  pthread_mutex_lock(&msg_mutex);

  if(msgs_list->head !=NULL)
    return false;
  else
    return true;

  pthread_mutex_unlock(&msg_mutex);

}


bool is_outputs_list_empty()
{

  pthread_mutex_lock(&data_mutex);

  if(outputs_list->head !=NULL)
    return false;
  else
    return true;

  pthread_mutex_unlock(&data_mutex);

}

bool is_data_list_empty()
{

  pthread_mutex_lock(&data_mutex);

  if(datas_list->head !=NULL)
    return false;
  else
    return true;

  pthread_mutex_unlock(&data_mutex);
}

void data_list_init()
{
   datas_list=malloc(sizeof(datas_queue));
   datas_list->head=NULL;
   datas_list->tail=NULL;
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
msg *get_output() 
{
  msg *current=NULL;

  pthread_mutex_lock(&data_mutex);

  if(outputs_list->head == NULL)
    current=NULL;
  else
    current=outputs_list->head;

  pthread_mutex_unlock(&data_mutex);

  return current;
}
=======
   //remove the job from the list and update the datebase.
   delete_job();
   return true; 
}
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757

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
* Name:  main 
* Function:
* Author: Yuehua Wang 
* Email: yuehua.research@gmail.com
*/


#include "config.h"

/* function 'cleanup' is called when the program is terminated.*/
void cleanup()
{
  printf("The experiment engine stopped. Release all the resource.\n");

  terminate_all(); 
}

void thread_init()
{
  printf("Start the experiment engine............\n");

  start_engine();
}

void setting_init()
{

  database_init();

  jobs_list_init();

}
void initialization(void)
{
  printf("********************************************************\n");
  printf("*****************Welcome to VInsight********************\n");
  printf("********************************************************\n");
  // initialize the thread subsystem
  thread_init();
  // initialize setting to defaults
  setting_init();

  //  perform any cleanup when quiting the experiment or thread
}



int main(int argc, char *argv[])
{
<<<<<<< HEAD

=======
/*
  job *temp;

  char *path="received_jobs/ex1";
  temp=new_jobs(path);
  
  if( temp !=NULL)
     printf("job.id=%d , start_time=%ld.%d, end_time =%ld.%d\n, job.name=%s\n", temp->id, temp->start_time.second,temp->start_time.millis, temp->end_time.second,temp->end_time.millis,temp->name);
  
  sorted_insert(temp);
  print_jobs_list();
  update_db(temp,1);
  delete_all_db();
*/
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
  initialization();

  while(1)
  {
    sleep(5);

    if(stop_flag == true) {
    
      terminate_all();
    }
  }

  atexit(cleanup);
}
/* start the experiment engine and initial the devices*/


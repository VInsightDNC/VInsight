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
* Name:
* Function:
* Author: Yuehua Wang 
* Email: yuehua.research@gmail.com
*/


#include "config.h"

void start_engine()
{
  
 // initial the job list and create the local database to store the experiment output
  jobs_list_init(); 
<<<<<<< HEAD
  msg_list_init();
  outputs_list_init();

  stop_flag=false;
  reserve_flag=false; 
 
 // create the threads
 th_id[0]=pthread_create(&entities[0],NULL,resource_manager,NULL);
 th_id[1]=pthread_create(&entities[1],NULL,experiment_controller,NULL);
 th_id[2]=pthread_create(&entities[2],NULL,health_monitoring,NULL);
 th_id[3]=pthread_create(&entities[3],NULL,processing_messages,NULL);

 //wait for all threads to complete
 sleep(5);
=======
 
  stop_flag=false;
  reserve_flag=false; 
 // create the threads
  
 th_id[0]=pthread_create(&entities[0],NULL,resource_manager,NULL);
 th_id[1]=pthread_create(&entities[1],NULL,experiment_controller,NULL);
 th_id[2]=pthread_create(&entities[2],NULL,health_monitoring,NULL);
 th_id[3]=pthread_create(&entities[3],NULL,listen_to_server,NULL);

 //wait for all threads to complete
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757

}

void wait_for_termination()
{
  for(int i=0;i<ENTITY_NUM;i++)
  {
     pthread_join(th_id[i], NULL);
  }
}

/*clean up and exit*/
void cleanup_threads()
{

  //destroy the mutexes
  pthread_mutex_destroy(&ex_jobs_mutex);
  pthread_mutex_destroy(&sys_task_mutex);
<<<<<<< HEAD
  pthread_mutex_destroy(&msg_mutex);
  pthread_mutex_destroy(&data_mutex);
=======
  pthread_mutex_destroy(&data_mutex);

>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
  //destroy the counter
  pthread_cond_destroy(&count_thread);
  
  //stop the threads
 for(int i=0;i<ENTITY_NUM;i++)
  pthread_cancel(entities[i]);

  pthread_cancel(ex_th_id);
  pthread_cancel(ex_trans_id);

}

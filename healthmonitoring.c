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
* Name: healthmonitoring.c 
* Function: check the health of the software and hardware of the mobile platform 
* Author: Yuehua Wang 
* Email: yuehua.research@gmail.com
*/

#include "config.h"

void *health_monitoring(void* arg)
{
  job *temp;
  
  printf("s-5 health_monitoring\n");
  
  thread_set();
  
  while(true)
  {  
 
   sleep(HEARTBEAT_INTERVAL);

   //check if there is any health monitoring job in the list

   if(heartbeat_existence()==false)
   {
     temp=(job *)malloc(sizeof(job));
     
     temp->priority=MAINTENANCE;
     
     temp->status=SUBMITTED;

     sorted_insert(temp);
   }

  }
}
/*
#define NORMAL_EXPERIMENT 0
#define EARLIEST 1 //level 2 is reserved for extension
#define MAINTENANCE 3 //level 4 is reserved for extension
#define EMERGENCY_STOP 5
#define PROCESSING 0
#define SUBMITTED 1
#define COMPLETED 2
#define FAILED 3
 * */
bool heartbeat_existence()
{
  int type=MAINTENANCE;

   if (check_job_list()==true)
     return true;
   else
     return false;
}

//check all the software
bool check_all_entities()
{

  int rc;
  
  for(int i=0; i<ENTITY_NUM;i++)
  {
    rc = pthread_kill(entities[i],0);

    if(rc == ESRCH)
    {
      printf("the specified thread did not exists or already quit/n");
      return false;
    }else if(rc == EINVAL)
    {
      printf("signal is invalid/n");
      return false;
    }else
      printf("the specified thread is alive/n");
  }
  return true;
}

//check all the hardware
bool check_all_devices()
{
  //check the devices
   if (device_init()==false) return false;

   return true;
}

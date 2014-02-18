
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
* Name: wimaxmeasurementtools.c
* Function: create tools for wimax network measurement
* Author: Yuehua Wang 
* Email: yuehua.research@gmail.com
*/

/*--------------------------------------------------------------------------------
 * wimax network measurement tools 
 * a. signal status monitoring
 * b. link throughput & delay
 *--------------------------------------------------------------------------------- */

#include "config.h"

int main(int argc, char *argv[])
{

  job *item;
  int duration;
  // read the arguments
  if(argc <5)
  {
    printf("Usage: viwimaxtool filename Server_IP Server_Port Duration\n");
    return 0;
  }
  
  //initial the wimax dongle

  if(wimax_dongle_init()==false)
  {
    printf("Please check the WiMAX dongle.\n");
    return 0;
  }

  //create a new job with several setting for wimax network measuremnt
  item=(job *)malloc(sizeof(struct JOB));

  memcpy(item->output,argv[1], strlen(argv[1]));
  memcpy(IP, argv[2],strlen(argv[2]));
  item->mode[1]=true;
  
  duration=atoi(argv[4]);

  // create a new thread for experiment execution 
  ex_th_id=pthread_create(&ex_thread,NULL,data_collection,(void *)item);

  sleep(duration);

  device_close();

  pthread_cancel(ex_thread);
}

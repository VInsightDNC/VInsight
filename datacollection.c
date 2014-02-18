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
* Name: datacollection.c
* Function: run the experiments and collect the data 
* Author: Yuehua Wang 
* Email: yuehua.research@gmail.com
*/
#include "config.h"

void *data_collection(void* arg)
{
  
  job *item=(job *)arg;

  printf("s-3 data_collection\n");

  thread_set();

  // configure the devices

  device_config(item);

  while(item->mode[0]==true ||item->mode[1]==true)
  {
     if(item->mode[0]== true){

     while(is_gps_ready()==false) {}
   
     store_gps_data(item);

     }
   
<<<<<<< HEAD
     if(item->mode[1]==true)  {
       signal_status(item);
       link_delay(item);
     }   
     sleep(1);
  }
}
=======
     if(item->mode[1]==true)  signal_status(item);
   
     sleep(1);
  }
}

>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757
void die(int sig)
{
    if (!isendwin())
    {
    	(void)mvcur(0, COLS - 1, LINES - 1, 0);

    	(void)echo();

    	(void)endwin();
    }

    (void)gps_close(&gpsdata);

    switch (sig) {
   
    case CGPS_QUIT:
        	break;
    case GPS_GONE:
        	printf("cgps: GPS hung up.\n");
        	break;
    case GPS_ERROR:
        	printf("cgps: GPS read returned error\n");
	        break;
    case GPS_TIMEOUT:
        	printf("cgps: GPS timeout\n");
        	break;
    default:
        	printf("cgps: caught signal %d\n", sig);
         	break;
    }

    /* Bye! */
    exit(0);
}


void get_gps(struct gps_data_t *gpsdata, char *scr)
{
 
 // char scr[200];
  
  errno=0;

  if (gps_read(gpsdata) == -1) {
		         
    printf( "cgps: socket error 4\n");
		    
    die(errno == 0 ? GPS_GONE : GPS_ERROR);
  } 

  
  if (gpsdata->fix.mode >= MODE_2D && isnan(gpsdata->fix.latitude) == 0 && isnan(gpsdata->fix.longitude) == 0 && isnan(gpsdata->fix.track) == 0) {

    if(gpsdata->fix.latitude <0)
        {
         sprintf(scr,"lat=-%s  ",deg_to_str(deg_type,fabs(gpsdata->fix.latitude)));        
       
        }else
        {
         sprintf(scr, "lat=%s  ",deg_to_str(deg_type,fabs(gpsdata->fix.latitude)));  
        }

	  if(gpsdata->fix.longitude <0)
      {
         snprintf(scr,200, "%s lon=-%s  ",scr, deg_to_str(deg_type,fabs(gpsdata->fix.longitude)));        
        }else
        {
         snprintf(scr,200, "%s lon=%s  ",scr, deg_to_str(deg_type,fabs(gpsdata->fix.longitude)));        
      }
    }

}

bool is_gps_ready()
{
  int option;
  int c,var;
  unsigned int flags = WATCH_ENABLE;


	altfactor = METERS_TO_FEET;
	altunits = "ft";
	speedfactor = MPS_TO_MPH;
	speedunits = "mph";

	gpsd_source_spec(NULL, &source);


  if (gps_open(source.server, source.port, &gpsdata) != 0)
  {
    printf( "cgps: no gpsd running or network error: %d, %s\n", errno, gps_errstr(errno));
    return false;
   }

  (void)signal(SIGINT, die);
  (void)signal(SIGHUP, die);

   status_timer = time(NULL);

   if (source.device != NULL)    	flags |= WATCH_DEVICE;

   (void)gps_stream(&gpsdata, flags, source.device);
	  
    if (!gps_waiting(&gpsdata, 5000000)) {
	        die(GPS_TIMEOUT);
	   } 
    else
    { 
      return true;
    }
  return false;
}

<<<<<<< HEAD


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
=======
>>>>>>> fbbb4b67a99363eb2b3b9594f4d0970862e8c757

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
* Name: omltransmission.c
* Function: transmit the experimental results to server using oml lib
* Author: Yuehua Wang 
* Email: yuehua.research@gmail.com
*/

/*--------------------------------------------------------------------------------
 *
 *--------------------------------------------------------------------------------- */

#include "omltransmission.h"

int  main(int argc, char **argv)
{

    char buffer[150];

    char po[10];
    
    char time[20];

    uint32_t intepart, flotpart;

    char *pf,*pd;
   
    int type;

    if(false == read_file(argv[1]))
    {
         printf("File is not found. Please the check the file in the directory you provided.\n");
        return 0;
    }  


    initilization(argv);

    int result =omlc_init ("openxc", &argc,(const char **) argv, NULL);
    
    if (result == -1) {
  
      fprintf (stderr, "Could not initialize OML\n");
      
      exit (1);
      
    }
    
    OmlMP *mp = omlc_add_mp ("reorder", mp_def);
    
    if (mp == NULL) {
                 
      fprintf (stderr, "Error: could not register Measurement Point 'counter'");
      
      exit (1);
      
    }
    
   FILE *lp =NULL;
 
   int filesize;

   int count =0,loop =0;
   int time_loop=0;
   while(true)
    {
    
    
      lp = fopen(argv[1],"r");
    
      fseek(lp,0L, SEEK_END);
    
      filesize = ftell(lp);

      printf("%d , %d \n",filesize, m_filesize);
      if (filesize > m_filesize)
      {

       //fseek(lp,0, SEEK_SET);
        fseek(lp,m_filesize,SEEK_SET);
         m_filesize = filesize;
        loop =0;
      }else
      {
        if(loop ==0) 
            printf("loop = %d ...",loop);
        if(loop>= m_maxloop)
            break;
        else
        {
          time_loop++;
            printf(" %d ...",time_loop);
            continue;
        }
    
      }
   omlc_start();
        
   OmlValueU values[4];
      
   omlc_zero_array(values,4);
    
   while(!feof(lp))
      {
        printf("count is %d\n",++count);
    
        memset(buffer,'\0',sizeof(buffer));
    
        printf("count is %d\n",count);
    
        fgets(buffer,120,lp);
    
         if(0 == strlen(buffer) )
         {
    
         printf("count is %d\n",strlen(buffer));
        // omlc_close();
         printf("count is %d\n",strlen(buffer));
        
        sleep(m_sleep);
        continue;
         }
         pf =&buffer[0];
         pd =&buffer[0];
    
         printf("the first sentence is %s, %d\n", buffer,strlen(buffer));
    
         if( NULL != strstr(buffer,"}"))
         {
      
          //check if the pre-defined string is contained
          type =  index_of_type(buffer); 
         
          if (type < 0)
              continue;
          else
              printf("type = %d \n",type);
          // abstract the timestamp

          stringToDouble(buffer,(long *)&intepart,(long *)&flotpart);

          pf = strstr(buffer," ");
          pd = strstr(buffer,",");
          memset(time,'\0',sizeof(time));
          memcpy(time,pf+1*sizeof(char),(pd-pf)-1*sizeof(char));
         
          memset(po,'\0',sizeof(po));
          pf =strstr(buffer, "\"value\": ");
          pf = pf+ sizeof("\"value\": ");
          pd = strstr(buffer,"}");
          memcpy(po,pf-1,pd-pf+1);
          
         char cohstr[5];
        
         sprintf(cohstr, " %d", type);
         
         double huar = (double)type; 
         
          omlc_set_long (values[0], intepart); //  omlc_set_double (values[0], time);
          
          omlc_set_long (values[1], flotpart);//tar[type]);
          
          omlc_set_uint32 (values[2],type);

         /* omlc_set_string (values[3], po);*/
  
          printf("time =%ld, type = %ld  %d, value = %s\n", (long)intepart,(long)flotpart,type, cohstr);
   
          omlc_inject (mp, values);
    
/*    
          omlc_reset_string(values[0]); // free the protentially allocated space 
    
          omlc_reset_string(values[1]);
          
          omlc_reset_string(values[2]);
      
          omlc_reset_string(values[3]);*/
         }
    
      }
    
      printf("program ends\n");
    
      fclose(lp);
  }

 return 0;
} 
void initilization( char *arv[])
{
    m_filesize = 0;
    m_filelength =0;
    m_accuracy = pow(10,6);
    m_interval = atoi(arv[2]);
    int i=0;

    while(con[i]!= NULL)
    {
       i++;
    }
    
    m_conlength =--i;
}
bool read_file( char *file_name)
{
  FILE *lp =NULL;
  int filesize;

  if (access(file_name,0) == -1)
  {

     return false;
  }
  else
      lp = fopen(file_name,"r");

    fseek(lp,0, SEEK_END);

    filesize = ftell(lp);

    if (filesize >m_filesize)
        return true;
    else 
        return false;

    //printf("file size = %d byte",filesize);

    //return true;
}

int index_of_type(char *buf)
{
    int count =0;

    while(count < m_conlength)
     {

         if (NULL != strstr(buf,con[count])) 
           {
               break;
           } else
               count++;
        
     }
    if(count >= m_conlength)
        count = -1;

    return count;

}

void  stringToDouble(char *po, long *intp, long *flop)
{
   double value =-1;
   double second =-1;
   char var[20];
   char *front,*end;
   front = po;
   end = po;

   memset(var,0, sizeof(var));
   front = strstr(po," ");
   end = strstr(po, ".");
   memcpy(var,front,(end-front)/sizeof(char));
   value = atol(var);   
   *intp = value;

   printf(" var = %s, value= %ld \n",var,*intp);

   front =strstr(po,",");
   memcpy(var,end+1*sizeof(char),(front-end)/sizeof(char));
   second = atol(var);
   value = value*m_accuracy+second;

   *flop = second;
   printf("po = %s, var =%s , value= %ld, %ld\n",po, var,*intp, *flop); 
  
}

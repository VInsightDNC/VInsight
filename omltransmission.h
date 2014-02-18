
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
* Name: omltransmission.h
* Function: head file of the file 'omltransmission.c'
* Author: Yuehua Wang 
* Email: yuehua.research@gmail.com
*/

#ifndef __oml_transmission_H_
#define __oml_transmission_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include "include/client/oml2/omlc.h"

//********************************************************************************
// datatype rename
//********************************************************************************

typedef unsigned char  uint8;                  
typedef signed   char  int8;                    
typedef unsigned int   uint16;                   
typedef signed   int   int16;                       
typedef unsigned long  uint32;                     
typedef signed   long  int32;                     

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

bool read_file(char *file_name);
int index_of_type(char *buf);
void initilization(char *arv[]);
void  stringToDouble(char *po, long *intp, long *flop);
#endif

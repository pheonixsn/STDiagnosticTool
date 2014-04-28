/**********************************************************************************************
-----------------------------------------------------------------------------------------------
Name :                  VSV_xmlApi.h 
Description :          convert xml files to algorithm data struct 
Product Number :        
Revision :              V1.0.0          
Module :                global
System :                
Language :              ANSI C
Develop Environment :   SlickEdit V17.0.0
Running Environment :   Debian V6.0.6
------------------------------------------------------------------------------------------------
版权声明
------------------------------------------------------------------------------------------------
Creation Data :             <5/17/2013   17:43:46>
Chief Editor :              <sunnan>
Participant :               <参与者>
Audit :                     <检查者>
Edit Log :                  <编辑记录>

Release :                   <>

Copyright (C) 2013 BendWeaver - All Rights Reserved
------------------------------------------------------------------------------------------------
***********************************************************************************************/

#ifndef __VSV_XMLAPI_H_INCL__
#define __VSV_XMLAPI_H_INCL__

//
//
#include "./algo_smoketrace_priv.h"





#ifdef __cplusplus
extern "C"
{
#endif
//
int VSV_initXml();

int VSV_destroyXml();

int VSV_getLicense();

int VSV_getInitParam(const char* str, int str_size, VSV_Channel * config_chan );

int VSV_getNewImageParam(const char* str, int str_size, VSV_NewimageConfig * config);

int VSV_setTestResult(char* str, int * str_size, const VSV_ProcessResult * config);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif // __VSV_XMLAPI_H_INCL__


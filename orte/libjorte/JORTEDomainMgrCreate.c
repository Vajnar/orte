/* JORTEDomainMgrCreate.c  */

/**
  * This code provides conversion between JAVA a C environments.
  * The C functions are calling here and results are send to JAVA
  * native functions. It uses the header pregenerated by JAVA
  * (by command 'javah -jni class_with_native_function')
  *
  * @author Lukas Pokorny (lukas_pokorny@centrum.cz)
  * @author CTU FEE Prague - Department of Control Engineering (dce.felk.cvut.cz)
  * @author Project ORTE - OCERA Real Time Ethernet (www.ocera.org)
  * @author dedication to Kj
  * @version 0.1
  *
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  */


// origin orte headers
#include "orte.h"
// pregenerated header
#include "jorte/org_ocera_orte_DomainMgr.h"
#include "jorte/4all.h"

/* ****************************** *
 *  create default manager domain *
 * ****************************** */
JNIEXPORT jint JNICALL
Java_org_ocera_orte_DomainMgr_jORTEDomainDefaultMgrCreate
(JNIEnv *env, jclass cls, jint jdomain, jboolean susp)
{
  jint       d;

  // call ORTE function
  d = (jint) ORTEDomainMgrCreate((int)jdomain,
                                 NULL,
                                 NULL,
                                 (Boolean) susp);
  if(d == 0)
  {
    printf(":!c: creating mgrDomain failed! \n");
    return 0;
  }
  #ifdef TEST_STAGE
     printf(":c: mgrDomain created.. \n");
  #endif
  return (d);
}


/* *************************** *
 *  create user manager domain *
 * *************************** */
JNIEXPORT jint JNICALL
Java_org_ocera_orte_DomainMg_jORTEDomainMgrCreate
(JNIEnv *env, jclass cls, jint jdomain, jint propHandle,
 jint eventsHandle, jboolean susp)
{
  jint        d;

  // call ORTE function
  d = (jint) ORTEDomainMgrCreate((int)jdomain,
                                 (ORTEDomainProp *) propHandle,
                                 (ORTEDomainAppEvents *) eventsHandle,
                                 (Boolean) susp);
  if(d == 0)
  {
    printf(":!c: creating mgrDomain failed! \n");
    return 0;
  }
  #ifdef TEST_STAGE
     printf(":c: mgrDomain created.. \n");
  #endif
  return (d);
}
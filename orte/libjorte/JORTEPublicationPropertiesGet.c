/* JORTEPublicationPropertiesGet.c */

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

#include <string.h>
#include <stdlib.h>
// library header file's path
#include "orte.h"
// enable TEST_STAGE run level
#include "jorte/4all.h"
#include "jorte/jorte_protos_api.h"
// pregenerated header
#include "jorte/org_ocera_orte_Publication.h"


JNIEXPORT jobject JNICALL
Java_org_ocera_orte_Publication_jORTEPublicationPropertiesGet
  (JNIEnv *env, jobject obj, jlong j_appDomain_handle)
{
  // jni types
  jclass         cls_pp   = NULL; // PublProp class
  jclass         cls_ntpT = NULL; // NtpTime class
  jobject        obj_pp   = NULL; // instance of PublProp
  jobject        obj_ntpT = NULL; // instance of NtpTime
  jfieldID       fid      = NULL;
  jmethodID      mid;
  jboolean       jbool = 0;
  //
  int            b = 0;
  int            flag_ok = 0;
  ORTEPublProp   pp;
  ORTEPublProp  *publ_prop = &pp;

  // calling original orte function
  #ifdef TEST_STAGE
  printf(":c: ORTEPublicationPropertiesGet() called.. \n");
  #endif

  // create new PublProps instance and set its fields
  do {
    // call ORTE function
    b = ORTEPublicationPropertiesGet((ORTEPublication *)j_appDomain_handle,
				     publ_prop);
    if (b == ORTE_BAD_HANDLE) {
      printf(":!c: PublicationPropertiesGet() failed! [bad pub handle] \n");
      break;
    }
    // find class
    cls_pp = findClass(env, "org.ocera.orte.types.PublProp");
    if (cls_pp == 0) {
      #ifdef TEST_STAGE
      printf(":!c: cls_pp = NULL \n");
      #endif
      break;
    }
    // call object constructor
    mid = (*env)->GetMethodID(env, cls_pp, "<init>", "()V");
    if (mid == 0) {
      #ifdef TEST_STAGE
      printf(":!c: mid = NULL \n");
      #endif
      break;
    }
    // new object
    obj_pp = (*env)->NewObject(env, cls_pp, mid);
    if (obj_pp == 0) {
      #ifdef TEST_STAGE
      printf(":!c: obj_pp = NULL \n");
      #endif
      break;
    }
    #ifdef TEST_STAGE
    printf(":c: instance of 'org.ocera.orte.types.PublProp' created..\n");
    #endif
    // ///////////////////////////////////////////////
    // setting object's fields
    /////////////////////////////////////////////////
    // set topic
    if (!setTopic(env, cls_pp, obj_pp, (const char *)publ_prop->topic)) {
      #ifdef TEST_STAGE
      printf(":!c: setTopic() failed! \n");
      #endif
      break;
    }
    /////////////////////////////////////////////////
    // set type
    if (!setType(env, cls_pp, obj_pp, (const char *)publ_prop->typeName)) {
      #ifdef TEST_STAGE
      printf(":!c: setType() failed! \n");
      #endif
      break;
    }
    /////////////////////////////////////////////////
    // fieldID - typeChecksum
    fid = (*env)->GetFieldID(env,
			     cls_pp,
			     "typeChecksum",
			     "I");
    if (fid == 0) {
      #ifdef TEST_STAGE
      printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    (*env)->SetIntField(env,
			obj_pp,
			fid,
			(jint)publ_prop->typeChecksum);
    /////////////////////////////////////////////////
    // fieldID - expectsAck
    fid = (*env)->GetFieldID(env,
			     cls_pp,
			     "expectsAck",
			     "Z");
    if (fid == 0) {
      #ifdef TEST_STAGE
      printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    if (publ_prop->expectsAck == ORTE_FALSE)
      jbool = 0;
    else
      jbool = 1;
    (*env)->SetBooleanField(env,
			    obj_pp,
			    fid,
			    jbool);
    /////////////////////////////////////////////////
    // fieldID - persistence
    cls_ntpT = findClass(env, "org.ocera.orte.types.NtpTime");
    if (cls_ntpT == 0) {
      #ifdef TEST_STAGE
      printf(":!c: cls_ntpT = NULL \n");
      #endif
      break;
    }
    // call object constructor
    mid = (*env)->GetMethodID(env, cls_ntpT, "<init>", "(IJ)V");
    if (mid == 0) {
      #ifdef TEST_STAGE
      printf(":!c: mid = NULL \n");
      #endif
      break;
    }
    // new object
    obj_ntpT = (*env)->NewObject(env,
				 cls_ntpT,
				 mid,
				 (jint)publ_prop->persistence.seconds,
				 (jlong)publ_prop->persistence.fraction);
    if (obj_ntpT == 0) {
      #ifdef TEST_STAGE
      printf(":!c: obj_ntpT = NULL \n");
      #endif
      break;
    }
    #ifdef TEST_STAGE
    printf(":c: instance of 'org.ocera.orte.types.NtpTime' created..\n");
    #endif
    // set 'PublProp' NtpTime's field
    fid = (*env)->GetFieldID(env,
			     cls_pp,
			     "persistence",
			     "Lorg/ocera/orte/types/NtpTime;");
    if (fid == 0) {
      #ifdef TEST_STAGE
      printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    (*env)->SetObjectField(env,
			   obj_pp,
			   fid,
			   obj_ntpT);
    /////////////////////////////////////////////////
    // fieldID - HBNornalRate
    // cls_ntpT and obj_ntpT already readed!!
    // new object
    obj_ntpT = (*env)->NewObject(env,
				 cls_ntpT,
				 mid,
				 (jint)publ_prop->HBNornalRate.seconds,
				 (jlong)publ_prop->HBNornalRate.fraction);
    if (obj_ntpT == 0) {
      #ifdef TEST_STAGE
      printf(":!c: obj_ntpT = NULL \n");
      #endif
      break;
    }
    #ifdef TEST_STAGE
    printf(":c: instance of 'org.ocera.orte.types.NtpTime' created..\n");
    #endif
    // set 'PublProp' NtpTime's field
    fid = (*env)->GetFieldID(env,
			     cls_pp,
			     "HBNornalRate",
			     "Lorg/ocera/orte/types/NtpTime;");
    if (fid == 0) {
      #ifdef TEST_STAGE
      printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    (*env)->SetObjectField(env,
			   obj_pp,
			   fid,
			   obj_ntpT);
    /////////////////////////////////////////////////
    // fieldID - HBCQLRate
    // cls_ntpT and obj_ntpT already readed!!
    // new object
    obj_ntpT = (*env)->NewObject(env,
				 cls_ntpT,
				 mid,
				 (jint)publ_prop->HBCQLRate.seconds,
				 (jlong)publ_prop->HBCQLRate.fraction);
    if (obj_ntpT == 0) {
      #ifdef TEST_STAGE
      printf(":!c: obj_ntpT = NULL \n");
      #endif
      break;
    }
    #ifdef TEST_STAGE
    printf(":c: instance of 'org.ocera.orte.types.NtpTime' created..\n");
    #endif
    // set 'PublProp' NtpTime's field
    fid = (*env)->GetFieldID(env,
			     cls_pp,
			     "HBCQLRate",
			     "Lorg/ocera/orte/types/NtpTime;");
    if (fid == 0) {
      #ifdef TEST_STAGE
      printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    (*env)->SetObjectField(env,
			   obj_pp,
			   fid,
			   obj_ntpT);
    /////////////////////////////////////////////////
    // fieldID - HBCQLRate
    // cls_ntpT and obj_ntpT already readed!!
    // new object
    obj_ntpT = (*env)->NewObject(env,
				 cls_ntpT,
				 mid,
				 (jint)publ_prop->maxBlockTime.seconds,
				 (jlong)publ_prop->maxBlockTime.fraction);
    if (obj_ntpT == 0) {
      #ifdef TEST_STAGE
      printf(":!c: obj_ntpT = NULL \n");
      #endif
      break;
    }
    #ifdef TEST_STAGE
    printf(":c: instance of 'org.ocera.orte.types.NtpTime' created..\n");
    #endif
    // set 'PublProp' NtpTime's field
    fid = (*env)->GetFieldID(env,
			     cls_pp,
			     "maxBlockTime",
			     "Lorg/ocera/orte/types/NtpTime;");
    if (fid == 0) {
      #ifdef TEST_STAGE
      printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    (*env)->SetObjectField(env,
			   obj_pp,
			   fid,
			   obj_ntpT);
    /////////////////////////////////////////////////
    // fieldID - reliabilityOffered
    fid = (*env)->GetFieldID(env,
			     cls_pp,
			     "reliabilityOffered",
			     "J");
    if (fid == 0) {
      #ifdef TEST_STAGE
      printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    (*env)->SetLongField(env,
			 obj_pp,
			 fid,
			 (jlong)publ_prop->reliabilityOffered);
    /////////////////////////////////////////////////
    // fieldID - sendQueueSize
    fid = (*env)->GetFieldID(env,
			     cls_pp,
			     "sendQueueSize",
			     "J");
    if (fid == 0) {
      #ifdef TEST_STAGE
      printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    (*env)->SetLongField(env,
			 obj_pp,
			 fid,
			 (jlong)publ_prop->sendQueueSize);
    /////////////////////////////////////////////////
    // fieldID - strength
    fid = (*env)->GetFieldID(env,
			     cls_pp,
			     "strength",
			     "I");
    if (fid == 0) {
      #ifdef TEST_STAGE
      printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    (*env)->SetIntField(env,
			obj_pp,
			fid,
			(jint)publ_prop->strength);
    /////////////////////////////////////////////////
    // fieldID - criticalQueueLevel
    fid = (*env)->GetFieldID(env,
			     cls_pp,
			     "criticalQueueLevel",
			     "J");
    if (fid == 0) {
      #ifdef TEST_STAGE
      printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    (*env)->SetLongField(env,
			 obj_pp,
			 fid,
			 (jlong)publ_prop->criticalQueueLevel);
    /////////////////////////////////////////////////
    // fieldID - HBMaxRetries
    fid = (*env)->GetFieldID(env,
			     cls_pp,
			     "HBMaxRetries",
			     "J");
    if (fid == 0) {
      #ifdef TEST_STAGE
      printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    (*env)->SetLongField(env,
			 obj_pp,
			 fid,
			 (jlong)publ_prop->HBMaxRetries);
    // set flag
    flag_ok = 1;
  } while (0);

  if (flag_ok == 0) {
    return NULL;
  }

  return obj_pp;

}

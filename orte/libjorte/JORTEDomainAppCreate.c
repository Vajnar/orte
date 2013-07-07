/* JORTEDomainAppCreate.c */

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

#include <stdlib.h>
// origin orte headers
#include "orte.h"
// pregenerated header
#include "jorte/org_ocera_orte_DomainApp.h"
// enable TEST_STAGE run level
#include "jorte/4all.h"
// new data types
#include "jorte/jorte_typedefs_defines.h"
#include "jorte/jorte_protos_api.h"

// /////////////////////////////////////////////////////////////////////
//  public void onRegFail()
// /////////////////////////////////////////////////////////////////////
Boolean
onRegFail(void *param)
{
// ///////////////////////////////// SPOLECNA CAST //
  JavaVM          *jvm = NULL;
  JNIEnv          *env = NULL; // local reference
  jclass           cls;
  jmethodID        mid;
  //
  JORTEDomainEventsContext_t   *domain_events_cont = (JORTEDomainEventsContext_t*) param;
  int flag_ok = 0;

  #ifdef TEST_STAGE
      printf(":c: event func. 'onRegFail()' called.. \n");
  #endif

  do
  {
// ///////////////////////////////// SPOLECNA CAST //
    if(domain_events_cont->jvm == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: jvm = NULL! \n");
     #endif
     break;
    }
    jvm = domain_events_cont->jvm;
    // get env
    (*jvm)->AttachCurrentThread(jvm, (void **)&env, NULL);
    if(env == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: env = NULL! \n");
     #endif
     break;
    }
    // find class
    cls = findClass(env, "org.ocera.orte.types.DomainEvents");
    if(cls == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: cls = NULL! \n");
     #endif
     break;
    }
// ///////////////////////////////// SPOLECNA CAST //
    // get method ID
    mid = (*env)->GetMethodID(env,
                              cls,
                              "onRegFail",
                              "()V");
    if(mid == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: mid = NULL! \n");
     #endif
     break;
    }
    // call method
    (*env)->CallVoidMethod(env,
                           domain_events_cont->obj_de,
                           mid);
    flag_ok = 1;
  } while(0);
  // while broken
  if(flag_ok)
  {
    if((*jvm)->DetachCurrentThread(jvm) != 0)
    {
      printf(":c!: DetachCurrentThread fault! \n");
      return  ORTE_FALSE;
    }
  }

  return ORTE_TRUE;
}


// /////////////////////////////////////////////////////////////////////
//  Event - public void onMgrNew()
// /////////////////////////////////////////////////////////////////////
Boolean
onMgrNew(const struct ORTEAppInfo *appInfo, void *param)
{
// ///////////////////////////////// SPOLECNA CAST //
  JavaVM          *jvm = NULL;
  JNIEnv          *env = NULL; // local reference
  jclass           cls;
  jobject          obj_ainfo;
  jmethodID        mid;
  //
  JORTEDomainEventsContext_t   *domain_events_cont = (JORTEDomainEventsContext_t*) param;
  int flag_ok = 0;

  #ifdef TEST_STAGE
      printf(":c: event func. 'onMgrNew()' called.. \n");
  #endif

  do
  {
// ///////////////////////////////// SPOLECNA CAST //
    if(domain_events_cont->jvm == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: jvm = NULL! \n");
     #endif
     break;
    }
    jvm = domain_events_cont->jvm;
    // get env
    (*jvm)->AttachCurrentThread(jvm, (void **)&env, NULL);
    if(env == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: env = NULL! \n");
     #endif
     break;
    }
    // find class
    cls = findClass(env, "org.ocera.orte.types.DomainEvents");
    if(cls == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: cls = NULL! \n");
     #endif
     break;
    }
    // create AppInfo instance
    obj_ainfo = createAppInfo(env, appInfo);
    if(obj_ainfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_ainfo = NULL! \n");
     #endif
     break;
    }
// ///////////////////////////////// SPOLECNA CAST //
    // get method ID
    mid = (*env)->GetMethodID(env,
                              cls,
                              "onMgrNew",
                              "(Lorg/ocera/orte/types/AppInfo;)V");
    if(mid == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: mid = NULL! \n");
     #endif
     break;
    }
    // call method
    (*env)->CallVoidMethod(env,
                           domain_events_cont->obj_de,
                           mid,
                           obj_ainfo);
    flag_ok = 1;
  } while(0);
  // while broken
  if(flag_ok)
  {
    if((*jvm)->DetachCurrentThread(jvm) != 0)
    {
      printf(":c!: DetachCurrentThread fault! \n");
      return  ORTE_FALSE;
    }
  }

  return ORTE_TRUE;
}


// /////////////////////////////////////////////////////////////////////
//  Event - public void onMgrDelete()
// /////////////////////////////////////////////////////////////////////
Boolean
onMgrDelete(const struct ORTEAppInfo *appInfo, void *param)
{
// ///////////////////////////////// SPOLECNA CAST //
  JavaVM          *jvm = NULL;
  JNIEnv          *env = NULL; // local reference
  jclass           cls;
  jobject          obj_ainfo;
  jmethodID        mid;
  //
  JORTEDomainEventsContext_t   *domain_events_cont = (JORTEDomainEventsContext_t*) param;
  int flag_ok = 0;

  #ifdef TEST_STAGE
      printf(":c: event func. 'onMgrDelete()' called.. \n");
  #endif

  do
  {
// ///////////////////////////////// SPOLECNA CAST //
    if(domain_events_cont->jvm == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: jvm = NULL! \n");
     #endif
     break;
    }
    jvm = domain_events_cont->jvm;
    // get env
    (*jvm)->AttachCurrentThread(jvm, (void **)&env, NULL);
    if(env == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: env = NULL! \n");
     #endif
     break;
    }
    // find class
    cls = findClass(env, "org.ocera.orte.types.DomainEvents");
    if(cls == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: cls = NULL! \n");
     #endif
     break;
    }
    // create AppInfo instance
    obj_ainfo = createAppInfo(env, appInfo);
    if(obj_ainfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_ainfo = NULL! \n");
     #endif
     break;
    }
// ///////////////////////////////// SPOLECNA CAST //
    // get method ID
    mid = (*env)->GetMethodID(env,
                              cls,
                              "onMgrDelete",
                              "(Lorg/ocera/orte/types/AppInfo;)V");
    if(mid == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: mid = NULL! \n");
     #endif
     break;
    }
    // call method
    (*env)->CallVoidMethod(env,
                           domain_events_cont->obj_de,
                           mid,
                           obj_ainfo);
    flag_ok = 1;
  } while(0);
  // while broken
  if(flag_ok)
  {
    if((*jvm)->DetachCurrentThread(jvm) != 0)
    {
      printf(":c!: DetachCurrentThread fault! \n");
      return  ORTE_FALSE;
    }
  }

  return ORTE_TRUE;
}



// /////////////////////////////////////////////////////////////////////
//  Event - onAppRemoteNew
// /////////////////////////////////////////////////////////////////////
Boolean
onAppRemoteNew(const struct ORTEAppInfo *appInfo, void *param)
{
// ///////////////////////////////// SPOLECNA CAST //
  JavaVM          *jvm = NULL;
  JNIEnv          *env = NULL; // local reference
  jclass           cls;
  jobject          obj_ainfo;
  jmethodID        mid;
  //
  JORTEDomainEventsContext_t   *domain_events_cont = (JORTEDomainEventsContext_t*) param;
  int flag_ok = 0;

  #ifdef TEST_STAGE
      printf(":c: event func. 'onAppRemoteNew()' called.. \n");
  #endif

  do
  {
// ///////////////////////////////// SPOLECNA CAST //
    if(domain_events_cont->jvm == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: jvm = NULL! \n");
     #endif
     break;
    }
    jvm = domain_events_cont->jvm;
    // get env
    (*jvm)->AttachCurrentThread(jvm, (void **)&env, NULL);
    if(env == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: env = NULL! \n");
     #endif
     break;
    }
    // find class
    cls = findClass(env, "org.ocera.orte.types.DomainEvents");
    if(cls == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: cls = NULL! \n");
     #endif
     break;
    }
    // create AppInfo instance
    obj_ainfo = createAppInfo(env, appInfo);
    if(obj_ainfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_ainfo = NULL! \n");
     #endif
     break;
    }
// ///////////////////////////////// SPOLECNA CAST //

    // get method ID
    mid = (*env)->GetMethodID(env,
                              cls,
                              "onAppRemoteNew",
                              "(Lorg/ocera/orte/types/AppInfo;)V");
    if(mid == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: mid = NULL! \n");
     #endif
     break;
    }
    // call method
    (*env)->CallVoidMethod(env,
                           domain_events_cont->obj_de,
                           mid,
                           obj_ainfo);
    flag_ok = 1;
  } while(0);
  // while broken
  if(flag_ok)
  {
    if((*jvm)->DetachCurrentThread(jvm) != 0)
    {
      printf(":c!: DetachCurrentThread fault! \n");
      return  ORTE_FALSE;
    }
  }

  return ORTE_TRUE;
}


// /////////////////////////////////////////////////////////////////////
//  public void onAppDelete() { }
// /////////////////////////////////////////////////////////////////////
Boolean
onAppDelete(const struct ORTEAppInfo *appInfo, void *param)
{
// ///////////////////////////////// SPOLECNA CAST //
  JavaVM          *jvm = NULL;
  JNIEnv          *env = NULL; // local reference
  jclass           cls;
  jobject          obj_ainfo;
  jmethodID        mid;
  //
  JORTEDomainEventsContext_t   *domain_events_cont = (JORTEDomainEventsContext_t*) param;
  int flag_ok = 0;

  #ifdef TEST_STAGE
      printf(":c: event func. 'onAppDelete()' called.. \n");
  #endif

  do
  {
// ///////////////////////////////// SPOLECNA CAST //
    if(domain_events_cont->jvm == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: jvm = NULL! \n");
     #endif
     break;
    }
    jvm = domain_events_cont->jvm;
    // get env
    (*jvm)->AttachCurrentThread(jvm, (void **)&env, NULL);
    if(env == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: env = NULL! \n");
     #endif
     break;
    }
    // find class
    cls = findClass(env, "org.ocera.orte.types.DomainEvents");
    if(cls == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: cls = NULL! \n");
     #endif
     break;
    }
    // create AppInfo instance
    obj_ainfo = createAppInfo(env, appInfo);
    if(obj_ainfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_ainfo = NULL! \n");
     #endif
     break;
    }
// ///////////////////////////////// SPOLECNA CAST //
    // get method ID
    mid = (*env)->GetMethodID(env,
                              cls,
                              "onAppDelete",
                              "(Lorg/ocera/orte/types/AppInfo;)V");
    if(mid == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: mid = NULL! \n");
     #endif
     break;
    }
    // call method
    (*env)->CallVoidMethod(env,
                           domain_events_cont->obj_de,
                           mid,
                           obj_ainfo);
    flag_ok = 1;
  } while(0);
  // while broken
  if(flag_ok)
  {
    if((*jvm)->DetachCurrentThread(jvm) != 0)
    {
      printf(":c!: DetachCurrentThread fault! \n");
      return  ORTE_FALSE;
    }
  }

  return ORTE_TRUE;
}


// /////////////////////////////////////////////////////////////////////
//  public void onPubRemoteNew()
// /////////////////////////////////////////////////////////////////////
Boolean
onPubRemoteNew(const struct ORTEAppInfo *appInfo,
               const struct ORTEPubInfo *pubInfo,
               void *param)
{
// ///////////////////////////////// SPOLECNA CAST //
  JavaVM          *jvm = NULL;
  JNIEnv          *env = NULL; // local reference
  jclass           cls;
  jobject          obj_ainfo;
  jobject          obj_pinfo;
  jmethodID        mid;
  //
  JORTEDomainEventsContext_t   *domain_events_cont = (JORTEDomainEventsContext_t*) param;
  int flag_ok = 0;

  #ifdef TEST_STAGE
      printf(":c: event func. 'onPubRemoteNew()' called.. \n");
  #endif

  do
  {
// ///////////////////////////////// SPOLECNA CAST //
    if(domain_events_cont->jvm == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: jvm = NULL! \n");
     #endif
     break;
    }
    jvm = domain_events_cont->jvm;
    // get env
    (*jvm)->AttachCurrentThread(jvm, (void **)&env, NULL);
    if(env == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: env = NULL! \n");
     #endif
     break;
    }
    // find class
    cls = findClass(env, "org.ocera.orte.types.DomainEvents");
    if(cls == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: cls = NULL! \n");
     #endif
     break;
    }
    // create AppInfo instance
    obj_ainfo = createAppInfo(env, appInfo);
    if(obj_ainfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_ainfo = NULL! \n");
     #endif
     break;
    }
    // create PubInfo instance
    obj_pinfo = createPubInfo(env, pubInfo);
    if(obj_pinfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_pinfo = NULL! \n");
     #endif
     break;
    }
// ///////////////////////////////// SPOLECNA CAST //
    // get method ID
    mid = (*env)->GetMethodID(env,
                              cls,
                              "onPubRemoteNew",
                              "(Lorg/ocera/orte/types/AppInfo;Lorg/ocera/orte/types/PubInfo;)V");
    if(mid == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: mid = NULL! \n");
     #endif
     break;
    }
    // call method
    (*env)->CallVoidMethod(env,
                           domain_events_cont->obj_de,
                           mid,
                           obj_ainfo,
                           obj_pinfo);
    flag_ok = 1;
  } while(0);
  // while broken
  if(flag_ok)
  {
    if((*jvm)->DetachCurrentThread(jvm) != 0)
    {
      printf(":c!: DetachCurrentThread fault! \n");
      return  ORTE_FALSE;
    }
  }

  return ORTE_TRUE;
}


// /////////////////////////////////////////////////////////////////////
//public void onPubRemoteChanged()
// /////////////////////////////////////////////////////////////////////
Boolean
onPubRemoteChanged(const struct ORTEAppInfo *appInfo,
                   const struct ORTEPubInfo *pubInfo,
                   void *param)
{
// ///////////////////////////////// SPOLECNA CAST //
  JavaVM          *jvm = NULL;
  JNIEnv          *env = NULL; // local reference
  jclass           cls;
  jobject          obj_ainfo;
  jobject          obj_pinfo;
  jmethodID        mid;
  //
  JORTEDomainEventsContext_t   *domain_events_cont = (JORTEDomainEventsContext_t*) param;
  int flag_ok = 0;

  #ifdef TEST_STAGE
      printf(":c: event func. 'onPubRemoteChanged()' called.. \n");
  #endif

  do
  {
// ///////////////////////////////// SPOLECNA CAST //
    if(domain_events_cont->jvm == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: jvm = NULL! \n");
     #endif
     break;
    }
    jvm = domain_events_cont->jvm;
    // get env
    (*jvm)->AttachCurrentThread(jvm, (void **)&env, NULL);
    if(env == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: env = NULL! \n");
     #endif
     break;
    }
    // find class
    cls = findClass(env, "org.ocera.orte.types.DomainEvents");
    if(cls == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: cls = NULL! \n");
     #endif
     break;
    }
    // create AppInfo instance
    obj_ainfo = createAppInfo(env, appInfo);
    if(obj_ainfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_ainfo = NULL! \n");
     #endif
     break;
    }
    // create PubInfo instance
    obj_pinfo = createPubInfo(env, pubInfo);
    if(obj_pinfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_pinfo = NULL! \n");
     #endif
     break;
    }
// ///////////////////////////////// SPOLECNA CAST //
    // get method ID
    mid = (*env)->GetMethodID(env,
                              cls,
                              "onPubRemoteChanged",
                              "(Lorg/ocera/orte/types/AppInfo;Lorg/ocera/orte/types/PubInfo;)V");
    if(mid == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: mid = NULL! \n");
     #endif
     break;
    }
    // call method
    (*env)->CallVoidMethod(env,
                           domain_events_cont->obj_de,
                           mid,
                           obj_ainfo,
                           obj_pinfo);
    flag_ok = 1;
  } while(0);
  // while broken
  if(flag_ok)
  {
    if((*jvm)->DetachCurrentThread(jvm) != 0)
    {
      printf(":c!: DetachCurrentThread fault! \n");
      return  ORTE_FALSE;
    }
  }

  return ORTE_TRUE;
}




// /////////////////////////////////////////////////////////////////////
//  public void onPubDelete()
// /////////////////////////////////////////////////////////////////////
Boolean
onPubDelete(const struct ORTEAppInfo *appInfo,
            const struct ORTEPubInfo *pubInfo,
            void *param)
{
// ///////////////////////////////// SPOLECNA CAST //
  JavaVM          *jvm = NULL;
  JNIEnv          *env = NULL; // local reference
  jclass           cls;
  jobject          obj_ainfo;
  jobject          obj_pinfo;
  jmethodID        mid;
  //
  JORTEDomainEventsContext_t   *domain_events_cont = (JORTEDomainEventsContext_t*) param;
  int flag_ok = 0;

  #ifdef TEST_STAGE
      printf(":c: event func. 'onPubDelete()' called.. \n");
  #endif

  do
  {
// ///////////////////////////////// SPOLECNA CAST //
    if(domain_events_cont->jvm == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: jvm = NULL! \n");
     #endif
     break;
    }
    jvm = domain_events_cont->jvm;
    // get env
    (*jvm)->AttachCurrentThread(jvm, (void **)&env, NULL);
    if(env == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: env = NULL! \n");
     #endif
     break;
    }
    // find class
    cls = findClass(env, "org.ocera.orte.types.DomainEvents");
    if(cls == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: cls = NULL! \n");
     #endif
     break;
    }
    // create AppInfo instance
    obj_ainfo = createAppInfo(env, appInfo);
    if(obj_ainfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_ainfo = NULL! \n");
     #endif
     break;
    }
    // create PubInfo instance
    obj_pinfo = createPubInfo(env, pubInfo);
    if(obj_pinfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_pinfo = NULL! \n");
     #endif
     break;
    }
// ///////////////////////////////// SPOLECNA CAST //
    // get method ID
    mid = (*env)->GetMethodID(env,
                              cls,
                              "onPubDelete",
                              "(Lorg/ocera/orte/types/AppInfo;Lorg/ocera/orte/types/PubInfo;)V");
    if(mid == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: mid = NULL! \n");
     #endif
     break;
    }
    // call method
    (*env)->CallVoidMethod(env,
                           domain_events_cont->obj_de,
                           mid,
                           obj_ainfo,
                           obj_pinfo);
    flag_ok = 1;
  } while(0);
  // while broken
  if(flag_ok)
  {
    if((*jvm)->DetachCurrentThread(jvm) != 0)
    {
      printf(":c!: DetachCurrentThread fault! \n");
      return  ORTE_FALSE;
    }
  }

  return ORTE_TRUE;
}


// /////////////////////////////////////////////////////////////////////
//  Event - onSubRemoteNew
// /////////////////////////////////////////////////////////////////////
Boolean
onSubRemoteNew(const struct ORTEAppInfo *appInfo,
               const struct ORTESubInfo *subInfo,
               void *param)
{
// ///////////////////////////////// SPOLECNA CAST //
  JavaVM          *jvm = NULL;
  JNIEnv          *env = NULL; // local reference
  jobject          obj_ainfo;
  jobject          obj_sinfo;
  jclass           cls;
  jmethodID        mid;
  //
  JORTEDomainEventsContext_t   *domain_events_cont = (JORTEDomainEventsContext_t*) param;
  int flag_ok = 0;

  #ifdef TEST_STAGE
      printf(":c: event func. 'onSubRemoteNew()' called.. \n");
  #endif

  do
  {
// ///////////////////////////////// SPOLECNA CAST //
    if(domain_events_cont->jvm == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: jvm = NULL! \n");
     #endif
     break;
    }
    jvm = domain_events_cont->jvm;
    // get env
    (*jvm)->AttachCurrentThread(jvm, (void **)&env, NULL);
    if(env == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: env = NULL! \n");
     #endif
     break;
    }
    // find class
    cls = findClass(env, "org.ocera.orte.types.DomainEvents");
    if(cls == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: cls = NULL! \n");
     #endif
     break;
    }
    // create AppInfo instance
    obj_ainfo = createAppInfo(env, appInfo);
    if(obj_ainfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_ainfo = NULL! \n");
     #endif
     break;
    }
    // create SubInfo instance
    obj_sinfo = createSubInfo(env, subInfo);
    if(obj_sinfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_sinfo = NULL! \n");
     #endif
     break;
    }
// ///////////////////////////////// SPOLECNA CAST //
    // get method ID
    mid = (*env)->GetMethodID(env,
                              cls,
                              "onSubRemoteNew",
                              "(Lorg/ocera/orte/types/AppInfo;Lorg/ocera/orte/types/SubInfo;)V");
    if(mid == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: mid = NULL! \n");
     #endif
     break;
    }
    // call method
    (*env)->CallVoidMethod(env,
                           domain_events_cont->obj_de,
                           mid,
                           obj_ainfo,
                           obj_sinfo);
    flag_ok = 1;
  } while(0);
  // while broken
  if(flag_ok)
  {
    if((*jvm)->DetachCurrentThread(jvm) != 0)
    {
      printf(":c!: DetachCurrentThread fault! \n");
      return  ORTE_FALSE;
    }
  }

  return ORTE_TRUE;
}


// /////////////////////////////////////////////////////////////////////
//  public void onSubRemoteChanged() { }
// /////////////////////////////////////////////////////////////////////
Boolean
onSubRemoteChanged(const struct ORTEAppInfo *appInfo,
                   const struct ORTESubInfo *subInfo,
                   void *param)
{
// ///////////////////////////////// SPOLECNA CAST //
  JavaVM          *jvm = NULL;
  JNIEnv          *env = NULL; // local reference
  jclass           cls;
  jobject          obj_ainfo;
  jobject          obj_sinfo;
  jmethodID        mid;
  //
  JORTEDomainEventsContext_t   *domain_events_cont = (JORTEDomainEventsContext_t*) param;
  int flag_ok = 0;

  #ifdef TEST_STAGE
      printf(":c: event func. 'onSubRemoteChanged()' called.. \n");
  #endif

  do
  {
// ///////////////////////////////// SPOLECNA CAST //
    if(domain_events_cont->jvm == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: jvm = NULL! \n");
     #endif
     break;
    }
    jvm = domain_events_cont->jvm;
    // get env
    (*jvm)->AttachCurrentThread(jvm, (void **)&env, NULL);
    if(env == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: env = NULL! \n");
     #endif
     break;
    }
    // find class
    cls = findClass(env, "org.ocera.orte.types.DomainEvents");
    if(cls == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: cls = NULL! \n");
     #endif
     break;
    }
    // create AppInfo instance
    obj_ainfo = createAppInfo(env, appInfo);
    if(obj_ainfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_ainfo = NULL! \n");
     #endif
     break;
    }
    // create SubInfo instance
    obj_sinfo = createSubInfo(env, subInfo);
    if(obj_sinfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_sinfo = NULL! \n");
     #endif
     break;
    }
// ///////////////////////////////// SPOLECNA CAST //
    // get method ID
    mid = (*env)->GetMethodID(env,
                              cls,
                              "onSubRemoteChanged",
                              "(Lorg/ocera/orte/types/AppInfo;Lorg/ocera/orte/types/SubInfo;)V");
    if(mid == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: mid = NULL! \n");
     #endif
     break;
    }
    // call method
    (*env)->CallVoidMethod(env,
                           domain_events_cont->obj_de,
                           mid,
                           obj_ainfo,
                           obj_sinfo);
    flag_ok = 1;
  } while(0);
  // while broken
  if(flag_ok)
  {
    if((*jvm)->DetachCurrentThread(jvm) != 0)
    {
      printf(":c!: DetachCurrentThread fault! \n");
      return  ORTE_FALSE;
    }
  }

  return ORTE_TRUE;
}


// /////////////////////////////////////////////////////////////////////
//  public void onSubDelete() { }
// /////////////////////////////////////////////////////////////////////
Boolean
onSubDelete(const struct ORTEAppInfo *appInfo,
            const struct ORTESubInfo *subInfo,
            void *param)
{
// ///////////////////////////////// SPOLECNA CAST //
  JavaVM          *jvm = NULL;
  JNIEnv          *env = NULL; // local reference
  jclass           cls;
  jobject          obj_ainfo;
  jobject          obj_sinfo;
  jmethodID        mid;
  //
  JORTEDomainEventsContext_t   *domain_events_cont = (JORTEDomainEventsContext_t*) param;
  int flag_ok = 0;

  #ifdef TEST_STAGE
      printf(":c: event func. 'onSubDelete()' called.. \n");
  #endif

  do
  {
// ///////////////////////////////// SPOLECNA CAST //
    if(domain_events_cont->jvm == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: jvm = NULL! \n");
     #endif
     break;
    }
    jvm = domain_events_cont->jvm;
    // get env
    (*jvm)->AttachCurrentThread(jvm, (void **)&env, NULL);
    if(env == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: env = NULL! \n");
     #endif
     break;
    }
    // find class
    cls = findClass(env, "org.ocera.orte.types.DomainEvents");
    if(cls == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: cls = NULL! \n");
     #endif
     break;
    }
    // create AppInfo instance
    obj_ainfo = createAppInfo(env, appInfo);
    if(obj_ainfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_ainfo = NULL! \n");
     #endif
     break;
    }
    // create SubInfo instance
    obj_sinfo = createSubInfo(env, subInfo);
    if(obj_sinfo == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: obj_sinfo = NULL! \n");
     #endif
     break;
    }
// ///////////////////////////////// SPOLECNA CAST //
    // get method ID
    mid = (*env)->GetMethodID(env,
                              cls,
                              "onSubDelete",
                              "(Lorg/ocera/orte/types/AppInfo;Lorg/ocera/orte/types/SubInfo;)V");
    if(mid == 0)
    {
     #ifdef TEST_STAGE
       printf(":!c: mid = NULL! \n");
     #endif
     break;
    }
    // call method
    (*env)->CallVoidMethod(env,
                           domain_events_cont->obj_de,
                           mid,
                           obj_ainfo,
                           obj_sinfo);
    flag_ok = 1;
  } while(0);
  // while broken
  if(flag_ok)
  {
    if((*jvm)->DetachCurrentThread(jvm) != 0)
    {
      printf(":c!: DetachCurrentThread fault! \n");
      return  ORTE_FALSE;
    }
  }

  return ORTE_TRUE;
}


// /////////////////////////////////////////////////////////////////////
// create default application domain
// /////////////////////////////////////////////////////////////////////
JNIEXPORT jlong JNICALL
Java_org_ocera_orte_DomainApp_jORTEDomainDefaultAppCreate
(JNIEnv *env, jclass class, jint jdomain, jboolean jsusp)
{
  jlong     d;

  #ifdef TEST_STAGE
    printf(":c: jsem pred ORTEDomainDefaultAppCreate() \n");
  #endif
  // call ORTE function
  d = (jlong) ORTEDomainAppCreate((int)jdomain,
                                 NULL,
                                 NULL,
                                 (Boolean) jsusp);
  if(!d) {
    printf(":!c: ORTEDomainDefaultAppCreate() FAILED.. \n");
    return 0;
  }
  #ifdef TEST_STAGE
    printf(":c: ORTEDomainDefautlAppCreate() ok.. + %d \n", d);
  #endif
  return (d);
}

// //////////////////////////////////////////////////////////////////////
// create user application domain
// //////////////////////////////////////////////////////////////////////
JNIEXPORT jlong JNICALL
Java_org_ocera_orte_DomainApp_jORTEDomainAppCreate
(JNIEnv *env, jclass cls,
 jint jdomain,
 jlong propHandle,
 jlong eventsHandle,
 jobject obj_de,
 jboolean jsusp)
{
  // jni varibles
  JavaVM                 *jvm;
  jlong                   d;
  //
  ORTEDomainAppEvents    *dom_events;
  JORTEDomainEventsContext_t  *domain_events_cont;

  #ifdef TEST_STAGE
    printf(":c: ORTEDomainAppCreate() called.. \n");
  #endif
  // memory alocation
  // don't forget free memory - free()!!
  domain_events_cont = (JORTEDomainEventsContext_t *) malloc(sizeof(JORTEDomainEventsContext_t));
  // get jvm
  jint b = (*env)->GetJavaVM(env,&jvm);
  if (b < 0)
  {
    printf(":!c: getJavaVM() failed! \n");
    return 0;
  }
  // create global references
  domain_events_cont->jvm = jvm;
  // domain events
  domain_events_cont->obj_de = (*env)->NewGlobalRef(env, obj_de);
  // get new events
  dom_events = (ORTEDomainAppEvents *) eventsHandle;
  ////////////////////////////////////////////////
  // set new events & their prarameters
  // onRegFail
  dom_events->onRegFail = (ORTEOnRegFail) onRegFail;
  dom_events->onRegFailParam = (void *) domain_events_cont;
  // onMgrNew
  dom_events->onMgrNew = (ORTEOnMgrNew) onMgrNew;
  dom_events->onMgrNewParam = (void *) domain_events_cont;
  // onMgrDelete
  dom_events->onMgrDelete = (ORTEOnMgrDelete) onMgrDelete;
  dom_events->onMgrDeleteParam = (void *) domain_events_cont;
  // onAppRemoteNew
  dom_events->onAppRemoteNew = (ORTEOnAppRemoteNew) onAppRemoteNew;
  dom_events->onAppRemoteNewParam = (void *) domain_events_cont;
  // onAppDelete
  dom_events->onAppDelete = (ORTEOnAppDelete) onAppDelete;
  dom_events->onAppDeleteParam = (void *) domain_events_cont;
  // onPubRemoteNew
  dom_events->onPubRemoteNew = (ORTEOnPubRemote) onPubRemoteNew;
  dom_events->onPubRemoteNewParam = (void *) domain_events_cont;
  // onPubRemoteChanged
  dom_events->onPubRemoteChanged = (ORTEOnPubRemote) onPubRemoteChanged;
  dom_events->onPubRemoteChangedParam = (void *) domain_events_cont;
  // onPubDelete
  dom_events->onPubDelete = (ORTEOnPubDelete) onPubDelete;
  dom_events->onPubDeleteParam = (void *) domain_events_cont;
  // onSubRemoteNew
  dom_events->onSubRemoteNew = (ORTEOnSubRemote) onSubRemoteNew;
  dom_events->onSubRemoteNewParam = (void *) domain_events_cont;
  // onSubRemoteChanged
  dom_events->onSubRemoteChanged = (ORTEOnSubRemote) onSubRemoteChanged;
  dom_events->onSubRemoteChangedParam = (void *) domain_events_cont;
  // onSubDelete
  dom_events->onSubDelete = (ORTEOnSubDelete) onSubDelete;
  dom_events->onSubDeleteParam = (void *) domain_events_cont;
  ////////////////////////////////////////////////
  // call ORTE function
  d = (jlong) ORTEDomainAppCreate((int)jdomain,
                                 (ORTEDomainProp *) propHandle,
                                 (ORTEDomainAppEvents *) eventsHandle,
                                 (Boolean) jsusp);
  if(!d) {
    printf(":!c: creating app domain failed! [NULL handle]  \n");
    return 0;
  }
  #ifdef TEST_STAGE
    printf(":c: ORTEDomainAppCreate() ok.. + %d \n", d);
  #endif
  return (d);
}

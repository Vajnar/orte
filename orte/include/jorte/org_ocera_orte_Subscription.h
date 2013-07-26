/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_ocera_orte_Subscription */

#ifndef _Included_org_ocera_orte_Subscription
#define _Included_org_ocera_orte_Subscription
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_ocera_orte_Subscription
 * Method:    jORTESubscriptionCreate
 * Signature: (JIILjava/lang/String;Ljava/lang/String;ILorg/ocera/orte/types/MessageData;Lorg/ocera/orte/types/NtpTime;Lorg/ocera/orte/types/NtpTime;Lorg/ocera/orte/SubscriptionCallback;J)J
 */
JNIEXPORT jlong JNICALL Java_org_ocera_orte_Subscription_jORTESubscriptionCreate
  (JNIEnv *, jobject, jlong, jint, jint, jstring, jstring, jobject, jint, jobject, jobject, jobject, jobject, jlong);

/*
 * Class:     org_ocera_orte_Subscription
 * Method:    jORTESubscriptionDestroy
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_ocera_orte_Subscription_jORTESubscriptionDestroy
  (JNIEnv *, jobject, jlong);

/*
 * Class:     org_ocera_orte_Subscription
 * Method:    jORTESubscriptionPropertiesGet
 * Signature: (J)Lorg/ocera/orte/types/SubsProp;
 */
JNIEXPORT jobject JNICALL Java_org_ocera_orte_Subscription_jORTESubscriptionPropertiesGet
  (JNIEnv *, jobject, jlong);

/*
 * Class:     org_ocera_orte_Subscription
 * Method:    jORTESubscriptionPropertiesSet
 * Signature: (JLorg/ocera/orte/types/SubsProp;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_ocera_orte_Subscription_jORTESubscriptionPropertiesSet
  (JNIEnv *, jobject, jlong, jobject);

/*
 * Class:     org_ocera_orte_Subscription
 * Method:    jORTESubscriptionGetStatus
 * Signature: (J)Lorg/ocera/orte/types/Status;
 */
JNIEXPORT jobject JNICALL Java_org_ocera_orte_Subscription_jORTESubscriptionGetStatus
  (JNIEnv *, jobject, jlong);

/*
 * Class:     org_ocera_orte_Subscription
 * Method:    jORTESubscriptionWaitForPublications
 * Signature: (JLorg/ocera/orte/types/NtpTime;JJ)I
 */
JNIEXPORT jint JNICALL Java_org_ocera_orte_Subscription_jORTESubscriptionWaitForPublications
  (JNIEnv *, jobject, jlong, jobject, jlong, jlong);

/*
 * Class:     org_ocera_orte_Subscription
 * Method:    jORTESubscriptionPull
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_ocera_orte_Subscription_jORTESubscriptionPull
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif

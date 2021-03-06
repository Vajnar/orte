/*
 *  $Id: parameter.c,v 0.0.0.1          2003/10/13
 *
 *  DEBUG:  section 11                  parameter
 *
 *  -------------------------------------------------------------------
 *                                ORTE
 *                      Open Real-Time Ethernet
 *
 *                      Copyright (C) 2001-2006
 *  Department of Control Engineering FEE CTU Prague, Czech Republic
 *                      http://dce.felk.cvut.cz
 *                      http://www.ocera.org
 *
 *  Author:              Petr Smolik	petr@smoliku.cz
 *  Advisor:             Pavel Pisa
 *  Project Responsible: Zdenek Hanzalek
 *  --------------------------------------------------------------------
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */

#include "orte_all.h"

/*****************************************************************************/
void
parameterPutString(ParameterSequence *ps, int8_t id, int8_t *sstr)
{
  int               len;

  len = strlen((char *)sstr)+1;
  ps->parameterID = id;
  ps->parameterLength = len;
  ps->parameter = NULL;

  if (MAX_PARAMETER_LOCAL_LENGTH < len) {
    ps->parameter = (u_char *)MALLOC(len);
    strncpy((char *)ps->parameter, (const char *)sstr, len);
  } else {
    strncpy((char *)ps->parameterLocal.asStr, (const char *)sstr, len);
  }
}

/*****************************************************************************/
int
parameterDelete(CSChange *csChange)
{
  ParameterSequence *ps;

  ul_list_for_each(CSChangeAttributes,
		   csChange,
		   ps) {
    if ((ps->parameterLength) > MAX_PARAMETER_LOCAL_LENGTH)
      FREE(ps->parameter);
  }
  //ps is like one piece of memory
  if (CSChangeAttributes_first(csChange))
    FREE(CSChangeAttributes_first(csChange));
  CSChangeAttributes_init_head(csChange);
  return ORTE_TRUE;
}


/*****************************************************************************/
int
parameterCodeCodecFromCSChange(CSChange *csChange, CDR_Codec *cdrCodec)
{
  ParameterSequence *ps;

  ul_list_for_each(CSChangeAttributes,
		   csChange,
		   ps) {

    if (CDR_put_ushort(cdrCodec, ps->parameterID) == CORBA_FALSE)
      return -1;
    if (CDR_put_ushort(cdrCodec, ps->parameterLength) == CORBA_FALSE)
      return -1;

    debug(11, 10) ("parameterCodeCodecToCSChange: parameterID-0x%x, len-%d\n",
		   ps->parameterID, ps->parameterLength);

    switch (ps->parameterID) {
      case PID_SENTINEL:
	break;
      //NtpTime
      case PID_EXPIRATION_TIME:
      case PID_PERSISTENCE:
      case PID_MINIMUM_SEPARATION:
	/* time in seconds */
	if (CDR_put_long(cdrCodec, ps->parameterLocal.asNtpTime.seconds) ==
	    CORBA_FALSE)
	  return -1;
	/* time in seconds / 2^32 */
	if (CDR_put_ulong(cdrCodec, ps->parameterLocal.asNtpTime.fraction) ==
	    CORBA_FALSE)
	  return -1;
	break;
      //CORBA_unsigned_long
      case PID_TYPE_CHECKSUM:
      case PID_STRENGTH:
      case PID_SEND_QUEUE_SIZE:
      case PID_RECV_QUEUE_SIZE:
      case PID_RELIABILITY_OFFERED:
      case PID_RELIABILITY_REQUESTED:
      case PID_MANAGER_KEY:
      case PID_MATATRAFFIC_MULTICAST_IPADDRESS:
      case PID_APP_IPADDRESS:
      case PID_USERDATA_MULTICAST_IPADDRESS:
      case PID_METATRAFFIC_UNICAST_PORT:
      case PID_USERDATA_UNICAST_PORT:
	if (CDR_put_ulong(cdrCodec, ps->parameterLocal.asLong) ==
	    CORBA_FALSE)
	  return -1;
	break;
      //VendorId
      case PID_VENDOR_ID:
	if (CDR_put_octet(cdrCodec, ps->parameterLocal.asVendorId.major) ==
	    CORBA_FALSE)
	  return -1;
	if (CDR_put_octet(cdrCodec, ps->parameterLocal.asVendorId.minor) ==
	    CORBA_FALSE)
	  return -1;
	break;
      //ProtocolVersion
      case PID_PROTOCOL_VERSION:
	if (CDR_put_octet(cdrCodec, ps->parameterLocal.asProtocolVersion.major) ==
	    CORBA_FALSE)
	  return -1;
	if (CDR_put_octet(cdrCodec, ps->parameterLocal.asProtocolVersion.minor) ==
	    CORBA_FALSE)
	  return -1;
	break;
      //SequenceNumber
      case PID_VARGAPPS_SEQUENCE_NUMBER_LAST:
	if (CDR_put_ulong(cdrCodec, ps->parameterLocal.asSequenceNumber.high) ==
	    CORBA_FALSE)
	  return -1;
	if (CDR_put_ulong(cdrCodec, ps->parameterLocal.asSequenceNumber.low) ==
	    CORBA_FALSE)
	  return -1;
	break;
      //Boolean
      case PID_EXPECTS_ACK:
	if (CDR_put_octet(cdrCodec, ps->parameterLocal.asOctet) ==
	    CORBA_FALSE)
	  return -1;
	break;
      //PathName,TypeName
      case PID_TOPIC:
      case PID_TYPE_NAME: {
	int wptr, len;

	wptr = cdrCodec->wptr;

	len = ps->parameterLength;
	if (len % 4) {                    //length alignment to 4
	  len &= ~3;
	  len += 4;
	}
	len += 4;                           //data size
	cdrCodec->wptr -= 2;                //new alignments value
	if (CDR_put_ushort(cdrCodec, (CORBA_unsigned_short)len) == CORBA_FALSE)
	  return -1;

	if (ps->parameterLength > MAX_PARAMETER_LOCAL_LENGTH) {
	  if (CDR_put_string(cdrCodec, (char *)ps->parameter) ==
	      CORBA_FALSE)
	    return -1;
	} else {
	  if (CDR_put_string(cdrCodec, (char *)ps->parameterLocal.asStr) ==
	      CORBA_FALSE)
	    return -1;
	}

	cdrCodec->wptr = wptr+len;
      } break;
      case PID_PAD:
	break;
      default:
	debug(11, 1) ("parameterCodeCodecFromCSChange: undefined parameterID: %d\n",
		      ps->parameterID);
	break;
    }
  }
  return 0;
}

/*****************************************************************************/
int
parameterDecodeCodecToCSChange(CSChange *csChange, CDR_Codec *cdrCodec)
{
  ParameterId       parameterId;
  ParameterLength   parameterLength;
  ParameterSequence *ps;
  uint16_t          counter = 0;
  unsigned int      rptr;

  CSChangeAttributes_init_head(csChange);
  rptr = cdrCodec->rptr;

  //count number of parameters -> we need one memory allocation for ps
  while (cdrCodec->rptr < cdrCodec->buf_len) {
    if (CDR_get_ushort(cdrCodec, &parameterId) == CORBA_FALSE)
      break;
    if (CDR_get_ushort(cdrCodec, &parameterLength) == CORBA_FALSE)
      break;
    if (parameterId == PID_SENTINEL)
      break;
    counter++;
    cdrCodec->rptr += parameterLength;
  }

  ps = (ParameterSequence *)MALLOC(sizeof(ParameterSequence)*(counter+1));
  cdrCodec->rptr = rptr;

  while (counter) {
    CDR_get_ushort(cdrCodec, &parameterId);
    CDR_get_ushort(cdrCodec, &parameterLength);

    ps->parameterID = parameterId;
    ps->parameterLength = parameterLength;
    ps->parameter = NULL;

    /* save start position of parameter */
    rptr = cdrCodec->rptr;

    debug(11, 10) ("parameterDecodeCodecToCSChange: parameterID-0x%x, len-%d\n",
		   parameterId, parameterLength);
    switch (parameterId) {
      case PID_SENTINEL:
	counter = 1;
	break;
      //NtpTime
      case PID_EXPIRATION_TIME:
      case PID_PERSISTENCE:
      case PID_MINIMUM_SEPARATION:
	/* time in seconds */
	CDR_get_long(cdrCodec, &ps->parameterLocal.asNtpTime.seconds);
	/* time in seconds / 2^32 */
	CDR_get_ulong(cdrCodec, (CORBA_unsigned_long *)&ps->parameterLocal.asNtpTime.fraction);
	break;
      //CORBA_unsigned_long
      case PID_TYPE_CHECKSUM:
      case PID_STRENGTH:
      case PID_SEND_QUEUE_SIZE:
      case PID_RECV_QUEUE_SIZE:
      case PID_RELIABILITY_OFFERED:
      case PID_RELIABILITY_REQUESTED:
      case PID_MANAGER_KEY:
      case PID_MATATRAFFIC_MULTICAST_IPADDRESS:
      case PID_APP_IPADDRESS:
      case PID_USERDATA_MULTICAST_IPADDRESS:
      case PID_METATRAFFIC_UNICAST_PORT:
      case PID_USERDATA_UNICAST_PORT:
	CDR_get_ulong(cdrCodec, &ps->parameterLocal.asLong);
	break;
      //VendorId
      case PID_VENDOR_ID:
	CDR_get_octet(cdrCodec, (CORBA_octet *)&ps->parameterLocal.asVendorId.major);
	CDR_get_octet(cdrCodec, (CORBA_octet *)&ps->parameterLocal.asVendorId.minor);
	break;
      //ProtocolVersion
      case PID_PROTOCOL_VERSION:
	CDR_get_octet(cdrCodec, (CORBA_octet *)&ps->parameterLocal.asProtocolVersion.major);
	CDR_get_octet(cdrCodec, (CORBA_octet *)&ps->parameterLocal.asProtocolVersion.minor);
	break;
      //SequenceNumber
      case PID_VARGAPPS_SEQUENCE_NUMBER_LAST:
	CDR_get_ulong(cdrCodec, (CORBA_unsigned_long *)&ps->parameterLocal.asSequenceNumber.high);
	CDR_get_ulong(cdrCodec, (CORBA_unsigned_long *)&ps->parameterLocal.asSequenceNumber.low);
	break;
      //Boolean
      case PID_EXPECTS_ACK:
	CDR_get_octet(cdrCodec, ps->parameterLocal.asStr);
	break;
      //PathName,TypeName
      case PID_TOPIC:
      case PID_TYPE_NAME: {
	CORBA_unsigned_long len;

	CDR_get_ulong(cdrCodec, (CORBA_unsigned_long *)&len);
	cdrCodec->rptr -= 4;
	ps->parameterLength = (uint16_t)len;
	if (ps->parameterLength > MAX_PARAMETER_LOCAL_LENGTH) {
	  CDR_get_string(cdrCodec, (CORBA_char **)&ps->parameter);
	} else {
	  CDR_get_string_buff(cdrCodec, (CORBA_char *)ps->parameterLocal.asStr);
	}
      } break;
      case PID_PAD:
	break;
      default:
	debug(11, 1) ("parameterDecodeCodecToCSChange: undefined parameterID: %d\n",
		      parameterId);
	break;
    }
    CSChangeAttributes_insert(csChange, ps);
    ps++; //next ps
    counter--;

    cdrCodec->rptr = rptr+parameterLength;
  }
  //SENTINEL
  ps->parameterID = PID_SENTINEL;
  ps->parameterLength = 0;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  return ORTE_TRUE;
}

/*****************************************************************************/
int
parameterUpdateCSChange(
  CSChange *csChange, AppParams *ap, Boolean Manager)
{
  ParameterSequence *ps;
  int               i;

  i = ap->managerKeyCount+
      ap->metatrafficMulticastIPAddressCount+
      ap->unicastIPAddressCount+7;
  if (!Manager)
    i--;
  CSChangeAttributes_init_head(csChange);
  ps = (ParameterSequence *)MALLOC(sizeof(ParameterSequence)*i);
  //EXPIRATION_TIME
  ps->parameterID = PID_EXPIRATION_TIME;
  ps->parameterLength = 8;
  memcpy(ps->parameterLocal.asStr, &ap->expirationTime, ps->parameterLength);
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  //MATATRAFFIC_MULTICAST_IPADDRESS
  for (i = 0; i < ap->metatrafficMulticastIPAddressCount; i++) {
    ps->parameterID = PID_MATATRAFFIC_MULTICAST_IPADDRESS;
    ps->parameterLength = 4;
    ps->parameterLocal.asIPAddress = ap->metatrafficMulticastIPAddressList[i];
    ps->parameter = NULL;
    CSChangeAttributes_insert(csChange, ps);
    ps++;
  }
  //METATRAFFIC_UNICAST_PORT
  ps->parameterID = PID_METATRAFFIC_UNICAST_PORT;
  ps->parameterLength = 4;
  ps->parameterLocal.asPort = ap->metatrafficUnicastPort;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  //USERDATA_UNICAST_PORT
  ps->parameterID = PID_USERDATA_UNICAST_PORT;
  ps->parameterLength = 4;
  ps->parameterLocal.asPort = ap->userdataUnicastPort;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  //APP_IPADDRESS
  for (i = 0; i < ap->unicastIPAddressCount; i++) {
    ps->parameterID = PID_APP_IPADDRESS;
    ;
    ps->parameterLength = 4;
    ps->parameterLocal.asIPAddress = ap->unicastIPAddressList[i];
    ps->parameter = NULL;
    CSChangeAttributes_insert(csChange, ps);
    ps++;
  }
  //PROTOCOL_VERSION
  ps->parameterID = PID_PROTOCOL_VERSION;
  ps->parameterLength = 2;
  ps->parameterLocal.asProtocolVersion = ap->protocolVersion;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  //VENDOR_ID
  ps->parameterID = PID_VENDOR_ID;
  ps->parameterLength = 2;
  ps->parameterLocal.asVendorId = ap->vendorId;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  if (Manager) {    //Manager
    //VARGAPPS_SEQUENCE_NUMBER_LAST
    ps->parameterID = PID_VARGAPPS_SEQUENCE_NUMBER_LAST;
    ps->parameterLength = 8;
    ps->parameterLocal.asSequenceNumber = ap->vargAppsSequenceNumber;
    ps->parameter = NULL;
    CSChangeAttributes_insert(csChange, ps);
    ps++;
  }
  //MANAGER_KEY
  for (i = 0; i < ap->managerKeyCount; i++) {
    ps->parameterID = PID_MANAGER_KEY;
    ps->parameterLength = 4;
    ps->parameterLocal.asUInt32 = ap->managerKeyList[i];
    ps->parameter = NULL;
    CSChangeAttributes_insert(csChange, ps);
    ps++;
  }
  //SENTINEL
  ps->parameterID = PID_SENTINEL;
  ps->parameterLength = 0;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  return 0;
}

/*****************************************************************************/
int
parameterUpdateCSChangeFromPublication(CSChange *csChange, ORTEPublProp *pp)
{
  ParameterSequence *ps;

  CSChangeAttributes_init_head(csChange);
  ps = (ParameterSequence *)MALLOC(sizeof(ParameterSequence)*8);
  //persistence
  ps->parameterID = PID_PERSISTENCE;
  ps->parameterLength = 8;
  memcpy(ps->parameterLocal.asStr, &pp->persistence, ps->parameterLength);
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  /* reliabitityOffered */
  ps->parameterID = PID_RELIABILITY_OFFERED;
  ps->parameterLength = 4;
  ps->parameterLocal.asUInt32 = pp->reliabilityOffered;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  /* sendQueueSize */
  ps->parameterID = PID_SEND_QUEUE_SIZE;
  ps->parameterLength = 4;
  ps->parameterLocal.asUInt32 = pp->sendQueueSize;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  /* strength */
  ps->parameterID = PID_STRENGTH;
  ps->parameterLength = 4;
  ps->parameterLocal.asUInt32 = pp->strength;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  /* topic */
  parameterPutString(ps, PID_TOPIC, pp->topic);
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  /* typeCheckSum */
  ps->parameterID = PID_TYPE_CHECKSUM;
  ps->parameterLength = 4;
  ps->parameterLocal.asUInt32 = pp->typeChecksum;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  /* typeName */
  parameterPutString(ps, PID_TYPE_NAME, pp->typeName);
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  /* sentinel -> end */
  ps->parameterID = PID_SENTINEL;
  ps->parameterLength = 0;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  return 0;
}

/*****************************************************************************/
int
parameterUpdateCSChangeFromSubscription(CSChange *csChange, ORTESubsProp *sp)
{
  ParameterSequence *ps;

  CSChangeAttributes_init_head(csChange);
  ps = (ParameterSequence *)MALLOC(sizeof(ParameterSequence)*8);
  //minimum separation
  ps->parameterID = PID_MINIMUM_SEPARATION;
  ps->parameterLength = 8;
  memcpy(ps->parameterLocal.asStr, &sp->minimumSeparation, ps->parameterLength);
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  /* receive queue size*/
  ps->parameterID = PID_RECV_QUEUE_SIZE;
  ps->parameterLength = 4;
  ps->parameterLocal.asUInt32 = sp->recvQueueSize;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  /* reliabitityRequested */
  ps->parameterID = PID_RELIABILITY_REQUESTED;
  ps->parameterLength = 4;
  ps->parameterLocal.asUInt32 = sp->reliabilityRequested;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  /* topic */
  parameterPutString(ps, PID_TOPIC, sp->topic);
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  /* typeCheckSum */
  ps->parameterID = PID_TYPE_CHECKSUM;
  ps->parameterLength = 4;
  ps->parameterLocal.asUInt32 = sp->typeChecksum;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  /* typeName */
  parameterPutString(ps, PID_TYPE_NAME, sp->typeName);
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  /* userdata multicast ipaddress */
  ps->parameterID = PID_USERDATA_MULTICAST_IPADDRESS;
  ps->parameterLength = 4;
  ps->parameterLocal.asIPAddress = sp->multicast;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  ps++;
  /* sentinel -> end */
  ps->parameterID = PID_SENTINEL;
  ps->parameterLength = 0;
  ps->parameter = NULL;
  CSChangeAttributes_insert(csChange, ps);
  return 0;
}

/*****************************************************************************/
int
parameterUpdateApplication(CSChange *csChange, AppParams *ap)
{
  ParameterSequence   *ps;

  ap->managerKeyCount = 0;
  ap->metatrafficMulticastIPAddressCount = 0;
  ap->unicastIPAddressCount = 0;
  ap->appId = csChange->guid.aid;
  ap->hostId = csChange->guid.hid;
  ul_list_for_each(CSChangeAttributes, csChange, ps) {
    switch (ps->parameterID) {
      case PID_EXPIRATION_TIME:
	ap->expirationTime = ps->parameterLocal.asNtpTime;
	break;
      case PID_MANAGER_KEY:
	ap->managerKeyList[ap->managerKeyCount] =
	  ps->parameterLocal.asUInt32;
	ap->managerKeyCount++;
	break;
      case PID_MATATRAFFIC_MULTICAST_IPADDRESS:
	ap->metatrafficMulticastIPAddressList[ap->metatrafficMulticastIPAddressCount] =
	  ps->parameterLocal.asIPAddress;
	ap->metatrafficMulticastIPAddressCount++;
	break;
      case PID_APP_IPADDRESS:
	ap->unicastIPAddressList[ap->unicastIPAddressCount] =
	  ps->parameterLocal.asIPAddress;
	ap->unicastIPAddressCount++;
	break;
      case PID_USERDATA_MULTICAST_IPADDRESS:
	break;
      case PID_METATRAFFIC_UNICAST_PORT:
	ap->metatrafficUnicastPort = ps->parameterLocal.asPort;
	break;
      case PID_USERDATA_UNICAST_PORT:
	ap->userdataUnicastPort = ps->parameterLocal.asPort;
	break;
      case PID_VENDOR_ID:
	ap->vendorId = ps->parameterLocal.asVendorId;
	break;
      case PID_PROTOCOL_VERSION:
	ap->protocolVersion = ps->parameterLocal.asProtocolVersion;
	break;
      case PID_VARGAPPS_SEQUENCE_NUMBER_LAST:
	ap->vargAppsSequenceNumber = ps->parameterLocal.asSequenceNumber;
	break;
    }
  }
  return 0;
}

/*****************************************************************************/
int
parameterUpdatePublication(CSChange *csChange, ORTEPublProp *pp)
{
  ParameterSequence   *ps;

  ul_list_for_each(CSChangeAttributes, csChange, ps) {
    switch (ps->parameterID) {
      case PID_EXPECTS_ACK:
	pp->expectsAck = *(Boolean *)&ps->parameterLocal;
	break;
      case PID_PERSISTENCE:
	pp->persistence = ps->parameterLocal.asNtpTime;
	break;
      case PID_RELIABILITY_OFFERED:
	pp->reliabilityOffered = ps->parameterLocal.asUInt32;
	break;
      case PID_SEND_QUEUE_SIZE:
	pp->sendQueueSize = ps->parameterLocal.asUInt32;
	break;
      case PID_STRENGTH:
	pp->strength = ps->parameterLocal.asUInt32;
	break;
      case PID_TOPIC:
	if (ps->parameterLength > MAX_PARAMETER_LOCAL_LENGTH)
	  strncpy((char *)pp->topic, (const char *)ps->parameter, ps->parameterLength);
	else
	  strncpy((char *)pp->topic, (const char *)ps->parameterLocal.asStr, ps->parameterLength);
	break;
      case PID_TYPE_CHECKSUM:
	pp->typeChecksum = ps->parameterLocal.asTypeChecksum;
	break;
      case PID_TYPE_NAME:
	if (ps->parameterLength > MAX_PARAMETER_LOCAL_LENGTH)
	  strncpy((char *)pp->typeName, (const char *)ps->parameter, ps->parameterLength);
	else
	  strncpy((char *)pp->typeName, (const char *)ps->parameterLocal.asStr, ps->parameterLength);
	break;
    }
  }
  return 0;
}

/*****************************************************************************/
int
parameterUpdateSubscription(CSChange *csChange, ORTESubsProp *sp)
{
  ParameterSequence   *ps;

  ul_list_for_each(CSChangeAttributes, csChange, ps) {
    switch (ps->parameterID) {
      case PID_MINIMUM_SEPARATION:
	sp->minimumSeparation = ps->parameterLocal.asNtpTime;
	break;
      case PID_RECV_QUEUE_SIZE:
	sp->recvQueueSize = ps->parameterLocal.asUInt32;
	break;
      case PID_RELIABILITY_REQUESTED:
	sp->reliabilityRequested = ps->parameterLocal.asUInt32;
	break;
      case PID_TOPIC:
	if (ps->parameterLength > MAX_PARAMETER_LOCAL_LENGTH)
	  strncpy((char *)sp->topic, (const char *)ps->parameter, ps->parameterLength);
	else
	  strncpy((char *)sp->topic, (const char *)ps->parameterLocal.asStr, ps->parameterLength);
	break;
      case PID_TYPE_CHECKSUM:
	sp->typeChecksum = ps->parameterLocal.asTypeChecksum;
	break;
      case PID_TYPE_NAME:
	if (ps->parameterLength > MAX_PARAMETER_LOCAL_LENGTH)
	  strncpy((char *)sp->typeName, (const char *)ps->parameter, ps->parameterLength);
	else
	  strncpy((char *)sp->typeName, (const char *)ps->parameterLocal.asStr, ps->parameterLength);
	break;
      case PID_USERDATA_MULTICAST_IPADDRESS:
	sp->multicast = ps->parameterLocal.asIPAddress;
	break;
    }
  }
  return 0;
}

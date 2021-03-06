/*

  midXparser
  A small footprint midi parser.
  Copyright (C) 2017/2018 by The KikGen labs.

  HEADER CLASS FILE

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.

   Licence : MIT.
*/
#pragma once
#include <stdbool.h>

#ifndef midiXparser_h
#define midiXparser_h
#define byte uint8_t
#include <stdint.h>
#include <stdlib.h>

  typedef enum  {
        // CHANNEL VOICE
        noteOffStatus         = 0X80,
        noteOnStatus          = 0X90,
        polyKeyPressureStatus = 0XA0,
        controlChangeStatus   = 0XB0,
        programChangeStatus   = 0XC0,
        channelPressureStatus = 0XD0,
        pitchBendStatus       = 0XE0,
        // SYSTEM COMMON
        soxStatus             = 0XF0,
        midiTimeCodeStatus    = 0XF1,
        songPosPointerStatus  = 0XF2,
        songSelectStatus      = 0XF3,
        reserved1Status       = 0XF4,
        reserved2Status       = 0XF5,
        tuneRequestStatus     = 0XF6,
        eoxStatus             = 0XF7,
        // REAL TIME
        timingClockStatus     = 0XF8,
        reserved3Status       = 0XF9,
        startStatus           = 0XFA,
        continueStatus        = 0XFB,
        stopStatus            = 0XFC,
        reserved4Status       = 0XFD,
        activeSensingStatus   = 0XFE,
        systemResetStatus     = 0XFF
    } midiStatusValue;
        // Midi messages type
    typedef enum  {
        noneMsgTypeMsk          = 0B0000,
        channelVoiceMsgTypeMsk  = 0B0001,
        systemCommonMsgTypeMsk  = 0B0010,
        realTimeMsgTypeMsk      = 0B0100,
        sysExMsgTypeMsk         = 0B1000,
        allMsgTypeMsk           = 0B1111
    } midiMsgTypeMaskValue;

  uint8_t  m_midiMsg[3];
  uint8_t  m_midiMsgRealTime; // Used for real time only
  uint8_t  m_indexMsgLen = 0;
  uint8_t  m_expectedMsgLen = 0;
  bool     m_sysExMode = false;
  bool     m_sysExError = false;
  unsigned m_sysExMsgLen = 0;
  unsigned m_sysExindexMsgLen = 0;
  bool     m_isByteCaptured=false;
  byte     m_readByte = 0;
  bool     m_runningStatusPossible=false;
  uint8_t  m_midiMsgTypeFilterMsk = noneMsgTypeMsk;
  uint8_t  m_midiParsedMsgType    = noneMsgTypeMsk;
  uint8_t  m_midiCurrentMsgType   = noneMsgTypeMsk;

static const  uint8_t m_systemCommonMsglen[]={
        // SYSTEM COMMON
        0, // soxStatus             = 0XF0,
        2, // midiTimeCodeStatus    = 0XF1,
        3, // songPosPointerStatus  = 0XF2,
        2, // songSelectStatus      = 0XF3,
        0, // reserved1Status       = 0XF4,
        0, // reserved2Status       = 0XF5,
        1, // tuneRequestStatus     = 0XF6,
        0  // eoxStatus             = 0XF7,
};

static const  uint8_t m_channelVoiceMsgMsglen[]={
        3, // noteOffStatus         = 0X80,
        3, // noteOnStatus          = 0X90,
        3, // polyKeyPressureStatus = 0XA0,
        3, // controlChangeStatus   = 0XB0,
        2, // programChangeStatus   = 0XC0,
        2, // channelPressureStatus = 0XD0,
        3, // pitchBendStatus       = 0XE0,
};






    // Methods
    bool        isSysExMode(void) ;
    bool        wasSysExMode(void) ;
    bool        isSysExError(void);
    bool        isByteCaptured(void) ;
    bool        isMidiStatus(midiStatusValue );
    uint8_t     getMidiMsgType(void) ;
    uint8_t     getMidiCurrentMsgType(void) ;
    uint8_t     getMidiMsgLen(void);
    uint8_t *   getMidiMsg(void);
    byte        getByte(void) ;
    unsigned    getSysExMsgLen(void) ;
    void        setMidiMsgFilter(uint8_t );
    bool        parse(byte );
    static uint8_t     getMidiStatusMsgTypeMsk(uint8_t ) ;
    static uint8_t     getMidiStatusMsgLen(uint8_t );





#endif
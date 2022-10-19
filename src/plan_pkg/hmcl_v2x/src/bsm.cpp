/*
 * UPER Based client application sample code
 * 
 * Copyright (c) 2022, CEST
 *
 */

// #include "j2735.h"
#include "j2735/MessageFrame.h"

int fill_j2735_bsm(MessageFrame_t *dst)
{        
    dst->messageId = 20; // J2735 표준문서 PDF 파일 참조 basicSafetyMessage DSRCmsgID ::= 20 -- BSM, heartbeat msg
    dst->value.present = MessageFrame__value_PR_BasicSafetyMessage; // MessageFrame::value choice (asn1c)

    BasicSafetyMessage_t *ptrBsm = &dst->value.choice.BasicSafetyMessage;

    ptrBsm->coreData.id.buf = (uint8_t *)malloc(4);
    ptrBsm->coreData.id.size = 4;

    ptrBsm->coreData.id.buf[0] = 0x00;         // (INPUT) <---- 할당된 대학별 ID 입력
    ptrBsm->coreData.id.buf[1] = 0x01;         // (INPUT) <---- 할당된 대학별 ID 입력
    ptrBsm->coreData.id.buf[2] = 0x02;         // (INPUT) <---- 할당된 대학별 ID 입력
    ptrBsm->coreData.id.buf[3] = 0x03;         // (INPUT) <---- 할당된 대학별 ID 입력

    ptrBsm->coreData.msgCnt = 0;               // (INPUT) <---- 매 BSM 전송마다 1씩 증가하는 값
    ptrBsm->coreData.secMark = 0;              // (INPUT) <---- 전송 시점 UTC 시간 (초)
    ptrBsm->coreData.lat = 0;                  // (INPUT) <---- 현재 차량의 위치 (위도)
    ptrBsm->coreData.Long = 0;                 // (INPUT) <---- 현재 차량의 위치 (경도)
    ptrBsm->coreData.elev = 0;                 // (INPUT) <---- 현재 차량의 위치 (고도)
    ptrBsm->coreData.accuracy.orientation = 0; // (INPUT) <---- 현재 차량의 위치 정확도 (SemiMajorAxisOrientation)
    ptrBsm->coreData.accuracy.semiMajor = 0;   // (INPUT) <---- 현재 차량의 위치 정확도 (SemiMajorAxisAccuracy)
    ptrBsm->coreData.accuracy.semiMinor = 0;   // (INPUT) <---- 현재 차량의 위치 정확도 (SemiMinorAxisAccuracy)
    ptrBsm->coreData.transmission = 0;         // (INPUT) <---- 현재 차량의 변속기 상태
    ptrBsm->coreData.speed = 0;                // (INPUT) <---- 현재 차량의 속도
    ptrBsm->coreData.heading = 0;              // (INPUT) <---- 현재 차량의 진행 방향
    ptrBsm->coreData.angle = 0;                // (INPUT) <---- 현재 차량의 조향각 (Steering Wheel Angle)
    ptrBsm->coreData.accelSet.lat = 0;         // (INPUT) <---- 현재 차량의 가속도 정보 (Lateral Axis)
    ptrBsm->coreData.accelSet.Long = 0;        // (INPUT) <---- 현재 차량의 가속도 정보 (Longitudinal Axis)
    ptrBsm->coreData.accelSet.vert = 0;        // (INPUT) <---- 현재 차량의 가속도 정보 (Vertical Axis)
    ptrBsm->coreData.accelSet.yaw = 0;         // (INPUT) <---- 현재 차량의 가속도 정보 (Yaw rate)

    ptrBsm->coreData.brakes.wheelBrakes.size = 1;
    ptrBsm->coreData.brakes.wheelBrakes.buf = (uint8_t *)malloc(1);
    ptrBsm->coreData.brakes.wheelBrakes.bits_unused = 3;
    *(ptrBsm->coreData.brakes.wheelBrakes.buf) = 0b10000000; // (INPUT) <---- 현재 차량의 휠브레이크 상태

    ptrBsm->coreData.brakes.abs = 0;        // (INPUT) <---- 현재 차량의 ABS 브레이크 상태
    ptrBsm->coreData.brakes.auxBrakes = 0;  // (INPUT) <---- 현재 차량의 주차 브레이크 상태
    ptrBsm->coreData.brakes.brakeBoost = 0; // (INPUT) <---- 현재 차량의 브레이크 Boost 활성 상태
    ptrBsm->coreData.brakes.scs = 0;        // (INPUT) <---- 현재 차량의 SCS 상태
    ptrBsm->coreData.brakes.traction = 0;   // (INPUT) <---- 현재 차량의 TCS 상태

    ptrBsm->coreData.size.length = 0; // (INPUT) <---- 차량의 길이
    ptrBsm->coreData.size.width = 0;  // (INPUT) <---- 차량의 너비

    ptrBsm->partII = NULL;   // <----- OPTION, not to use
    ptrBsm->regional = NULL; // <----- OPTION, not to use

    return 0;
}

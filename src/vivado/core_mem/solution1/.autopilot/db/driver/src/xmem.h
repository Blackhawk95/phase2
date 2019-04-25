// ==============================================================
// File generated on Tue Apr 09 13:16:47 +0530 2019
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XMEM_H
#define XMEM_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xmem_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Crtl_bus_BaseAddress;
} XMem_Config;
#endif

typedef struct {
    u32 Crtl_bus_BaseAddress;
    u32 IsReady;
} XMem;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XMem_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XMem_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XMem_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XMem_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XMem_Initialize(XMem *InstancePtr, u16 DeviceId);
XMem_Config* XMem_LookupConfig(u16 DeviceId);
int XMem_CfgInitialize(XMem *InstancePtr, XMem_Config *ConfigPtr);
#else
int XMem_Initialize(XMem *InstancePtr, const char* InstanceName);
int XMem_Release(XMem *InstancePtr);
#endif

void XMem_Start(XMem *InstancePtr);
u32 XMem_IsDone(XMem *InstancePtr);
u32 XMem_IsIdle(XMem *InstancePtr);
u32 XMem_IsReady(XMem *InstancePtr);
void XMem_EnableAutoRestart(XMem *InstancePtr);
void XMem_DisableAutoRestart(XMem *InstancePtr);

void XMem_Set_a(XMem *InstancePtr, u64 Data);
u64 XMem_Get_a(XMem *InstancePtr);
void XMem_Set_ma(XMem *InstancePtr, u32 Data);
u32 XMem_Get_ma(XMem *InstancePtr);
void XMem_Set_data_i(XMem *InstancePtr, u32 Data);
u32 XMem_Get_data_i(XMem *InstancePtr);
u32 XMem_Get_data_o(XMem *InstancePtr);
u32 XMem_Get_data_o_vld(XMem *InstancePtr);
void XMem_Set_flag(XMem *InstancePtr, u32 Data);
u32 XMem_Get_flag(XMem *InstancePtr);

void XMem_InterruptGlobalEnable(XMem *InstancePtr);
void XMem_InterruptGlobalDisable(XMem *InstancePtr);
void XMem_InterruptEnable(XMem *InstancePtr, u32 Mask);
void XMem_InterruptDisable(XMem *InstancePtr, u32 Mask);
void XMem_InterruptClear(XMem *InstancePtr, u32 Mask);
u32 XMem_InterruptGetEnabled(XMem *InstancePtr);
u32 XMem_InterruptGetStatus(XMem *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif

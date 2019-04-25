// ==============================================================
// File generated on Tue Apr 09 13:16:47 +0530 2019
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xmem.h"

extern XMem_Config XMem_ConfigTable[];

XMem_Config *XMem_LookupConfig(u16 DeviceId) {
	XMem_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XMEM_NUM_INSTANCES; Index++) {
		if (XMem_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XMem_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XMem_Initialize(XMem *InstancePtr, u16 DeviceId) {
	XMem_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XMem_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XMem_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif


// ==============================================================
// File generated on Wed Apr 03 13:02:10 +0530 2019
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xmem.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XMem_CfgInitialize(XMem *InstancePtr, XMem_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Crtl_bus_BaseAddress = ConfigPtr->Crtl_bus_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XMem_Start(XMem *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMem_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_AP_CTRL) & 0x80;
    XMem_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_AP_CTRL, Data | 0x01);
}

u32 XMem_IsDone(XMem *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMem_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XMem_IsIdle(XMem *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMem_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XMem_IsReady(XMem *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMem_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XMem_EnableAutoRestart(XMem *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMem_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_AP_CTRL, 0x80);
}

void XMem_DisableAutoRestart(XMem *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMem_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_AP_CTRL, 0);
}

void XMem_Set_a_V(XMem *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMem_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_A_V_DATA, Data);
}

u32 XMem_Get_a_V(XMem *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMem_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_A_V_DATA);
    return Data;
}

void XMem_Set_ma_V(XMem *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMem_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_MA_V_DATA, Data);
}

u32 XMem_Get_ma_V(XMem *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMem_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_MA_V_DATA);
    return Data;
}

void XMem_Set_data_V_i(XMem *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMem_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_DATA_V_I_DATA, Data);
}

u32 XMem_Get_data_V_i(XMem *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMem_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_DATA_V_I_DATA);
    return Data;
}

u32 XMem_Get_data_V_o(XMem *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMem_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_DATA_V_O_DATA);
    return Data;
}

u32 XMem_Get_data_V_o_vld(XMem *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMem_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_DATA_V_O_CTRL);
    return Data & 0x1;
}

void XMem_Set_flag_V(XMem *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMem_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_FLAG_V_DATA, Data);
}

u32 XMem_Get_flag_V(XMem *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMem_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_FLAG_V_DATA);
    return Data;
}

void XMem_InterruptGlobalEnable(XMem *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMem_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_GIE, 1);
}

void XMem_InterruptGlobalDisable(XMem *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMem_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_GIE, 0);
}

void XMem_InterruptEnable(XMem *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMem_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_IER);
    XMem_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_IER, Register | Mask);
}

void XMem_InterruptDisable(XMem *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMem_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_IER);
    XMem_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_IER, Register & (~Mask));
}

void XMem_InterruptClear(XMem *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMem_WriteReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_ISR, Mask);
}

u32 XMem_InterruptGetEnabled(XMem *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMem_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_IER);
}

u32 XMem_InterruptGetStatus(XMem *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMem_ReadReg(InstancePtr->Crtl_bus_BaseAddress, XMEM_CRTL_BUS_ADDR_ISR);
}


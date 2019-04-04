// ==============================================================
// File generated on Wed Apr 03 13:02:10 +0530 2019
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// CRTL_BUS
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x10 : Data signal of a_V
//        bit 15~0 - a_V[15:0] (Read/Write)
//        others   - reserved
// 0x14 : reserved
// 0x18 : Data signal of ma_V
//        bit 7~0 - ma_V[7:0] (Read/Write)
//        others  - reserved
// 0x1c : reserved
// 0x20 : Data signal of data_V_i
//        bit 7~0 - data_V_i[7:0] (Read/Write)
//        others  - reserved
// 0x24 : reserved
// 0x28 : Data signal of data_V_o
//        bit 7~0 - data_V_o[7:0] (Read)
//        others  - reserved
// 0x2c : Control signal of data_V_o
//        bit 0  - data_V_o_ap_vld (Read/COR)
//        others - reserved
// 0x30 : Data signal of flag_V
//        bit 7~0 - flag_V[7:0] (Read/Write)
//        others  - reserved
// 0x34 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XMEM_CRTL_BUS_ADDR_AP_CTRL       0x00
#define XMEM_CRTL_BUS_ADDR_GIE           0x04
#define XMEM_CRTL_BUS_ADDR_IER           0x08
#define XMEM_CRTL_BUS_ADDR_ISR           0x0c
#define XMEM_CRTL_BUS_ADDR_A_V_DATA      0x10
#define XMEM_CRTL_BUS_BITS_A_V_DATA      16
#define XMEM_CRTL_BUS_ADDR_MA_V_DATA     0x18
#define XMEM_CRTL_BUS_BITS_MA_V_DATA     8
#define XMEM_CRTL_BUS_ADDR_DATA_V_I_DATA 0x20
#define XMEM_CRTL_BUS_BITS_DATA_V_I_DATA 8
#define XMEM_CRTL_BUS_ADDR_DATA_V_O_DATA 0x28
#define XMEM_CRTL_BUS_BITS_DATA_V_O_DATA 8
#define XMEM_CRTL_BUS_ADDR_DATA_V_O_CTRL 0x2c
#define XMEM_CRTL_BUS_ADDR_FLAG_V_DATA   0x30
#define XMEM_CRTL_BUS_BITS_FLAG_V_DATA   8


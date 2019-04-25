// ==============================================================
// File generated on Tue Apr 09 13:16:47 +0530 2019
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
// 0x10 : Data signal of a
//        bit 31~0 - a[31:0] (Read/Write)
// 0x14 : Data signal of a
//        bit 31~0 - a[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of ma
//        bit 31~0 - ma[31:0] (Read/Write)
// 0x20 : reserved
// 0x24 : Data signal of data_i
//        bit 31~0 - data_i[31:0] (Read/Write)
// 0x28 : reserved
// 0x2c : Data signal of data_o
//        bit 31~0 - data_o[31:0] (Read)
// 0x30 : Control signal of data_o
//        bit 0  - data_o_ap_vld (Read/COR)
//        others - reserved
// 0x34 : Data signal of flag
//        bit 31~0 - flag[31:0] (Read/Write)
// 0x38 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XMEM_CRTL_BUS_ADDR_AP_CTRL     0x00
#define XMEM_CRTL_BUS_ADDR_GIE         0x04
#define XMEM_CRTL_BUS_ADDR_IER         0x08
#define XMEM_CRTL_BUS_ADDR_ISR         0x0c
#define XMEM_CRTL_BUS_ADDR_A_DATA      0x10
#define XMEM_CRTL_BUS_BITS_A_DATA      64
#define XMEM_CRTL_BUS_ADDR_MA_DATA     0x1c
#define XMEM_CRTL_BUS_BITS_MA_DATA     32
#define XMEM_CRTL_BUS_ADDR_DATA_I_DATA 0x24
#define XMEM_CRTL_BUS_BITS_DATA_I_DATA 32
#define XMEM_CRTL_BUS_ADDR_DATA_O_DATA 0x2c
#define XMEM_CRTL_BUS_BITS_DATA_O_DATA 32
#define XMEM_CRTL_BUS_ADDR_DATA_O_CTRL 0x30
#define XMEM_CRTL_BUS_ADDR_FLAG_DATA   0x34
#define XMEM_CRTL_BUS_BITS_FLAG_DATA   32


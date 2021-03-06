// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2018.3
// Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#include "mem.h"
#include "AESL_pkg.h"

using namespace std;

namespace ap_rtl {

const sc_logic mem::ap_const_logic_1 = sc_dt::Log_1;
const sc_logic mem::ap_const_logic_0 = sc_dt::Log_0;
const sc_lv<2> mem::ap_ST_fsm_state1 = "1";
const sc_lv<2> mem::ap_ST_fsm_state2 = "10";
const sc_lv<32> mem::ap_const_lv32_0 = "00000000000000000000000000000000";
const int mem::C_S_AXI_DATA_WIDTH = "100000";
const sc_lv<1> mem::ap_const_lv1_0 = "0";
const sc_lv<1> mem::ap_const_lv1_1 = "1";
const sc_lv<32> mem::ap_const_lv32_1 = "1";
const bool mem::ap_const_boolean_1 = true;

mem::mem(sc_module_name name) : sc_module(name), mVcdFile(0) {
    nvm_U = new mem_nvm("nvm_U");
    nvm_U->clk(ap_clk);
    nvm_U->reset(ap_rst_n_inv);
    nvm_U->address0(nvm_address0);
    nvm_U->ce0(nvm_ce0);
    nvm_U->we0(nvm_we0);
    nvm_U->d0(dram_q0);
    nvm_U->q0(nvm_q0);
    dram_U = new mem_dram("dram_U");
    dram_U->clk(ap_clk);
    dram_U->reset(ap_rst_n_inv);
    dram_U->address0(dram_address0);
    dram_U->ce0(dram_ce0);
    dram_U->we0(dram_we0);
    dram_U->d0(data_i);
    dram_U->q0(dram_q0);
    mem_CRTL_BUS_s_axi_U = new mem_CRTL_BUS_s_axi<C_S_AXI_CRTL_BUS_ADDR_WIDTH,C_S_AXI_CRTL_BUS_DATA_WIDTH>("mem_CRTL_BUS_s_axi_U");
    mem_CRTL_BUS_s_axi_U->AWVALID(s_axi_CRTL_BUS_AWVALID);
    mem_CRTL_BUS_s_axi_U->AWREADY(s_axi_CRTL_BUS_AWREADY);
    mem_CRTL_BUS_s_axi_U->AWADDR(s_axi_CRTL_BUS_AWADDR);
    mem_CRTL_BUS_s_axi_U->WVALID(s_axi_CRTL_BUS_WVALID);
    mem_CRTL_BUS_s_axi_U->WREADY(s_axi_CRTL_BUS_WREADY);
    mem_CRTL_BUS_s_axi_U->WDATA(s_axi_CRTL_BUS_WDATA);
    mem_CRTL_BUS_s_axi_U->WSTRB(s_axi_CRTL_BUS_WSTRB);
    mem_CRTL_BUS_s_axi_U->ARVALID(s_axi_CRTL_BUS_ARVALID);
    mem_CRTL_BUS_s_axi_U->ARREADY(s_axi_CRTL_BUS_ARREADY);
    mem_CRTL_BUS_s_axi_U->ARADDR(s_axi_CRTL_BUS_ARADDR);
    mem_CRTL_BUS_s_axi_U->RVALID(s_axi_CRTL_BUS_RVALID);
    mem_CRTL_BUS_s_axi_U->RREADY(s_axi_CRTL_BUS_RREADY);
    mem_CRTL_BUS_s_axi_U->RDATA(s_axi_CRTL_BUS_RDATA);
    mem_CRTL_BUS_s_axi_U->RRESP(s_axi_CRTL_BUS_RRESP);
    mem_CRTL_BUS_s_axi_U->BVALID(s_axi_CRTL_BUS_BVALID);
    mem_CRTL_BUS_s_axi_U->BREADY(s_axi_CRTL_BUS_BREADY);
    mem_CRTL_BUS_s_axi_U->BRESP(s_axi_CRTL_BUS_BRESP);
    mem_CRTL_BUS_s_axi_U->ACLK(ap_clk);
    mem_CRTL_BUS_s_axi_U->ARESET(ap_rst_n_inv);
    mem_CRTL_BUS_s_axi_U->ACLK_EN(ap_var_for_const0);
    mem_CRTL_BUS_s_axi_U->ap_start(ap_start);
    mem_CRTL_BUS_s_axi_U->interrupt(interrupt);
    mem_CRTL_BUS_s_axi_U->ap_ready(ap_ready);
    mem_CRTL_BUS_s_axi_U->ap_done(ap_done);
    mem_CRTL_BUS_s_axi_U->ap_idle(ap_idle);
    mem_CRTL_BUS_s_axi_U->a(a);
    mem_CRTL_BUS_s_axi_U->ma(ma);
    mem_CRTL_BUS_s_axi_U->data_o(data_o);
    mem_CRTL_BUS_s_axi_U->data_o_ap_vld(data_o_ap_vld);
    mem_CRTL_BUS_s_axi_U->data_i(data_i);
    mem_CRTL_BUS_s_axi_U->flag(flag);

    SC_METHOD(thread_ap_clk_no_reset_);
    dont_initialize();
    sensitive << ( ap_clk.pos() );

    SC_METHOD(thread_ap_CS_fsm_state1);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_CS_fsm_state2);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_done);
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_ap_idle);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm_state1 );

    SC_METHOD(thread_ap_ready);
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_ap_rst_n_inv);
    sensitive << ( ap_rst_n );

    SC_METHOD(thread_data_o);
    sensitive << ( data_i );
    sensitive << ( tmp_reg_172 );
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( storemerge_fu_159_p3 );

    SC_METHOD(thread_data_o_ap_vld);
    sensitive << ( tmp_reg_172 );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_dram_address0);
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( tmp_fu_132_p1 );
    sensitive << ( tmp_1_fu_136_p3 );
    sensitive << ( tmp_6_fu_144_p1 );
    sensitive << ( tmp_7_fu_149_p1 );
    sensitive << ( tmp_8_fu_154_p1 );

    SC_METHOD(thread_dram_ce0);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( tmp_fu_132_p1 );
    sensitive << ( tmp_1_fu_136_p3 );

    SC_METHOD(thread_dram_we0);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( tmp_fu_132_p1 );
    sensitive << ( tmp_1_fu_136_p3 );

    SC_METHOD(thread_nvm_address0);
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( a );
    sensitive << ( a_read_reg_167 );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_nvm_ce0);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_nvm_we0);
    sensitive << ( tmp_reg_172 );
    sensitive << ( tmp_1_reg_176 );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_storemerge_fu_159_p3);
    sensitive << ( nvm_q0 );
    sensitive << ( dram_q0 );
    sensitive << ( tmp_1_reg_176 );

    SC_METHOD(thread_tmp_1_fu_136_p3);
    sensitive << ( flag );

    SC_METHOD(thread_tmp_6_fu_144_p0);
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( ma );

    SC_METHOD(thread_tmp_6_fu_144_p1);
    sensitive << ( tmp_6_fu_144_p0 );

    SC_METHOD(thread_tmp_7_fu_149_p0);
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( ma );

    SC_METHOD(thread_tmp_7_fu_149_p1);
    sensitive << ( tmp_7_fu_149_p0 );

    SC_METHOD(thread_tmp_8_fu_154_p0);
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( ma );

    SC_METHOD(thread_tmp_8_fu_154_p1);
    sensitive << ( tmp_8_fu_154_p0 );

    SC_METHOD(thread_tmp_fu_132_p1);
    sensitive << ( flag );

    SC_METHOD(thread_ap_NS_fsm);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm );
    sensitive << ( ap_CS_fsm_state1 );

    SC_THREAD(thread_hdltv_gen);
    sensitive << ( ap_clk.pos() );

    SC_THREAD(thread_ap_var_for_const0);

    ap_CS_fsm = "01";
    static int apTFileNum = 0;
    stringstream apTFilenSS;
    apTFilenSS << "mem_sc_trace_" << apTFileNum ++;
    string apTFn = apTFilenSS.str();
    mVcdFile = sc_create_vcd_trace_file(apTFn.c_str());
    mVcdFile->set_time_unit(1, SC_PS);
    if (1) {
#ifdef __HLS_TRACE_LEVEL_PORT__
    sc_trace(mVcdFile, ap_clk, "(port)ap_clk");
    sc_trace(mVcdFile, ap_rst_n, "(port)ap_rst_n");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_AWVALID, "(port)s_axi_CRTL_BUS_AWVALID");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_AWREADY, "(port)s_axi_CRTL_BUS_AWREADY");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_AWADDR, "(port)s_axi_CRTL_BUS_AWADDR");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_WVALID, "(port)s_axi_CRTL_BUS_WVALID");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_WREADY, "(port)s_axi_CRTL_BUS_WREADY");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_WDATA, "(port)s_axi_CRTL_BUS_WDATA");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_WSTRB, "(port)s_axi_CRTL_BUS_WSTRB");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_ARVALID, "(port)s_axi_CRTL_BUS_ARVALID");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_ARREADY, "(port)s_axi_CRTL_BUS_ARREADY");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_ARADDR, "(port)s_axi_CRTL_BUS_ARADDR");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_RVALID, "(port)s_axi_CRTL_BUS_RVALID");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_RREADY, "(port)s_axi_CRTL_BUS_RREADY");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_RDATA, "(port)s_axi_CRTL_BUS_RDATA");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_RRESP, "(port)s_axi_CRTL_BUS_RRESP");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_BVALID, "(port)s_axi_CRTL_BUS_BVALID");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_BREADY, "(port)s_axi_CRTL_BUS_BREADY");
    sc_trace(mVcdFile, s_axi_CRTL_BUS_BRESP, "(port)s_axi_CRTL_BUS_BRESP");
    sc_trace(mVcdFile, interrupt, "(port)interrupt");
#endif
#ifdef __HLS_TRACE_LEVEL_INT__
    sc_trace(mVcdFile, ap_rst_n_inv, "ap_rst_n_inv");
    sc_trace(mVcdFile, ap_start, "ap_start");
    sc_trace(mVcdFile, ap_done, "ap_done");
    sc_trace(mVcdFile, ap_idle, "ap_idle");
    sc_trace(mVcdFile, ap_CS_fsm, "ap_CS_fsm");
    sc_trace(mVcdFile, ap_CS_fsm_state1, "ap_CS_fsm_state1");
    sc_trace(mVcdFile, ap_ready, "ap_ready");
    sc_trace(mVcdFile, a, "a");
    sc_trace(mVcdFile, ma, "ma");
    sc_trace(mVcdFile, data_i, "data_i");
    sc_trace(mVcdFile, data_o, "data_o");
    sc_trace(mVcdFile, data_o_ap_vld, "data_o_ap_vld");
    sc_trace(mVcdFile, flag, "flag");
    sc_trace(mVcdFile, nvm_address0, "nvm_address0");
    sc_trace(mVcdFile, nvm_ce0, "nvm_ce0");
    sc_trace(mVcdFile, nvm_we0, "nvm_we0");
    sc_trace(mVcdFile, nvm_q0, "nvm_q0");
    sc_trace(mVcdFile, dram_address0, "dram_address0");
    sc_trace(mVcdFile, dram_ce0, "dram_ce0");
    sc_trace(mVcdFile, dram_we0, "dram_we0");
    sc_trace(mVcdFile, dram_q0, "dram_q0");
    sc_trace(mVcdFile, a_read_reg_167, "a_read_reg_167");
    sc_trace(mVcdFile, tmp_fu_132_p1, "tmp_fu_132_p1");
    sc_trace(mVcdFile, tmp_reg_172, "tmp_reg_172");
    sc_trace(mVcdFile, tmp_1_fu_136_p3, "tmp_1_fu_136_p3");
    sc_trace(mVcdFile, tmp_1_reg_176, "tmp_1_reg_176");
    sc_trace(mVcdFile, tmp_6_fu_144_p1, "tmp_6_fu_144_p1");
    sc_trace(mVcdFile, tmp_7_fu_149_p1, "tmp_7_fu_149_p1");
    sc_trace(mVcdFile, tmp_8_fu_154_p1, "tmp_8_fu_154_p1");
    sc_trace(mVcdFile, ap_CS_fsm_state2, "ap_CS_fsm_state2");
    sc_trace(mVcdFile, storemerge_fu_159_p3, "storemerge_fu_159_p3");
    sc_trace(mVcdFile, tmp_6_fu_144_p0, "tmp_6_fu_144_p0");
    sc_trace(mVcdFile, tmp_7_fu_149_p0, "tmp_7_fu_149_p0");
    sc_trace(mVcdFile, tmp_8_fu_154_p0, "tmp_8_fu_154_p0");
    sc_trace(mVcdFile, ap_NS_fsm, "ap_NS_fsm");
#endif

    }
    mHdltvinHandle.open("mem.hdltvin.dat");
    mHdltvoutHandle.open("mem.hdltvout.dat");
}

mem::~mem() {
    if (mVcdFile) 
        sc_close_vcd_trace_file(mVcdFile);

    mHdltvinHandle << "] " << endl;
    mHdltvoutHandle << "] " << endl;
    mHdltvinHandle.close();
    mHdltvoutHandle.close();
    delete nvm_U;
    delete dram_U;
    delete mem_CRTL_BUS_s_axi_U;
}

void mem::thread_ap_var_for_const0() {
    ap_var_for_const0 = ap_const_logic_1;
}

void mem::thread_ap_clk_no_reset_() {
    if ( ap_rst_n_inv.read() == ap_const_logic_1) {
        ap_CS_fsm = ap_ST_fsm_state1;
    } else {
        ap_CS_fsm = ap_NS_fsm.read();
    }
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1))) {
        a_read_reg_167 = a.read();
        tmp_1_reg_176 = flag.read().range(1, 1);
        tmp_reg_172 = tmp_fu_132_p1.read();
    }
}

void mem::thread_ap_CS_fsm_state1() {
    ap_CS_fsm_state1 = ap_CS_fsm.read()[0];
}

void mem::thread_ap_CS_fsm_state2() {
    ap_CS_fsm_state2 = ap_CS_fsm.read()[1];
}

void mem::thread_ap_done() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        ap_done = ap_const_logic_1;
    } else {
        ap_done = ap_const_logic_0;
    }
}

void mem::thread_ap_idle() {
    if ((esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) && 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()))) {
        ap_idle = ap_const_logic_1;
    } else {
        ap_idle = ap_const_logic_0;
    }
}

void mem::thread_ap_ready() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        ap_ready = ap_const_logic_1;
    } else {
        ap_ready = ap_const_logic_0;
    }
}

void mem::thread_ap_rst_n_inv() {
    ap_rst_n_inv =  (sc_logic) (~ap_rst_n.read());
}

void mem::thread_data_o() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
         esl_seteq<1,1,1>(tmp_reg_172.read(), ap_const_lv1_1))) {
        data_o = storemerge_fu_159_p3.read();
    } else {
        data_o = data_i.read();
    }
}

void mem::thread_data_o_ap_vld() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
         esl_seteq<1,1,1>(tmp_reg_172.read(), ap_const_lv1_1))) {
        data_o_ap_vld = ap_const_logic_1;
    } else {
        data_o_ap_vld = ap_const_logic_0;
    }
}

void mem::thread_dram_address0() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read())) {
        if (esl_seteq<1,1,1>(tmp_fu_132_p1.read(), ap_const_lv1_1)) {
            dram_address0 =  (sc_lv<6>) (tmp_8_fu_154_p1.read());
        } else if ((esl_seteq<1,1,1>(tmp_fu_132_p1.read(), ap_const_lv1_0) && 
                    esl_seteq<1,1,1>(tmp_1_fu_136_p3.read(), ap_const_lv1_1))) {
            dram_address0 =  (sc_lv<6>) (tmp_7_fu_149_p1.read());
        } else if ((esl_seteq<1,1,1>(tmp_fu_132_p1.read(), ap_const_lv1_0) && 
                    esl_seteq<1,1,1>(tmp_1_fu_136_p3.read(), ap_const_lv1_0))) {
            dram_address0 =  (sc_lv<6>) (tmp_6_fu_144_p1.read());
        } else {
            dram_address0 = "XXXXXX";
        }
    } else {
        dram_address0 = "XXXXXX";
    }
}

void mem::thread_dram_ce0() {
    if (((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
          esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1) && 
          esl_seteq<1,1,1>(tmp_fu_132_p1.read(), ap_const_lv1_0) && 
          esl_seteq<1,1,1>(tmp_1_fu_136_p3.read(), ap_const_lv1_0)) || 
         (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
          esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1) && 
          esl_seteq<1,1,1>(tmp_fu_132_p1.read(), ap_const_lv1_1)) || 
         (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
          esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1) && 
          esl_seteq<1,1,1>(tmp_fu_132_p1.read(), ap_const_lv1_0) && 
          esl_seteq<1,1,1>(tmp_1_fu_136_p3.read(), ap_const_lv1_1)))) {
        dram_ce0 = ap_const_logic_1;
    } else {
        dram_ce0 = ap_const_logic_0;
    }
}

void mem::thread_dram_we0() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
         esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1) && 
         esl_seteq<1,1,1>(tmp_fu_132_p1.read(), ap_const_lv1_0) && 
         esl_seteq<1,1,1>(tmp_1_fu_136_p3.read(), ap_const_lv1_1))) {
        dram_we0 = ap_const_logic_1;
    } else {
        dram_we0 = ap_const_logic_0;
    }
}

void mem::thread_nvm_address0() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        nvm_address0 =  (sc_lv<16>) (a_read_reg_167.read());
    } else if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read())) {
        nvm_address0 =  (sc_lv<16>) (a.read());
    } else {
        nvm_address0 =  (sc_lv<16>) ("XXXXXXXXXXXXXXXX");
    }
}

void mem::thread_nvm_ce0() {
    if (((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
          esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1)) || 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()))) {
        nvm_ce0 = ap_const_logic_1;
    } else {
        nvm_ce0 = ap_const_logic_0;
    }
}

void mem::thread_nvm_we0() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
         esl_seteq<1,1,1>(tmp_reg_172.read(), ap_const_lv1_0) && 
         esl_seteq<1,1,1>(tmp_1_reg_176.read(), ap_const_lv1_0))) {
        nvm_we0 = ap_const_logic_1;
    } else {
        nvm_we0 = ap_const_logic_0;
    }
}

void mem::thread_storemerge_fu_159_p3() {
    storemerge_fu_159_p3 = (!tmp_1_reg_176.read()[0].is_01())? sc_lv<32>(): ((tmp_1_reg_176.read()[0].to_bool())? dram_q0.read(): nvm_q0.read());
}

void mem::thread_tmp_1_fu_136_p3() {
    tmp_1_fu_136_p3 = flag.read().range(1, 1);
}

void mem::thread_tmp_6_fu_144_p0() {
    tmp_6_fu_144_p0 = ma.read();
}

void mem::thread_tmp_6_fu_144_p1() {
    tmp_6_fu_144_p1 = esl_sext<64,32>(tmp_6_fu_144_p0.read());
}

void mem::thread_tmp_7_fu_149_p0() {
    tmp_7_fu_149_p0 = ma.read();
}

void mem::thread_tmp_7_fu_149_p1() {
    tmp_7_fu_149_p1 = esl_sext<64,32>(tmp_7_fu_149_p0.read());
}

void mem::thread_tmp_8_fu_154_p0() {
    tmp_8_fu_154_p0 = ma.read();
}

void mem::thread_tmp_8_fu_154_p1() {
    tmp_8_fu_154_p1 = esl_sext<64,32>(tmp_8_fu_154_p0.read());
}

void mem::thread_tmp_fu_132_p1() {
    tmp_fu_132_p1 = flag.read().range(1-1, 0);
}

void mem::thread_ap_NS_fsm() {
    switch (ap_CS_fsm.read().to_uint64()) {
        case 1 : 
            if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1))) {
                ap_NS_fsm = ap_ST_fsm_state2;
            } else {
                ap_NS_fsm = ap_ST_fsm_state1;
            }
            break;
        case 2 : 
            ap_NS_fsm = ap_ST_fsm_state1;
            break;
        default : 
            ap_NS_fsm =  (sc_lv<2>) ("XX");
            break;
    }
}

void mem::thread_hdltv_gen() {
    const char* dump_tv = std::getenv("AP_WRITE_TV");
    if (!(dump_tv && string(dump_tv) == "on")) return;

    wait();

    mHdltvinHandle << "[ " << endl;
    mHdltvoutHandle << "[ " << endl;
    int ap_cycleNo = 0;
    while (1) {
        wait();
        const char* mComma = ap_cycleNo == 0 ? " " : ", " ;
        mHdltvinHandle << mComma << "{"  <<  " \"ap_rst_n\" :  \"" << ap_rst_n.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"s_axi_CRTL_BUS_AWVALID\" :  \"" << s_axi_CRTL_BUS_AWVALID.read() << "\" ";
        mHdltvoutHandle << mComma << "{"  <<  " \"s_axi_CRTL_BUS_AWREADY\" :  \"" << s_axi_CRTL_BUS_AWREADY.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"s_axi_CRTL_BUS_AWADDR\" :  \"" << s_axi_CRTL_BUS_AWADDR.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"s_axi_CRTL_BUS_WVALID\" :  \"" << s_axi_CRTL_BUS_WVALID.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"s_axi_CRTL_BUS_WREADY\" :  \"" << s_axi_CRTL_BUS_WREADY.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"s_axi_CRTL_BUS_WDATA\" :  \"" << s_axi_CRTL_BUS_WDATA.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"s_axi_CRTL_BUS_WSTRB\" :  \"" << s_axi_CRTL_BUS_WSTRB.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"s_axi_CRTL_BUS_ARVALID\" :  \"" << s_axi_CRTL_BUS_ARVALID.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"s_axi_CRTL_BUS_ARREADY\" :  \"" << s_axi_CRTL_BUS_ARREADY.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"s_axi_CRTL_BUS_ARADDR\" :  \"" << s_axi_CRTL_BUS_ARADDR.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"s_axi_CRTL_BUS_RVALID\" :  \"" << s_axi_CRTL_BUS_RVALID.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"s_axi_CRTL_BUS_RREADY\" :  \"" << s_axi_CRTL_BUS_RREADY.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"s_axi_CRTL_BUS_RDATA\" :  \"" << s_axi_CRTL_BUS_RDATA.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"s_axi_CRTL_BUS_RRESP\" :  \"" << s_axi_CRTL_BUS_RRESP.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"s_axi_CRTL_BUS_BVALID\" :  \"" << s_axi_CRTL_BUS_BVALID.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"s_axi_CRTL_BUS_BREADY\" :  \"" << s_axi_CRTL_BUS_BREADY.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"s_axi_CRTL_BUS_BRESP\" :  \"" << s_axi_CRTL_BUS_BRESP.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"interrupt\" :  \"" << interrupt.read() << "\" ";
        mHdltvinHandle << "}" << std::endl;
        mHdltvoutHandle << "}" << std::endl;
        ap_cycleNo++;
    }
}

}


// ==============================================================
// File generated on Wed Apr 03 12:27:11 +0530 2019
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================

#define AP_INT_MAX_W 32678

#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;


// [dump_struct_tree [build_nameSpaceTree] dumpedStructList] ---------->


// [dump_enumeration [get_enumeration_list]] ---------->


// wrapc file define: "a_V"
#define AUTOTB_TVIN_a_V  "../tv/cdatafile/c.mem.autotvin_a_V.dat"
// wrapc file define: "ma_V"
#define AUTOTB_TVIN_ma_V  "../tv/cdatafile/c.mem.autotvin_ma_V.dat"
// wrapc file define: "data_V"
#define AUTOTB_TVIN_data_V  "../tv/cdatafile/c.mem.autotvin_data_V.dat"
#define AUTOTB_TVOUT_data_V  "../tv/cdatafile/c.mem.autotvout_data_V.dat"
// wrapc file define: "flag_V"
#define AUTOTB_TVIN_flag_V  "../tv/cdatafile/c.mem.autotvin_flag_V.dat"

#define INTER_TCL  "../tv/cdatafile/ref.tcl"

// tvout file define: "data_V"
#define AUTOTB_TVOUT_PC_data_V  "../tv/rtldatafile/rtl.mem.autotvout_data_V.dat"

class INTER_TCL_FILE {
	public:
		INTER_TCL_FILE(const char* name) {
			mName = name;
			a_V_depth = 0;
			ma_V_depth = 0;
			data_V_depth = 0;
			flag_V_depth = 0;
			trans_num =0;
		}

		~INTER_TCL_FILE() {
			mFile.open(mName);
			if (!mFile.good()) {
				cout << "Failed to open file ref.tcl" << endl;
				exit (1);
			}
			string total_list = get_depth_list();
			mFile << "set depth_list {\n";
			mFile << total_list;
			mFile << "}\n";
			mFile << "set trans_num "<<trans_num<<endl;
			mFile.close();
		}

		string get_depth_list () {
			stringstream total_list;
			total_list << "{a_V " << a_V_depth << "}\n";
			total_list << "{ma_V " << ma_V_depth << "}\n";
			total_list << "{data_V " << data_V_depth << "}\n";
			total_list << "{flag_V " << flag_V_depth << "}\n";
			return total_list.str();
		}

		void set_num (int num , int* class_num) {
			(*class_num) = (*class_num) > num ? (*class_num) : num;
		}
	public:
		int a_V_depth;
		int ma_V_depth;
		int data_V_depth;
		int flag_V_depth;
		int trans_num;

	private:
		ofstream mFile;
		const char* mName;
};

extern void mem (
ap_int<16> a,
ap_int<8> ma,
ap_int<8>* data,
ap_int<8> flag);

void AESL_WRAP_mem (
ap_int<16> a,
ap_int<8> ma,
ap_int<8>* data,
ap_int<8> flag)
{
	refine_signal_handler();
	fstream wrapc_switch_file_token;
	wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
	int AESL_i;
	if (wrapc_switch_file_token.good())
	{
		CodeState = ENTER_WRAPC_PC;
		static unsigned AESL_transaction_pc = 0;
		string AESL_token;
		string AESL_num;
		static AESL_FILE_HANDLER aesl_fh;


		// output port post check: "data_V"
		aesl_fh.read(AUTOTB_TVOUT_PC_data_V, AESL_token); // [[transaction]]
		if (AESL_token != "[[transaction]]")
		{
			exit(1);
		}
		aesl_fh.read(AUTOTB_TVOUT_PC_data_V, AESL_num); // transaction number

		if (atoi(AESL_num.c_str()) == AESL_transaction_pc)
		{
			aesl_fh.read(AUTOTB_TVOUT_PC_data_V, AESL_token); // data

			sc_bv<8> *data_V_pc_buffer = new sc_bv<8>[1];
			int i = 0;

			while (AESL_token != "[[/transaction]]")
			{
				bool no_x = false;
				bool err = false;

				// search and replace 'X' with "0" from the 1st char of token
				while (!no_x)
				{
					size_t x_found = AESL_token.find('X');
					if (x_found != string::npos)
					{
						if (!err)
						{
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'data_V', possible cause: There are uninitialized variables in the C design." << endl;
							err = true;
						}
						AESL_token.replace(x_found, 1, "0");
					}
					else
					{
						no_x = true;
					}
				}

				no_x = false;

				// search and replace 'x' with "0" from the 3rd char of token
				while (!no_x)
				{
					size_t x_found = AESL_token.find('x', 2);

					if (x_found != string::npos)
					{
						if (!err)
						{
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'data_V', possible cause: There are uninitialized variables in the C design." << endl;
							err = true;
						}
						AESL_token.replace(x_found, 1, "0");
					}
					else
					{
						no_x = true;
					}
				}

				// push token into output port buffer
				if (AESL_token != "")
				{
					data_V_pc_buffer[i] = AESL_token.c_str();
					i++;
				}

				aesl_fh.read(AUTOTB_TVOUT_PC_data_V, AESL_token); // data or [[/transaction]]

				if (AESL_token == "[[[/runtime]]]" || aesl_fh.eof(AUTOTB_TVOUT_PC_data_V))
				{
					exit(1);
				}
			}

			// ***********************************
			if (i > 0)
			{
				// RTL Name: data_V
				{
					// bitslice(7, 0)
					// {
						// celement: data.V(7, 0)
						// {
							sc_lv<8>* data_V_lv0_0_0_1 = new sc_lv<8>[1];
						// }
					// }

					// bitslice(7, 0)
					{
						int hls_map_index = 0;
						// celement: data.V(7, 0)
						{
							// carray: (0) => (0) @ (1)
							for (int i_0 = 0; i_0 <= 0; i_0 += 1)
							{
								if (&(data[0]) != NULL) // check the null address if the c port is array or others
								{
									data_V_lv0_0_0_1[hls_map_index].range(7, 0) = sc_bv<8>(data_V_pc_buffer[hls_map_index].range(7, 0));
									hls_map_index++;
								}
							}
						}
					}

					// bitslice(7, 0)
					{
						int hls_map_index = 0;
						// celement: data.V(7, 0)
						{
							// carray: (0) => (0) @ (1)
							for (int i_0 = 0; i_0 <= 0; i_0 += 1)
							{
								// sub                    : i_0
								// ori_name               : data[i_0]
								// sub_1st_elem           : 0
								// ori_name_1st_elem      : data[0]
								// output_left_conversion : data[i_0]
								// output_type_conversion : (data_V_lv0_0_0_1[hls_map_index]).to_string(SC_BIN).c_str()
								if (&(data[0]) != NULL) // check the null address if the c port is array or others
								{
									data[i_0] = (data_V_lv0_0_0_1[hls_map_index]).to_string(SC_BIN).c_str();
									hls_map_index++;
								}
							}
						}
					}
				}
			}

			// release memory allocation
			delete [] data_V_pc_buffer;
		}

		AESL_transaction_pc++;
	}
	else
	{
		CodeState = ENTER_WRAPC;
		static unsigned AESL_transaction;

		static AESL_FILE_HANDLER aesl_fh;

		// "a_V"
		char* tvin_a_V = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_a_V);

		// "ma_V"
		char* tvin_ma_V = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_ma_V);

		// "data_V"
		char* tvin_data_V = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_data_V);
		char* tvout_data_V = new char[50];
		aesl_fh.touch(AUTOTB_TVOUT_data_V);

		// "flag_V"
		char* tvin_flag_V = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_flag_V);

		CodeState = DUMP_INPUTS;
		static INTER_TCL_FILE tcl_file(INTER_TCL);
		int leading_zero;

		// [[transaction]]
		sprintf(tvin_a_V, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_a_V, tvin_a_V);

		sc_bv<16> a_V_tvin_wrapc_buffer;

		// RTL Name: a_V
		{
			// bitslice(15, 0)
			{
				// celement: a.V(15, 0)
				{
					// carray: (0) => (0) @ (0)
					{
						// sub                   : 
						// ori_name              : a
						// sub_1st_elem          : 
						// ori_name_1st_elem     : a
						// regulate_c_name       : a_V
						// input_type_conversion : (a).to_string(2).c_str()
						if (&(a) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<16> a_V_tmp_mem;
							a_V_tmp_mem = (a).to_string(2).c_str();
							a_V_tvin_wrapc_buffer.range(15, 0) = a_V_tmp_mem.range(15, 0);
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 1; i++)
		{
			sprintf(tvin_a_V, "%s\n", (a_V_tvin_wrapc_buffer).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_a_V, tvin_a_V);
		}

		tcl_file.set_num(1, &tcl_file.a_V_depth);
		sprintf(tvin_a_V, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_a_V, tvin_a_V);

		// [[transaction]]
		sprintf(tvin_ma_V, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_ma_V, tvin_ma_V);

		sc_bv<8> ma_V_tvin_wrapc_buffer;

		// RTL Name: ma_V
		{
			// bitslice(7, 0)
			{
				// celement: ma.V(7, 0)
				{
					// carray: (0) => (0) @ (0)
					{
						// sub                   : 
						// ori_name              : ma
						// sub_1st_elem          : 
						// ori_name_1st_elem     : ma
						// regulate_c_name       : ma_V
						// input_type_conversion : (ma).to_string(2).c_str()
						if (&(ma) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<8> ma_V_tmp_mem;
							ma_V_tmp_mem = (ma).to_string(2).c_str();
							ma_V_tvin_wrapc_buffer.range(7, 0) = ma_V_tmp_mem.range(7, 0);
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 1; i++)
		{
			sprintf(tvin_ma_V, "%s\n", (ma_V_tvin_wrapc_buffer).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_ma_V, tvin_ma_V);
		}

		tcl_file.set_num(1, &tcl_file.ma_V_depth);
		sprintf(tvin_ma_V, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_ma_V, tvin_ma_V);

		// [[transaction]]
		sprintf(tvin_data_V, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_data_V, tvin_data_V);

		sc_bv<8>* data_V_tvin_wrapc_buffer = new sc_bv<8>[1];

		// RTL Name: data_V
		{
			// bitslice(7, 0)
			{
				int hls_map_index = 0;
				// celement: data.V(7, 0)
				{
					// carray: (0) => (0) @ (1)
					for (int i_0 = 0; i_0 <= 0; i_0 += 1)
					{
						// sub                   : i_0
						// ori_name              : data[i_0]
						// sub_1st_elem          : 0
						// ori_name_1st_elem     : data[0]
						// regulate_c_name       : data_V
						// input_type_conversion : (data[i_0]).to_string(2).c_str()
						if (&(data[0]) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<8> data_V_tmp_mem;
							data_V_tmp_mem = (data[i_0]).to_string(2).c_str();
							data_V_tvin_wrapc_buffer[hls_map_index].range(7, 0) = data_V_tmp_mem.range(7, 0);
                                 	       hls_map_index++;
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 1; i++)
		{
			sprintf(tvin_data_V, "%s\n", (data_V_tvin_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_data_V, tvin_data_V);
		}

		tcl_file.set_num(1, &tcl_file.data_V_depth);
		sprintf(tvin_data_V, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_data_V, tvin_data_V);

		// release memory allocation
		delete [] data_V_tvin_wrapc_buffer;

		// [[transaction]]
		sprintf(tvin_flag_V, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_flag_V, tvin_flag_V);

		sc_bv<8> flag_V_tvin_wrapc_buffer;

		// RTL Name: flag_V
		{
			// bitslice(7, 0)
			{
				// celement: flag.V(7, 0)
				{
					// carray: (0) => (0) @ (0)
					{
						// sub                   : 
						// ori_name              : flag
						// sub_1st_elem          : 
						// ori_name_1st_elem     : flag
						// regulate_c_name       : flag_V
						// input_type_conversion : (flag).to_string(2).c_str()
						if (&(flag) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<8> flag_V_tmp_mem;
							flag_V_tmp_mem = (flag).to_string(2).c_str();
							flag_V_tvin_wrapc_buffer.range(7, 0) = flag_V_tmp_mem.range(7, 0);
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 1; i++)
		{
			sprintf(tvin_flag_V, "%s\n", (flag_V_tvin_wrapc_buffer).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_flag_V, tvin_flag_V);
		}

		tcl_file.set_num(1, &tcl_file.flag_V_depth);
		sprintf(tvin_flag_V, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_flag_V, tvin_flag_V);

// [call_c_dut] ---------->

		CodeState = CALL_C_DUT;
		mem(a, ma, data, flag);

		CodeState = DUMP_OUTPUTS;

		// [[transaction]]
		sprintf(tvout_data_V, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVOUT_data_V, tvout_data_V);

		sc_bv<8>* data_V_tvout_wrapc_buffer = new sc_bv<8>[1];

		// RTL Name: data_V
		{
			// bitslice(7, 0)
			{
				int hls_map_index = 0;
				// celement: data.V(7, 0)
				{
					// carray: (0) => (0) @ (1)
					for (int i_0 = 0; i_0 <= 0; i_0 += 1)
					{
						// sub                   : i_0
						// ori_name              : data[i_0]
						// sub_1st_elem          : 0
						// ori_name_1st_elem     : data[0]
						// regulate_c_name       : data_V
						// input_type_conversion : (data[i_0]).to_string(2).c_str()
						if (&(data[0]) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<8> data_V_tmp_mem;
							data_V_tmp_mem = (data[i_0]).to_string(2).c_str();
							data_V_tvout_wrapc_buffer[hls_map_index].range(7, 0) = data_V_tmp_mem.range(7, 0);
                                 	       hls_map_index++;
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 1; i++)
		{
			sprintf(tvout_data_V, "%s\n", (data_V_tvout_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVOUT_data_V, tvout_data_V);
		}

		tcl_file.set_num(1, &tcl_file.data_V_depth);
		sprintf(tvout_data_V, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVOUT_data_V, tvout_data_V);

		// release memory allocation
		delete [] data_V_tvout_wrapc_buffer;

		CodeState = DELETE_CHAR_BUFFERS;
		// release memory allocation: "a_V"
		delete [] tvin_a_V;
		// release memory allocation: "ma_V"
		delete [] tvin_ma_V;
		// release memory allocation: "data_V"
		delete [] tvin_data_V;
		delete [] tvout_data_V;
		// release memory allocation: "flag_V"
		delete [] tvin_flag_V;

		AESL_transaction++;

		tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
	}
}


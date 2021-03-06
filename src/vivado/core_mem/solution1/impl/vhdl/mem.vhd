-- ==============================================================
-- RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
-- Version: 2018.3
-- Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
-- 
-- ===========================================================

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity mem is
generic (
    C_S_AXI_CRTL_BUS_ADDR_WIDTH : INTEGER := 6;
    C_S_AXI_CRTL_BUS_DATA_WIDTH : INTEGER := 32 );
port (
    ap_clk : IN STD_LOGIC;
    ap_rst_n : IN STD_LOGIC;
    s_axi_CRTL_BUS_AWVALID : IN STD_LOGIC;
    s_axi_CRTL_BUS_AWREADY : OUT STD_LOGIC;
    s_axi_CRTL_BUS_AWADDR : IN STD_LOGIC_VECTOR (C_S_AXI_CRTL_BUS_ADDR_WIDTH-1 downto 0);
    s_axi_CRTL_BUS_WVALID : IN STD_LOGIC;
    s_axi_CRTL_BUS_WREADY : OUT STD_LOGIC;
    s_axi_CRTL_BUS_WDATA : IN STD_LOGIC_VECTOR (C_S_AXI_CRTL_BUS_DATA_WIDTH-1 downto 0);
    s_axi_CRTL_BUS_WSTRB : IN STD_LOGIC_VECTOR (C_S_AXI_CRTL_BUS_DATA_WIDTH/8-1 downto 0);
    s_axi_CRTL_BUS_ARVALID : IN STD_LOGIC;
    s_axi_CRTL_BUS_ARREADY : OUT STD_LOGIC;
    s_axi_CRTL_BUS_ARADDR : IN STD_LOGIC_VECTOR (C_S_AXI_CRTL_BUS_ADDR_WIDTH-1 downto 0);
    s_axi_CRTL_BUS_RVALID : OUT STD_LOGIC;
    s_axi_CRTL_BUS_RREADY : IN STD_LOGIC;
    s_axi_CRTL_BUS_RDATA : OUT STD_LOGIC_VECTOR (C_S_AXI_CRTL_BUS_DATA_WIDTH-1 downto 0);
    s_axi_CRTL_BUS_RRESP : OUT STD_LOGIC_VECTOR (1 downto 0);
    s_axi_CRTL_BUS_BVALID : OUT STD_LOGIC;
    s_axi_CRTL_BUS_BREADY : IN STD_LOGIC;
    s_axi_CRTL_BUS_BRESP : OUT STD_LOGIC_VECTOR (1 downto 0);
    interrupt : OUT STD_LOGIC );
end;


architecture behav of mem is 
    attribute CORE_GENERATION_INFO : STRING;
    attribute CORE_GENERATION_INFO of behav : architecture is
    "mem,hls_ip_2018_3,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xc7z020clg484-1,HLS_INPUT_CLOCK=10.000000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=6.508000,HLS_SYN_LAT=1,HLS_SYN_TPT=none,HLS_SYN_MEM=129,HLS_SYN_DSP=0,HLS_SYN_FF=326,HLS_SYN_LUT=516,HLS_VERSION=2018_3}";
    constant ap_const_logic_1 : STD_LOGIC := '1';
    constant ap_const_logic_0 : STD_LOGIC := '0';
    constant ap_ST_fsm_state1 : STD_LOGIC_VECTOR (1 downto 0) := "01";
    constant ap_ST_fsm_state2 : STD_LOGIC_VECTOR (1 downto 0) := "10";
    constant ap_const_lv32_0 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000000";
    constant C_S_AXI_DATA_WIDTH : INTEGER range 63 downto 0 := 20;
    constant ap_const_lv1_0 : STD_LOGIC_VECTOR (0 downto 0) := "0";
    constant ap_const_lv1_1 : STD_LOGIC_VECTOR (0 downto 0) := "1";
    constant ap_const_lv32_1 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000001";
    constant ap_const_boolean_1 : BOOLEAN := true;

    signal ap_rst_n_inv : STD_LOGIC;
    signal ap_start : STD_LOGIC;
    signal ap_done : STD_LOGIC;
    signal ap_idle : STD_LOGIC;
    signal ap_CS_fsm : STD_LOGIC_VECTOR (1 downto 0) := "01";
    attribute fsm_encoding : string;
    attribute fsm_encoding of ap_CS_fsm : signal is "none";
    signal ap_CS_fsm_state1 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state1 : signal is "none";
    signal ap_ready : STD_LOGIC;
    signal a : STD_LOGIC_VECTOR (63 downto 0);
    signal ma : STD_LOGIC_VECTOR (31 downto 0);
    signal data_i : STD_LOGIC_VECTOR (31 downto 0);
    signal data_o : STD_LOGIC_VECTOR (31 downto 0);
    signal data_o_ap_vld : STD_LOGIC;
    signal flag : STD_LOGIC_VECTOR (31 downto 0);
    signal nvm_address0 : STD_LOGIC_VECTOR (15 downto 0);
    signal nvm_ce0 : STD_LOGIC;
    signal nvm_we0 : STD_LOGIC;
    signal nvm_q0 : STD_LOGIC_VECTOR (31 downto 0);
    signal dram_address0 : STD_LOGIC_VECTOR (5 downto 0);
    signal dram_ce0 : STD_LOGIC;
    signal dram_we0 : STD_LOGIC;
    signal dram_q0 : STD_LOGIC_VECTOR (31 downto 0);
    signal a_read_reg_167 : STD_LOGIC_VECTOR (63 downto 0);
    signal tmp_fu_132_p1 : STD_LOGIC_VECTOR (0 downto 0);
    signal tmp_reg_172 : STD_LOGIC_VECTOR (0 downto 0);
    signal tmp_1_fu_136_p3 : STD_LOGIC_VECTOR (0 downto 0);
    signal tmp_1_reg_176 : STD_LOGIC_VECTOR (0 downto 0);
    signal tmp_6_fu_144_p1 : STD_LOGIC_VECTOR (63 downto 0);
    signal tmp_7_fu_149_p1 : STD_LOGIC_VECTOR (63 downto 0);
    signal tmp_8_fu_154_p1 : STD_LOGIC_VECTOR (63 downto 0);
    signal ap_CS_fsm_state2 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state2 : signal is "none";
    signal storemerge_fu_159_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal tmp_6_fu_144_p0 : STD_LOGIC_VECTOR (31 downto 0);
    signal tmp_7_fu_149_p0 : STD_LOGIC_VECTOR (31 downto 0);
    signal tmp_8_fu_154_p0 : STD_LOGIC_VECTOR (31 downto 0);
    signal ap_NS_fsm : STD_LOGIC_VECTOR (1 downto 0);

    component mem_nvm IS
    generic (
        DataWidth : INTEGER;
        AddressRange : INTEGER;
        AddressWidth : INTEGER );
    port (
        clk : IN STD_LOGIC;
        reset : IN STD_LOGIC;
        address0 : IN STD_LOGIC_VECTOR (15 downto 0);
        ce0 : IN STD_LOGIC;
        we0 : IN STD_LOGIC;
        d0 : IN STD_LOGIC_VECTOR (31 downto 0);
        q0 : OUT STD_LOGIC_VECTOR (31 downto 0) );
    end component;


    component mem_dram IS
    generic (
        DataWidth : INTEGER;
        AddressRange : INTEGER;
        AddressWidth : INTEGER );
    port (
        clk : IN STD_LOGIC;
        reset : IN STD_LOGIC;
        address0 : IN STD_LOGIC_VECTOR (5 downto 0);
        ce0 : IN STD_LOGIC;
        we0 : IN STD_LOGIC;
        d0 : IN STD_LOGIC_VECTOR (31 downto 0);
        q0 : OUT STD_LOGIC_VECTOR (31 downto 0) );
    end component;


    component mem_CRTL_BUS_s_axi IS
    generic (
        C_S_AXI_ADDR_WIDTH : INTEGER;
        C_S_AXI_DATA_WIDTH : INTEGER );
    port (
        AWVALID : IN STD_LOGIC;
        AWREADY : OUT STD_LOGIC;
        AWADDR : IN STD_LOGIC_VECTOR (C_S_AXI_ADDR_WIDTH-1 downto 0);
        WVALID : IN STD_LOGIC;
        WREADY : OUT STD_LOGIC;
        WDATA : IN STD_LOGIC_VECTOR (C_S_AXI_DATA_WIDTH-1 downto 0);
        WSTRB : IN STD_LOGIC_VECTOR (C_S_AXI_DATA_WIDTH/8-1 downto 0);
        ARVALID : IN STD_LOGIC;
        ARREADY : OUT STD_LOGIC;
        ARADDR : IN STD_LOGIC_VECTOR (C_S_AXI_ADDR_WIDTH-1 downto 0);
        RVALID : OUT STD_LOGIC;
        RREADY : IN STD_LOGIC;
        RDATA : OUT STD_LOGIC_VECTOR (C_S_AXI_DATA_WIDTH-1 downto 0);
        RRESP : OUT STD_LOGIC_VECTOR (1 downto 0);
        BVALID : OUT STD_LOGIC;
        BREADY : IN STD_LOGIC;
        BRESP : OUT STD_LOGIC_VECTOR (1 downto 0);
        ACLK : IN STD_LOGIC;
        ARESET : IN STD_LOGIC;
        ACLK_EN : IN STD_LOGIC;
        ap_start : OUT STD_LOGIC;
        interrupt : OUT STD_LOGIC;
        ap_ready : IN STD_LOGIC;
        ap_done : IN STD_LOGIC;
        ap_idle : IN STD_LOGIC;
        a : OUT STD_LOGIC_VECTOR (63 downto 0);
        ma : OUT STD_LOGIC_VECTOR (31 downto 0);
        data_o : IN STD_LOGIC_VECTOR (31 downto 0);
        data_o_ap_vld : IN STD_LOGIC;
        data_i : OUT STD_LOGIC_VECTOR (31 downto 0);
        flag : OUT STD_LOGIC_VECTOR (31 downto 0) );
    end component;



begin
    nvm_U : component mem_nvm
    generic map (
        DataWidth => 32,
        AddressRange => 65536,
        AddressWidth => 16)
    port map (
        clk => ap_clk,
        reset => ap_rst_n_inv,
        address0 => nvm_address0,
        ce0 => nvm_ce0,
        we0 => nvm_we0,
        d0 => dram_q0,
        q0 => nvm_q0);

    dram_U : component mem_dram
    generic map (
        DataWidth => 32,
        AddressRange => 64,
        AddressWidth => 6)
    port map (
        clk => ap_clk,
        reset => ap_rst_n_inv,
        address0 => dram_address0,
        ce0 => dram_ce0,
        we0 => dram_we0,
        d0 => data_i,
        q0 => dram_q0);

    mem_CRTL_BUS_s_axi_U : component mem_CRTL_BUS_s_axi
    generic map (
        C_S_AXI_ADDR_WIDTH => C_S_AXI_CRTL_BUS_ADDR_WIDTH,
        C_S_AXI_DATA_WIDTH => C_S_AXI_CRTL_BUS_DATA_WIDTH)
    port map (
        AWVALID => s_axi_CRTL_BUS_AWVALID,
        AWREADY => s_axi_CRTL_BUS_AWREADY,
        AWADDR => s_axi_CRTL_BUS_AWADDR,
        WVALID => s_axi_CRTL_BUS_WVALID,
        WREADY => s_axi_CRTL_BUS_WREADY,
        WDATA => s_axi_CRTL_BUS_WDATA,
        WSTRB => s_axi_CRTL_BUS_WSTRB,
        ARVALID => s_axi_CRTL_BUS_ARVALID,
        ARREADY => s_axi_CRTL_BUS_ARREADY,
        ARADDR => s_axi_CRTL_BUS_ARADDR,
        RVALID => s_axi_CRTL_BUS_RVALID,
        RREADY => s_axi_CRTL_BUS_RREADY,
        RDATA => s_axi_CRTL_BUS_RDATA,
        RRESP => s_axi_CRTL_BUS_RRESP,
        BVALID => s_axi_CRTL_BUS_BVALID,
        BREADY => s_axi_CRTL_BUS_BREADY,
        BRESP => s_axi_CRTL_BUS_BRESP,
        ACLK => ap_clk,
        ARESET => ap_rst_n_inv,
        ACLK_EN => ap_const_logic_1,
        ap_start => ap_start,
        interrupt => interrupt,
        ap_ready => ap_ready,
        ap_done => ap_done,
        ap_idle => ap_idle,
        a => a,
        ma => ma,
        data_o => data_o,
        data_o_ap_vld => data_o_ap_vld,
        data_i => data_i,
        flag => flag);





    ap_CS_fsm_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst_n_inv = '1') then
                ap_CS_fsm <= ap_ST_fsm_state1;
            else
                ap_CS_fsm <= ap_NS_fsm;
            end if;
        end if;
    end process;

    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_start = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_state1))) then
                a_read_reg_167 <= a;
                tmp_1_reg_176 <= flag(1 downto 1);
                tmp_reg_172 <= tmp_fu_132_p1;
            end if;
        end if;
    end process;

    ap_NS_fsm_assign_proc : process (ap_start, ap_CS_fsm, ap_CS_fsm_state1)
    begin
        case ap_CS_fsm is
            when ap_ST_fsm_state1 => 
                if (((ap_start = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_state1))) then
                    ap_NS_fsm <= ap_ST_fsm_state2;
                else
                    ap_NS_fsm <= ap_ST_fsm_state1;
                end if;
            when ap_ST_fsm_state2 => 
                ap_NS_fsm <= ap_ST_fsm_state1;
            when others =>  
                ap_NS_fsm <= "XX";
        end case;
    end process;
    ap_CS_fsm_state1 <= ap_CS_fsm(0);
    ap_CS_fsm_state2 <= ap_CS_fsm(1);

    ap_done_assign_proc : process(ap_CS_fsm_state2)
    begin
        if ((ap_const_logic_1 = ap_CS_fsm_state2)) then 
            ap_done <= ap_const_logic_1;
        else 
            ap_done <= ap_const_logic_0;
        end if; 
    end process;


    ap_idle_assign_proc : process(ap_start, ap_CS_fsm_state1)
    begin
        if (((ap_start = ap_const_logic_0) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
            ap_idle <= ap_const_logic_1;
        else 
            ap_idle <= ap_const_logic_0;
        end if; 
    end process;


    ap_ready_assign_proc : process(ap_CS_fsm_state2)
    begin
        if ((ap_const_logic_1 = ap_CS_fsm_state2)) then 
            ap_ready <= ap_const_logic_1;
        else 
            ap_ready <= ap_const_logic_0;
        end if; 
    end process;


    ap_rst_n_inv_assign_proc : process(ap_rst_n)
    begin
                ap_rst_n_inv <= not(ap_rst_n);
    end process;


    data_o_assign_proc : process(data_i, tmp_reg_172, ap_CS_fsm_state2, storemerge_fu_159_p3)
    begin
        if (((tmp_reg_172 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state2))) then 
            data_o <= storemerge_fu_159_p3;
        else 
            data_o <= data_i;
        end if; 
    end process;


    data_o_ap_vld_assign_proc : process(tmp_reg_172, ap_CS_fsm_state2)
    begin
        if (((tmp_reg_172 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state2))) then 
            data_o_ap_vld <= ap_const_logic_1;
        else 
            data_o_ap_vld <= ap_const_logic_0;
        end if; 
    end process;


    dram_address0_assign_proc : process(ap_CS_fsm_state1, tmp_fu_132_p1, tmp_1_fu_136_p3, tmp_6_fu_144_p1, tmp_7_fu_149_p1, tmp_8_fu_154_p1)
    begin
        if ((ap_const_logic_1 = ap_CS_fsm_state1)) then
            if ((tmp_fu_132_p1 = ap_const_lv1_1)) then 
                dram_address0 <= tmp_8_fu_154_p1(6 - 1 downto 0);
            elsif (((tmp_1_fu_136_p3 = ap_const_lv1_1) and (tmp_fu_132_p1 = ap_const_lv1_0))) then 
                dram_address0 <= tmp_7_fu_149_p1(6 - 1 downto 0);
            elsif (((tmp_1_fu_136_p3 = ap_const_lv1_0) and (tmp_fu_132_p1 = ap_const_lv1_0))) then 
                dram_address0 <= tmp_6_fu_144_p1(6 - 1 downto 0);
            else 
                dram_address0 <= "XXXXXX";
            end if;
        else 
            dram_address0 <= "XXXXXX";
        end if; 
    end process;


    dram_ce0_assign_proc : process(ap_start, ap_CS_fsm_state1, tmp_fu_132_p1, tmp_1_fu_136_p3)
    begin
        if ((((ap_start = ap_const_logic_1) and (tmp_1_fu_136_p3 = ap_const_lv1_0) and (tmp_fu_132_p1 = ap_const_lv1_0) and (ap_const_logic_1 = ap_CS_fsm_state1)) or ((ap_start = ap_const_logic_1) and (tmp_1_fu_136_p3 = ap_const_lv1_1) and (tmp_fu_132_p1 = ap_const_lv1_0) and (ap_const_logic_1 = ap_CS_fsm_state1)) or ((ap_start = ap_const_logic_1) and (tmp_fu_132_p1 = ap_const_lv1_1) and (ap_const_logic_1 = ap_CS_fsm_state1)))) then 
            dram_ce0 <= ap_const_logic_1;
        else 
            dram_ce0 <= ap_const_logic_0;
        end if; 
    end process;


    dram_we0_assign_proc : process(ap_start, ap_CS_fsm_state1, tmp_fu_132_p1, tmp_1_fu_136_p3)
    begin
        if (((ap_start = ap_const_logic_1) and (tmp_1_fu_136_p3 = ap_const_lv1_1) and (tmp_fu_132_p1 = ap_const_lv1_0) and (ap_const_logic_1 = ap_CS_fsm_state1))) then 
            dram_we0 <= ap_const_logic_1;
        else 
            dram_we0 <= ap_const_logic_0;
        end if; 
    end process;


    nvm_address0_assign_proc : process(ap_CS_fsm_state1, a, a_read_reg_167, ap_CS_fsm_state2)
    begin
        if ((ap_const_logic_1 = ap_CS_fsm_state2)) then 
            nvm_address0 <= a_read_reg_167(16 - 1 downto 0);
        elsif ((ap_const_logic_1 = ap_CS_fsm_state1)) then 
            nvm_address0 <= a(16 - 1 downto 0);
        else 
            nvm_address0 <= "XXXXXXXXXXXXXXXX";
        end if; 
    end process;


    nvm_ce0_assign_proc : process(ap_start, ap_CS_fsm_state1, ap_CS_fsm_state2)
    begin
        if (((ap_const_logic_1 = ap_CS_fsm_state2) or ((ap_start = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_state1)))) then 
            nvm_ce0 <= ap_const_logic_1;
        else 
            nvm_ce0 <= ap_const_logic_0;
        end if; 
    end process;


    nvm_we0_assign_proc : process(tmp_reg_172, tmp_1_reg_176, ap_CS_fsm_state2)
    begin
        if (((tmp_1_reg_176 = ap_const_lv1_0) and (tmp_reg_172 = ap_const_lv1_0) and (ap_const_logic_1 = ap_CS_fsm_state2))) then 
            nvm_we0 <= ap_const_logic_1;
        else 
            nvm_we0 <= ap_const_logic_0;
        end if; 
    end process;

    storemerge_fu_159_p3 <= 
        dram_q0 when (tmp_1_reg_176(0) = '1') else 
        nvm_q0;
    tmp_1_fu_136_p3 <= flag(1 downto 1);
    tmp_6_fu_144_p0 <= ma;
        tmp_6_fu_144_p1 <= std_logic_vector(IEEE.numeric_std.resize(signed(tmp_6_fu_144_p0),64));

    tmp_7_fu_149_p0 <= ma;
        tmp_7_fu_149_p1 <= std_logic_vector(IEEE.numeric_std.resize(signed(tmp_7_fu_149_p0),64));

    tmp_8_fu_154_p0 <= ma;
        tmp_8_fu_154_p1 <= std_logic_vector(IEEE.numeric_std.resize(signed(tmp_8_fu_154_p0),64));

    tmp_fu_132_p1 <= flag(1 - 1 downto 0);
end behav;

LIBRARY ieee;
USE ieee.std_logic_1164.all; 
USE ieee.std_logic_arith.all; 
USE ieee.std_logic_unsigned.all; 
ENTITY integration IS
   PORT (
		SW : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
      KEY : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
      CLOCK_50 : IN STD_LOGIC;
		LEDG : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
      DRAM_CLK, DRAM_CKE : OUT STD_LOGIC;
      DRAM_ADDR : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
      DRAM_BA_0, DRAM_BA_1 : BUFFER STD_LOGIC;
      DRAM_CS_N, DRAM_CAS_N, DRAM_RAS_N, DRAM_WE_N : OUT STD_LOGIC;
      DRAM_DQ : INOUT STD_LOGIC_VECTOR(15 DOWNTO 0);
      DRAM_UDQM, DRAM_LDQM : BUFFER STD_LOGIC;
		
		--VGA--
		VGA_R:out	std_logic_vector(9	downto	0);	
		VGA_G:out	std_logic_vector(9	downto	0);	
		VGA_B:out	std_logic_vector(9	downto	0);	
		VGA_CLK:	out	std_logic;
		VGA_BLANK:	out	std_logic;	
		VGA_HS:out	std_logic;	
		VGA_VS:out	std_logic;	
		VGA_SYNC:out	std_logic;
		
		--SDCARD--
		SD_CMD, SD_DAT, SD_DAT3 : inout std_logic;
		SD_CLK : out std_logic;
		
		--SRAM--
		SRAM_DQ	:	INOUT	STD_LOGIC_VECTOR(15	downto	0);
		SRAM_ADDR	:	OUT	STD_LOGIC_VECTOR(17	downto	0);
		SRAM_LB_N	:	OUT	STD_LOGIC;
		SRAM_UB_N	:	OUT	STD_LOGIC;
		SRAM_CE_N	:	OUT	STD_LOGIC;
		SRAM_OE_N	:	OUT	STD_LOGIC;
		SRAM_WE_N	:	OUT	STD_LOGIC;
		
		--AUDIO--
		I2C_SDAT : inout std_logic;
		I2C_SCLK : out   std_logic;
		AUD_XCK:  out   std_logic; 
		CLOCK_27: in    std_logic;
		AUD_ADCDAT        : in    std_logic;             -- ADCDAT
		AUD_ADCLRCK       : in    std_logic;             -- ADCLRCK
      AUD_BCLK          : in    std_logic;             -- BCLK
      AUD_DACDAT        : out   std_logic;                                        -- DACDAT
      AUD_DACLRCK       : in    std_logic;    
		
		
		PS2_CLK : INOUT STD_LOGIC;
		PS2_DAT : INOUT STD_LOGIC
			);
   END integration;

ARCHITECTURE Structure OF integration IS
   COMPONENT integrated_module1 PORT (
				clk_clk                  : in    std_logic;             -- clk
            reset_reset_n            : in    std_logic;             -- reset_n
            sdram_wire_addr          : out   std_logic_vector(11 downto 0);                    -- addr
            sdram_wire_ba            : out   std_logic_vector(1 downto 0);                     -- ba
            sdram_wire_cas_n         : out   std_logic;                                        -- cas_n
            sdram_wire_cke           : out   std_logic;                                        -- cke
            sdram_wire_cs_n          : out   std_logic;                                        -- cs_n
            sdram_wire_dq            : inout std_logic_vector(15 downto 0); -- dq
            sdram_wire_dqm           : out   std_logic_vector(1 downto 0);                     -- dqm
            sdram_wire_ras_n         : out   std_logic;                                        -- ras_n
            sdram_wire_we_n          : out   std_logic;                                        -- we_n
            sram_DQ                  : inout std_logic_vector(15 downto 0); -- DQ
            sram_ADDR                : out   std_logic_vector(17 downto 0);                    -- ADDR
            sram_LB_N                : out   std_logic;                                        -- LB_N
            sram_UB_N                : out   std_logic;                                        -- UB_N
            sram_CE_N                : out   std_logic;                                        -- CE_N
            sram_OE_N                : out   std_logic;                                        -- OE_N
            sram_WE_N                : out   std_logic;                                        -- WE_N
            vga_controller_CLK       : out   std_logic;                                        -- CLK
            vga_controller_HS        : out   std_logic;                                        -- HS
            vga_controller_VS        : out   std_logic;                                        -- VS
            vga_controller_BLANK     : out   std_logic;                                        -- BLANK
            vga_controller_SYNC      : out   std_logic;                                        -- SYNC
            vga_controller_R         : out   std_logic_vector(9 downto 0);                     -- R
            vga_controller_G         : out   std_logic_vector(9 downto 0);                     -- G
            vga_controller_B         : out   std_logic_vector(9 downto 0);                     -- B
            sdram_clk_clk            : out   std_logic;                                        -- clk
            switches_export          : in    std_logic_vector(7 downto 0);							  -- export
            leds_export              : out   std_logic_vector(7 downto 0);                     -- export
            pushbuttons_export       : in    std_logic_vector(3 downto 0); 							  -- export
            sd_card_ports_b_SD_cmd   : inout std_logic;                     		              -- b_SD_cmd
            sd_card_ports_b_SD_dat   : inout std_logic;                     		              -- b_SD_dat
            sd_card_ports_b_SD_dat3  : inout std_logic;                     			 	        -- b_SD_dat3
            sd_card_ports_o_SD_clock : out   std_logic;
				
				audio_0_external_ADCDAT        : in    std_logic;             -- ADCDAT
				audio_0_external_ADCLRCK       : in    std_logic;             -- ADCLRCK
				audio_0_external_BCLK          : in    std_logic;             -- BCLK
				audio_0_external_DACDAT        : out   std_logic;                                        -- DACDAT
				audio_0_external_DACLRCK       : in    std_logic;             -- DACLRCK
				audio_and_video_interface_SDAT : inout std_logic;             -- SDAT
				audio_and_video_interface_SCLK : out   std_logic;                                         -- SCLK
				clocks_audio_clk_clk           : out   std_logic;                                        -- clk
				clocks_clk_in_secondary_clk    : in    std_logic;              -- clk
				
				keyboard_CLK						 : inout std_logic;
				keyboard_DAT						 : inout std_logic
        );
   END COMPONENT;

   SIGNAL DQM : STD_LOGIC_VECTOR(1 DOWNTO 0);
   SIGNAL BA : STD_LOGIC_VECTOR(1 DOWNTO 0);
   BEGIN
      DRAM_BA_0 <= BA(0);
      DRAM_BA_1 <= BA(1);
      DRAM_UDQM <= DQM(1);
      DRAM_LDQM <= DQM(0);
		
      NiosII: integrated_module1 PORT MAP (
			clk_clk => CLOCK_50,
			reset_reset_n => '1',
			sdram_clk_clk => DRAM_CLK,
			sdram_wire_addr => DRAM_ADDR,
         sdram_wire_ba => BA,
         sdram_wire_cas_n => DRAM_CAS_N,
         sdram_wire_cke => DRAM_CKE,
         sdram_wire_cs_n => DRAM_CS_N,
         sdram_wire_dq => DRAM_DQ,
         sdram_wire_dqm => DQM,
         sdram_wire_ras_n => DRAM_RAS_N,
         sdram_wire_we_n => DRAM_WE_N, 
			
			vga_controller_CLK	=>	VGA_CLK,	
			vga_controller_HS	=>	VGA_HS,	
			vga_controller_VS	=>	VGA_VS,	
			vga_controller_BLANK	=>	VGA_BLANK,	
			vga_controller_SYNC	=>	VGA_SYNC,	
			vga_controller_R	=>	VGA_R,	
			vga_controller_G	=>	VGA_G,	
			vga_controller_B	=>	VGA_B,
			
			sram_DQ	=>	SRAM_DQ,
			sram_ADDR	=>	SRAM_ADDR,
			sram_LB_N	=>	SRAM_LB_N,
			sram_UB_N	=>	SRAM_UB_N,	
			sram_CE_N	=> sram_CE_N,
			sram_OE_N   => sraM_OE_N,
			sram_WE_N	=> sram_WE_N,
			
			leds_export => LEDG,

         switches_export => SW,
			
			pushbuttons_export => KEY,
			
			sd_card_ports_b_SD_cmd => SD_CMD,
			sd_card_ports_b_SD_dat => SD_DAT,
			sd_card_ports_b_SD_dat3 => SD_DAT3,
			sd_card_ports_o_SD_clock => SD_CLK,
			
			audio_0_external_ADCDAT  =>  AUD_ADCDAT,
			audio_0_external_ADCLRCK => AUD_ADCLRCK,
			audio_0_external_BCLK    => AUD_BCLK,
			audio_0_external_DACDAT  => AUD_DACDAT,
			audio_0_external_DACLRCK => AUD_DACLRCK,
			audio_and_video_interface_SDAT => I2C_SDAT,
			audio_and_video_interface_SCLK => I2C_SCLK,
			clocks_audio_clk_clk    => AUD_XCK,       
			clocks_clk_in_secondary_clk => CLOCK_27,
			
			keyboard_CLK => PS2_CLK,
			keyboard_DAT => PS2_DAT
			);
			
		

   END Structure;
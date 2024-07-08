library verilog;
use verilog.vl_types.all;
entity BLK_MEM_GEN_V7_3_softecc_output_reg_stage is
    generic(
        C_DATA_WIDTH    : integer := 32;
        C_ADDRB_WIDTH   : integer := 10;
        C_HAS_SOFTECC_OUTPUT_REGS_B: integer := 0;
        C_USE_SOFTECC   : integer := 0;
        FLOP_DELAY      : integer := 100
    );
    port(
        CLK             : in     vl_logic;
        DIN             : in     vl_logic_vector;
        DOUT            : out    vl_logic_vector;
        SBITERR_IN      : in     vl_logic;
        DBITERR_IN      : in     vl_logic;
        SBITERR         : out    vl_logic;
        DBITERR         : out    vl_logic;
        RDADDRECC_IN    : in     vl_logic_vector;
        RDADDRECC       : out    vl_logic_vector
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of C_DATA_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of C_ADDRB_WIDTH : constant is 1;
    attribute mti_svvh_generic_type of C_HAS_SOFTECC_OUTPUT_REGS_B : constant is 1;
    attribute mti_svvh_generic_type of C_USE_SOFTECC : constant is 1;
    attribute mti_svvh_generic_type of FLOP_DELAY : constant is 1;
end BLK_MEM_GEN_V7_3_softecc_output_reg_stage;

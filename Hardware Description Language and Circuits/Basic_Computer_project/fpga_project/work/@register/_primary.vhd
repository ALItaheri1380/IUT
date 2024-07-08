library verilog;
use verilog.vl_types.all;
entity \Register\ is
    generic(
        WIDTH           : integer := 12
    );
    port(
        increment       : in     vl_logic;
        enable_write    : in     vl_logic;
        clear           : in     vl_logic;
        clock           : in     vl_logic;
        input_data      : in     vl_logic_vector;
        output_data     : out    vl_logic_vector
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of WIDTH : constant is 1;
end \Register\;

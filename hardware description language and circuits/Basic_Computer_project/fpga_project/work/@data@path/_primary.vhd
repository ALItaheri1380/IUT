library verilog;
use verilog.vl_types.all;
entity DataPath is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        Enable          : in     vl_logic;
        Ac              : out    vl_logic_vector(15 downto 0)
    );
end DataPath;

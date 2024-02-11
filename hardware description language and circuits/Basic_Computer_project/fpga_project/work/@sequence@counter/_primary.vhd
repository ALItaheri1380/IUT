library verilog;
use verilog.vl_types.all;
entity SequenceCounter is
    port(
        clk             : in     vl_logic;
        enable          : in     vl_logic;
        rst             : in     vl_logic;
        \Out\           : out    vl_logic_vector(3 downto 0)
    );
end SequenceCounter;

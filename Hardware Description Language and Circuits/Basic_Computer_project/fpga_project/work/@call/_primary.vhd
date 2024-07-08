library verilog;
use verilog.vl_types.all;
entity Call is
    port(
        Clear           : in     vl_logic;
        clk             : in     vl_logic;
        enable          : in     vl_logic;
        decodersignal   : out    vl_logic_vector(15 downto 0)
    );
end Call;

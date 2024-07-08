library verilog;
use verilog.vl_types.all;
entity Ind_Data is
    port(
        clka            : in     vl_logic;
        wea             : in     vl_logic_vector(0 downto 0);
        addra           : in     vl_logic_vector(11 downto 0);
        dina            : in     vl_logic_vector(15 downto 0);
        clkb            : in     vl_logic;
        addrb           : in     vl_logic_vector(11 downto 0);
        doutb           : out    vl_logic_vector(15 downto 0)
    );
end Ind_Data;

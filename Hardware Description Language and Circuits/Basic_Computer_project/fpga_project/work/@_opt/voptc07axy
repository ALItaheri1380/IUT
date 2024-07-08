library verilog;
use verilog.vl_types.all;
entity Control_Section is
    port(
        CheckIncrPc     : in     vl_logic;
        PrgrmCntr       : in     vl_logic_vector(11 downto 0);
        mData           : in     vl_logic_vector(15 downto 0);
        AluData         : in     vl_logic_vector(15 downto 0);
        InstraDt        : in     vl_logic_vector(15 downto 0);
        decoderDt       : in     vl_logic_vector(15 downto 0);
        curntd          : in     vl_logic_vector(7 downto 0);
        Control_of_Alu  : out    vl_logic_vector(3 downto 0);
        ArIdt           : out    vl_logic_vector(11 downto 0);
        IrIdt           : out    vl_logic_vector(15 downto 0);
        DrIdat          : out    vl_logic_vector(15 downto 0);
        AcIdat          : out    vl_logic_vector(15 downto 0);
        Arw1            : out    vl_logic;
        Drw1            : out    vl_logic;
        Acw2            : out    vl_logic;
        PCINCR          : out    vl_logic;
        Ven             : out    vl_logic;
        Mw1             : out    vl_logic
    );
end Control_Section;

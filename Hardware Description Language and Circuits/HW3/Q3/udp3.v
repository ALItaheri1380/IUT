// udp
primitive t_ff_udp(out , clk , t , set , reset);

output reg out;
input clk , t , set , reset;

    table
        // clk t set resret
        ? ? ? 1 :?:0;
        ? ? ? (10) :?:-;
        ? ? 1 0 :?:1;
        ? ? (10) 0:?:-;
        (01) 0 0 0 :?:-;
        (01) 1 0 0 :0:1;
        (01) 1 0 0 :1:0;
        (0x) ? 0 0 :?:-;
        (?0) ? 0 0 :?:-;  
        ? (??) 0 0 :?:-;

    endtable
    
endprimitive


// top module
module top;

wire out;
reg clk , t , set , reset;

    t_ff_udp u(out , clk , t , set , reset);

    initial begin
        #100 {clk , t , set , reset} = 4'b0001;
        #100 {clk , t , set , reset} = 4'b1010;
        #100 {clk , t , set , reset} = 4'b0001;
        #100 {clk , t , set , reset} = 4'b1100;
        #100 {clk , t , set , reset} = 4'b0000;
        #100;
    end
endmodule
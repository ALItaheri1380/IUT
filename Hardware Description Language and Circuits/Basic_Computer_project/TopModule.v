`timescale 1ns / 1ps

module Top_Module;

    reg clk;
    reg reset;
    reg Enable;
    wire [15:0] Ac;

    initial  
    begin
        #50;
        forever
        begin
            #100 clk = 1'b0;
            #100 clk = 1'b1;
        end
    end

    DataPath dpth (clk , reset , Enable , Ac);

    initial begin
        reset = 1'b1;
        #30;
        reset = 1'b0;
        Enable= 1'b1;
    end

endmodule


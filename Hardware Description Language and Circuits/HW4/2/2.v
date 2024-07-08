module machineTwo(in,Algo,clk,reset,out);
    input in,reset,clk;
    input [5:0] Algo;
    output reg out;

    `define IDLE 2'b00
    `define REC 2'b01
    `define  ACk 2'b10

    reg [1:0] state;
    reg [5:0] Ph;
    integer  tclk;

    function [5:0] Shift_reg;
        input [5:0] temp;
        input in1;
        begin
            Shift_reg = {temp[4:0], in1};
        end
    endfunction

    always @(posedge clk) begin

        if(reset)begin
            state=`IDLE;
            Ph=6'bxxxxxx;
        end

        if(reset==0 && state==`IDLE) state=`REC;

        if(reset ==0 && state==`REC)begin
            Ph = Shift_reg(Ph,in);

            if(Ph==Algo)begin
                state=`ACk;
                tclk=0;
            end            
        end
        if(reset==0 && state==`ACk)begin
            tclk=tclk+1;
            
            if (tclk==2) begin
                state=`IDLE;
                tclk = 0;
            end
        end
        out = (state == `ACk);
    end    
endmodule
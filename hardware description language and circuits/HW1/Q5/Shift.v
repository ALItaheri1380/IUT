module Shift_reg(Clk, Load, Data, Clear, Shift, Dir, OUT);

    input [0:7] Data;
    input Clear, Clk, Shift, Load, Dir;
    output reg [0:7] OUT;

    integer i, j;

    always @(negedge Clk) begin
        if (Clear) begin
            OUT = 8'b0;
        end else if (Load) begin
            OUT = Data;
        end else if (Shift) begin
            case (Dir)
                1'b1: begin
                    OUT[0] = 0;
                    for(i = 1; i < 8; i = i + 1) begin
                        OUT[i] = Data[i - 1];
                    end
                end
                1'b0: begin
                    OUT[7] = 0;
                    for(j = 0; j < 7; j = j + 1) begin
                        OUT[j] = Data[j + 1];
                    end 
                end
                default: OUT = 8'bx;
            endcase
        end
    end
endmodule



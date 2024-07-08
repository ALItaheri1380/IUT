module MachineThree(
 input reset, isCar, clk, 
 input [3:0] y1, y2
);
  reg [5:0] state;
  reg [31:0] cnt;
  
    `define GREENR  6'b100001
    `define YELLOWR 6'b010001
    `define REDG    6'b001100
    `define REDY    6'b001010

  always @(posedge clk or posedge reset) begin

    if (reset) begin
      state = `GREENR;
      cnt = 0;
    end
      case(state)
        `GREENR: begin
          if (isCar) begin
            state = `YELLOWR;
            cnt = 0;
          end
        end

        `YELLOWR: begin
            if(cnt == y1)begin
                state = `REDG;
                cnt = 0;
            end
            else cnt = cnt + 1;
        end

        `REDG: begin
            if(!isCar) begin
                state = `REDY;
                cnt = 0;
            end
        end

        `REDY:begin
            if(cnt == y2) begin
                state = `GREENR;
                cnt = 0;
            end
            else cnt = cnt + 1;
        end
      endcase
  end
endmodule
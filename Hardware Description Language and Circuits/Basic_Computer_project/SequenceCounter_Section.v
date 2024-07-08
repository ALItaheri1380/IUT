module SequenceCounter(input clk,input enable,input rst,output reg [3:0] Out);
  
  reg [3:0] temp_out;
  
  always @(posedge clk or posedge rst) begin
    if (rst) begin
      temp_out = 0;
    end
    else begin
      if (enable) begin
        temp_out = temp_out + 1;
      end
    end
  end
  
  always @(*) begin
    Out = temp_out;
  end
  
endmodule
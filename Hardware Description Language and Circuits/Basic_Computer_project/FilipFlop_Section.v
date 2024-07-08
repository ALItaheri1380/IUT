module FilipFlop(D,clk,Reset,Enable,Q);
  input D,clk,Reset,Enable;
  output reg Q;
  always@(posedge clk or posedge Reset)
    if(Reset) Q = 0;
    else if(Enable) Q = D;
endmodule
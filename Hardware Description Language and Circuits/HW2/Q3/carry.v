module CLA_adder(A, B, Cin, Sum, Cout);
  
  input [3:0] A, B;
  input Cin;
  output [3:0] Sum;
  output Cout;
  
  wire [3:0] P, G;
  wire [4:0] C;
  
  assign P = A ^ B;
  assign G = A & B;
  
  assign C[0] = Cin;
  
  genvar i;
  
  generate
  for(i=0; i<4; i=i+1) begin
      assign Sum[i] = P[i] ^ C[i];
      assign C[i+1] = G[i] | (P[i] & C[i]);
  end
  endgenerate
  
  assign Cout = C[4];
  
endmodule
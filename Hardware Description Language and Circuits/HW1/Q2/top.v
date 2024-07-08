module top;

reg j = 0, k = 0, clk = 1;
wire q, qbar; 

jkff_gate g(clk, j, k, q, qbar);



initial begin

  force q = 1'b0;
  force qbar = 1'b1;

  #100 {k , j , clk} = 3'b011;
  release q;
  release qbar;
  #100 {k , j , clk} = 3'b010;
  #100 {k , j , clk} = 3'b101;
  #100 {k , j , clk} = 3'b100;
  #100 {k , j , clk} = 3'b110;
  #100;
end

endmodule
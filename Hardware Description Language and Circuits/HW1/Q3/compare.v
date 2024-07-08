module comparator(a, b, x, y, z);
  input [3:0] a, b;
  output x, y, z;

  assign z = (a == b);
  assign y = (a < b);
  assign x = (a > b);

endmodule
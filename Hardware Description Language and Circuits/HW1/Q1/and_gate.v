module and_gate(a , b , o);
  
  input a , b;
  output o;
 
  wire x , y;

  not_gate n1(a , x);
  not_gate n2(b , y);
  nor(o , x , y);


endmodule

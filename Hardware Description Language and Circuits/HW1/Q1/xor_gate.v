module xor_gate(a , b , o);
	
	input a , b;
	output o;
	
	wire x , y;

	and_gate g1(a , b , x);
	nor(y , a , b);
	nor(o , x , y);
	
	
	
endmodule

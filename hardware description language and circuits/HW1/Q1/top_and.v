module top_G_and;

reg i1, i2;
wire o;

and_gate m1(i1 , i2 , o);


initial
begin
	#100 {i1, i2} = 0;
	#100 {i1, i2} = 1;
	#100 {i1, i2} = 2;
	#100 {i1, i2} = 3;
	#100;
end

endmodule

module top;

	reg [15:0] a , b;
	wire x , y , z;
	
	compare16 t(a , b , x , y , z);

	initial
	begin
		#100 {a , b} = 32'b11100000000000001000000000000000;
		#100 {a , b} = 32'b10000000000000001000000000000000;
		#100 {a , b} = 32'b00000000000000001110000000000000;
		#100;
	end

	

endmodule




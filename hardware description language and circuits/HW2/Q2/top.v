module top;

	reg [3:0] a;
	wire [47:0] b;
	fct f(a , b);

	initial 
		begin
			#100{a} = 4'b0110;
			#100{a} = 4'b0100;
			#100{a} = 4'b0011;
			#100;
		end

endmodule

module mux(a , b , s , o);

	input [4:0] a , b;
	input [1:0] s;
	output reg[5:0] o;

	always @(a or  b or s)
	begin
		if(s == 0)
			o = a;
		else if(s == 1)
			{o[5] , o[4:0]} = a + b;
		else if(s == 2)
			o = a - b;
		else if(s == 3)
			{o[5] , o[4:0]} = a + 1;

	end
	


endmodule
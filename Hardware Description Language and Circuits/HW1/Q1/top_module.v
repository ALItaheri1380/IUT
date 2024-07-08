module top;


reg in;
wire o;

not_gate a1(in , o);

initial
begin
	#100 {in} = 0;
	#100 {in} = 1;
	#100;
end

endmodule




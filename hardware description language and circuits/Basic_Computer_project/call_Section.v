module Call(Clear , clk , enable , decodersignal);
	input Clear, clk, enable;
	output [15:0] decodersignal;

	wire clr;
	wire [3:0] sc_signal;
	assign clr = Clear | decodersignal[13];
	 
	SequenceCounter sq(clk , enable , clr , sc_signal);	
	decoder dcdr(sc_signal,decodersignal);

endmodule

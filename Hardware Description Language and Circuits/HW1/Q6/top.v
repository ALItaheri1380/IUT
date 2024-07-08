module top;
	
	reg [7:0] dividend , divisor;
	wire[7:0] remainder, submultiple;
	
	loop L(dividend , divisor , remainder , submultiple);
	
	initial
	begin
		#100 {dividend  , divisor} = 1794;//adad ro bara inke 16 bit nanevisam decimal kardam bozorg nashe hei(ghaedata moadelesho migire to binery)
		#100 {dividend  , divisor} = 3843; 
		#100 {dividend  , divisor} = 65303;
		#100 {dividend  , divisor} = 3587;
		#100;
	end

endmodule

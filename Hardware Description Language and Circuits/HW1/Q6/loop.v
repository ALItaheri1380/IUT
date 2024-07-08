module loop(dividend , divisor , remainder , submultiple);
	
	input [7:0] dividend , divisor;
	output reg[7:0] remainder , submultiple;

	integer i;
	reg[7:0] result; 
	
	always @ (dividend or divisor) 
	     begin
		if (1<divisor && divisor<8)
		begin
		    i = 0;
		    result = dividend;

		    while(result >= divisor)
	            begin
	   	        result = result - divisor;
	     	        i = i + 1;
	     	    end
		   remainder = i;
		   submultiple = result;
		end
		else
		   begin
		       $display("out of range");
		       remainder   = 8'bxxxxxxxx;
		       submultiple = 8'bxxxxxxxx;
		   end
			
	      end
	 

endmodule

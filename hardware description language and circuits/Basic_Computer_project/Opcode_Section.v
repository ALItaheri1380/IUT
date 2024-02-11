module Opcode_Section(cdp, out);

    input [2:0] cdp;

    output [7:0] out;

    reg [7:0] temp;     

    always@(*) begin
		if(!cdp)
			temp = 1;
		else if(cdp == 1)
			temp = 2;
		else if(cdp == 2)
			temp = 4;
		else if(cdp == 3)
			temp = 8;
		else if(cdp == 4)
			temp = 16;
		else if(cdp == 5)
			temp = 32;
		else if(cdp == 6)
			temp = 64;
		else if(cdp == 7)
			temp = 128;									
	end  
    assign out = temp;

endmodule
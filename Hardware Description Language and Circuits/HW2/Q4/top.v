module top;
    reg  [7:0] a , b;
    reg  cin;
    wire [7:0] s;
    wire cout;

    full_adder_8bit F(a , b , cin , s , cout);

    initial 
    begin
        #100{a , b , cin} = 17'b0;
	#100{a , b , cin} = 17'b11111111000000001;
	#100;
// max delay is : 96
    end

endmodule

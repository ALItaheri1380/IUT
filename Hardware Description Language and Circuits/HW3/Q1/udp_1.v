primitive udp(out , a , b , c , d);

    output out;
    input a , b , c , d;

    table
        // a , b , c , d : out
       ? ? 0 ? : 1;
       ? ? ? 0 : 1;
       1 0 1 ? : 1;
       0 ? 1 1 : 0;
       1 1 1 1 : 0;
    endtable    

endprimitive

module top;

reg a , b , c , d;
wire out;
	udp u(out , a , b , c , d);
	initial 
	begin
		#100 {a , b , c ,d} = 4'b0000;
		#100 {a , b , c ,d} = 4'b0001;
		#100 {a , b , c ,d} = 4'b0011;
		#100 {a , b , c ,d} = 4'b0110;
		#100 {a , b , c ,d} = 4'b1001;
		#100 {a , b , c ,d} = 4'b1111;
		#100 {a , b , c ,d} = 4'b1101;
		#100 {a , b , c ,d} = 4'b1000;
		#100;
	end

	





endmodule
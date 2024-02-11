module jkff_gate(clk , j , k , Q , Qbar);

	input j,k,clk;
	output Q,Qbar;

	wire x; 
	wire y; 

	nand(x,clk,j,Qbar);
	nand(y, k,clk,Q);
	nand(Q,Qbar,x);
	nand(Qbar,Q,y);

endmodule

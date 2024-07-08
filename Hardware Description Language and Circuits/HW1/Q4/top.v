module top;

reg [4:0] a , b;
reg [1:0] s;
wire[5:0] o;

mux m(a , b , s , o);

initial
begin
	#100 {s , a , b} =658;//adad ro bara inke to 12 bit(2 + 5 + 5) nanevisam decimal kardam bozorg nashe hei(ghaedata moadelesho migire to binery)
	#100 {s , a , b} =1682;
	#100 {s , a , b} =2706;
	#100 {s , a , b} =3730;
	#100;
end

endmodule





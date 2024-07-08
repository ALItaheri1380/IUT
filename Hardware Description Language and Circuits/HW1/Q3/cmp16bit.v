module compare16(a , b , x , y , z);

	input [15:0] a , b;
	output x , y , z;
		
	wire [3:0] s3 , s2 , s1;

	

	
	
	comparator c4(a[15:12] , b[15:12] , s3[3] , s2[3] , s1[3]);
	comparator c3(a[11:8]  , b[11:8]  , s3[2] , s2[2] , s1[2]);
	comparator c2(a[7:4]   , b[7:4]   , s3[1] , s2[1] , s1[1]);
	comparator c1(a[3:0]   , b[3:0]   , s3[0] , s2[0] , s1[0]);
	
	assign z = (s1 == 15);
	assign x = (s3 > s2);
	assign y = (s3 < s2);



endmodule

module full_adder(a , b , cin , s , cout);

    input a , b , cin;
    output s , cout;

    wire o1 , o2 , o3;

    xor #(8 , 4) ga(o1 , a , b);
    xor #(8 , 4) gb(s , o1 , cin);
    and #(5 , 3) gc(o2 , cin , o1);
    and #(5 , 3) gd(o3 , a ,  b);
    or  #(6 , 3) ge(cout , o2 , o3);

endmodule


module full_adder_8bit(A , B , Cin , S , Cout);

    input [7:0] A , B;
    input Cin;
    output [7:0] S;
    output Cout;
    wire c1 , c2 , c3 , c4 , c5;

    full_adder fa(A[0] , B[0] , Cin, S[0] ,   c1);
    full_adder fb(A[1] , B[1] , c1 , S[1] ,   c2);
    full_adder fc(A[2] , B[2] , c2 , S[2] ,   c3);
    full_adder fd(A[3] , B[3] , c3 , S[3] ,   c4);
    full_adder fe(A[4] , B[4] , c4 , S[4] ,   c5);
    full_adder ff(A[5] , B[5] , c5 , S[5] ,   c6);
    full_adder fg(A[6] , B[6] , c6 , S[6] ,   c7);
    full_adder fh(A[7] , B[7] , c7 , S[7] , Cout);

endmodule



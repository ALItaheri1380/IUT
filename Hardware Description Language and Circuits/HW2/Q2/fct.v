module fct(a , b);
    input [3:0] a;
    output reg [47:0] b;

    always @(a)
        b = fact(a);

    function [47:0] fact;
        input [3:0] in;
        integer i;
        begin
            fact = 1;
            for (i = 1; i <= in;i=i+1 )
                fact = fact * i;  
        end
    endfunction
endmodule
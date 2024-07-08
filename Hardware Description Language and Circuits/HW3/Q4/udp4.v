module counter(Q , clk , t , reset , set);

`define NBit 5

    output [`NBit -1 : 0] Q;
    input clk , t , reset , set;
    wire [`NBit -1: 0] T; 
    
    generate        
        genvar i;
        
        t_ff_udp t1(Q[0] , clk , 1 , set , reset);
        assign T[0] = 1;

        t_ff_udp t2(Q[1] , clk , Q[0] , set , reset);
        assign T[1] = Q[0];

        for (i = 2 ; i <`NBit ; i = i + 1) begin
	    
            and(T[i] , Q[i - 1] , T[i - 1]);

            t_ff_udp T_FF(Q[i] , clk , T[i] , set , reset);
        end
    endgenerate

endmodule

module top_counter;
`define NBit 5

    wire [`NBit - 1 : 0] Q;
    reg clk , t , reset , set;

    counter cnt1(Q , clk , t , reset , set);

    initial begin
        #100 {t , reset , set , clk} = 4'b0100;
        #100{reset , clk} = 2'b01;
        #100{t , clk} = 2'b10;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1; 
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1; 
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1; 
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1; 
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1; 
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1; 
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100{clk} = 0;
        #100{clk} = 1;
        #100;
    end
endmodule
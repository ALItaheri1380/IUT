module top_Priority;
    wire [1:0] out;
    reg a , b , c , d , enable;

    Priority_4bit0 p1(out[0] , a , b , c , d , enable);
    Priority_4bit1 p2(out[1] , a , b , c , d , enable);

    initial 
        begin
            #100 {a , b , c , d , enable} = 0;
            #100 {a , b , c , d , enable} = 1;
            #100 {a , b , c , d , enable} = 2;
            #100 {a , b , c , d , enable} = 3;
            #100 {a , b , c , d , enable} = 4;
            #100 {a , b , c , d , enable} = 5;
            #100 {a , b , c , d , enable} = 6;
            #100 {a , b , c , d , enable} = 7;
            #100 {a , b , c , d , enable} = 8;
            #100 {a , b , c , d , enable} = 9;
            #100 {a , b , c , d , enable} = 10;
            #100 {a , b , c , d , enable} = 11;
            #100 {a , b , c , d , enable} = 12;
            #100 {a , b , c , d , enable} = 13;
            #100 {a , b , c , d , enable} = 14;
            #100 {a , b , c , d , enable} = 15;
            #100 {a , b , c , d , enable} = 16;
            #100 {a , b , c , d , enable} = 17;
            #100 {a , b , c , d , enable} = 18;
            #100 {a , b , c , d , enable} = 19;
            #100 {a , b , c , d , enable} = 20;
            #100 {a , b , c , d , enable} = 21;
            #100 {a , b , c , d , enable} = 22;
            #100 {a , b , c , d , enable} = 23;
            #100 {a , b , c , d , enable} = 24;
            #100 {a , b , c , d , enable} = 25;
            #100 {a , b , c , d , enable} = 26;
            #100 {a , b , c , d , enable} = 27;
            #100 {a , b , c , d , enable} = 28;
            #100 {a , b , c , d , enable} = 29;
            #100 {a , b , c , d , enable} = 30;
            #100 {a , b , c , d , enable} = 31;
            #100;
        end
endmodule
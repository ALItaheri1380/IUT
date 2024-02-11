module log(a , b , out);

    input [15:0] a;
    input [2:0] b;
    output reg[4:0] out;

    always @(a or b) 
        logtask(a , b);
    task logtask;
        input [15:0] A;
        input [2:0] B;
        integer i;
        integer cnt;
            begin
                i = B;
                cnt = 0;
                while (A>i) 
                begin
                        i = i * B;
                        cnt = cnt + 1;
                end
                log.out = cnt;
            end

    endtask


endmodule
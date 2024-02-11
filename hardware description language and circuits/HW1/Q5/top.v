module top;

    reg [7:0] Data;
    reg Load , Clear , Clk , Shift , Dir;

    wire[7:0] OUT;

    Shift_reg Sh(Clk , Load , Data , Clear , Shift , Dir , OUT);

    initial begin
        #100 {Data , Load , Clear , Clk , Shift , Dir} = 13'b1000001110000;
        #100 {Clk} = 1'b1;
        #100 {Data , Load , Clear , Clk , Shift , Dir} = 13'b1000001101000;
        #100 {Clk} = 1'b1;
        #100 {Data , Load , Clear , Clk , Shift , Dir} = 13'b1000001100010;
        #100 {Clk} = 1'b1;
        #100 {Data , Load , Clear , Clk , Shift , Dir} = 13'b1000001100011;
        #50;

    end


endmodule
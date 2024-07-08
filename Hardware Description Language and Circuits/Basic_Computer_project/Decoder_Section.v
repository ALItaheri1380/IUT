module decoder(Ptr,Out);

	input  [3:0] Ptr;
    output [15:0] Out;
    
	reg [15:0] temp;

	assign Out = temp;

	always@(*) begin
        if(Ptr == 0)begin
            temp = 1;
        end else if(Ptr == 1)begin
            temp = 2;
        end else if(Ptr == 2)begin
            temp = 4;
        end else if(Ptr == 3)begin
            temp = 8;
        end else if(Ptr == 4)begin
            temp = 16;
        end else if(Ptr == 5)begin
            temp = 32;
        end else if(Ptr == 6)begin
            temp = 64;
        end else if(Ptr == 7)begin
            temp = 128;
        end else if(Ptr == 8)begin
            temp = 256;
        end else if(Ptr == 9)begin
            temp = 512;
        end else if(Ptr == 10)begin
            temp = 1024;
        end else if(Ptr == 11)begin
            temp = 2048;
        end else if(Ptr == 12)begin
            temp = 4096;
        end else if(Ptr == 13)begin
            temp = 8192;
        end else if(Ptr == 14)begin
            temp = 16384;
        end else if(Ptr == 15)begin
            temp = 32768;
        end      
    end 
endmodule

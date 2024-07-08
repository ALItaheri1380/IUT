module machineOne(data , clk , reset , out1 , out2);
    input data , clk , reset;
    output reg out1 , out2;

    reg [1:0] state , next_state;
    reg [10:0] cnt = 11'd0;

    `define BIT0 2'b00
    `define BIT1 2'b01
    `define BIT2 2'b10
    `define Rather 2'b11

    always @(posedge clk) state = next_state;

    always @(state or data or reset) begin
        if(reset)begin
            next_state = `BIT0;
            cnt  = 0;
        end

        else begin
            case (state)
                `BIT0:begin
                    if(data)begin
                        next_state = `BIT1;
                        cnt = 1;
                    end
                    else begin
                        next_state = `BIT0;
                        cnt = 0;
                    end
                end

                `BIT1:begin
                    if(data) begin
                        next_state = `BIT2;
                        cnt = 2;
                    end
                    else begin
                        next_state = `BIT0;
                        cnt = 0;
                    end
                end

                `BIT2:begin
                    if(data) begin
                        next_state = `Rather;
                        cnt = cnt + 1;
                    end
                    else begin
                        next_state = `BIT0;
                        cnt = 0;
                    end
                end
                `Rather:begin
                    if(data)begin
                        cnt = cnt + 1;
                        next_state = `Rather;
                    end
                    else begin
                        cnt = 0;
                        next_state = `BIT0;
                    end
                end
            endcase
        end
    end 

    always @(state)begin
        out1 = (state == `BIT2);
        out2 = (cnt < 4);
    end
endmodule

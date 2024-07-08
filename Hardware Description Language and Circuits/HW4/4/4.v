module WashingMachine(timer, tmpOk, finish, closeDoor, StartButton, beep, quiet, load, unload, reset);


    input timer , finish , quiet , reset , closeDoor , StartButton , tmpOk;
    output reg beep , load , unload;

    reg [3:0] state;

    reg [2:0] timeLndrycmprtmnt = 0;
    reg [2:0] heat_time = 0;
    reg [3:0] Eng_time = 0;
    reg [3:0]  rl = 0;

    `define SHEDDING_CLOTHES 4'b0000
    `define POURING_TIDE 4'b0001
    `define SET_TIMER  4'b0010
    `define S_BUTTON   4'b0011
    `define WATR_TIDE  4'b0100 
    `define WATR_PART  4'b0101
    `define S_HEATER   4'b0110
    `define S_ENGINE   4'b0111
    `define OUT_WATER  4'b1000
    `define INPCLRWATR 4'b1001
    `define ROTATION   4'b1010
    `define EMPTY      4'b1011

    `define TimeLaundryCompartment 2
    `define HeatTime 2
    `define ENGINE_TIME 3
    `define Roll 3

    always @(posedge timer or reset) begin

        if(reset) begin
            state = `SHEDDING_CLOTHES;
            timeLndrycmprtmnt = 0;
            heat_time = 0;
        end

        case (state)
            `SHEDDING_CLOTHES:begin
                if(closeDoor) begin
                    timeLndrycmprtmnt = 0;
                    state = `POURING_TIDE;
                end
            end

            `POURING_TIDE:begin
		        if(closeDoor)
                    state = `SET_TIMER;
            end
             
            `SET_TIMER:begin
                if(closeDoor && StartButton)begin
                    state = `S_BUTTON;
                    timeLndrycmprtmnt = 0;
                end
            end

            `S_BUTTON:begin
                if(closeDoor && StartButton) 
                    state = `WATR_TIDE;
            end

            `WATR_TIDE:begin
                if(closeDoor && StartButton)begin
                    state = `WATR_PART;
                    timeLndrycmprtmnt = 0;
                end
            end

            `WATR_PART:begin
                if(timeLndrycmprtmnt == `TimeLaundryCompartment 
                   && closeDoor && StartButton)begin
                    state = `S_HEATER;
                    timeLndrycmprtmnt = 0;
                end
                else begin
                    timeLndrycmprtmnt = timeLndrycmprtmnt + 1;
                end
            end

            `S_HEATER:begin
                if(tmpOk) begin
                    if(heat_time == `HeatTime 
                    && closeDoor && StartButton)begin
                        state = `S_ENGINE;
                        heat_time = 0;
                    end

                    else
                        heat_time = heat_time + 1;
                end
            end

            `S_ENGINE:begin
                if(Eng_time == `ENGINE_TIME
                && closeDoor && StartButton)begin
                    state = `OUT_WATER;
                    Eng_time = 0;
                end
                else
                    Eng_time = Eng_time + 1;
            end

            `OUT_WATER:begin
                if(closeDoor && StartButton)begin
                    state = `INPCLRWATR;
                end
            end

            `INPCLRWATR:begin
                if(closeDoor && StartButton)begin
                    state = `ROTATION;
                end
            end

            `ROTATION:begin
                if(rl == `Roll && closeDoor
                   && StartButton && finish)
                begin
                    rl = 0;
                    state = `EMPTY;
                end
                else
                    rl = rl + 1;
            end

            `EMPTY: state = `SHEDDING_CLOTHES;
        endcase

   // output:

        load   =(state == `SHEDDING_CLOTHES);
        unload =(state == `EMPTY);
        beep   = ((state == `EMPTY) && quiet == 0);
    end
endmodule 
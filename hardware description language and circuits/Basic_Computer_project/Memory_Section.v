`timescale 1ns / 1ps
module memory(clock,memoryWrite,Adrss,InpData,OutData);
	 input clock,memoryWrite;
    input  [11:0] Adrss;
	 input  [15:0] InpData;
    output [15:0] OutData;
	 
Ind_Data mm(
  .clka(clock), // input clka
  .wea(memoryWrite), // input [0 : 0] wea
  .addra(Adrss), // input [11 : 0] addra
  .dina(InpData), // input [15 : 0] dina
  .clkb(clock), // input clkb
  .addrb(Adrss), // input [11 : 0] addrb
  .doutb(OutData) // output [15 : 0] doutb
);

endmodule

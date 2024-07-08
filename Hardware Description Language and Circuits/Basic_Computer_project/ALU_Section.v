module ALU(Ac , Dr , St_Alu , EI , EO , Incr , data);
  input EI;
  input [15:0] Ac;
  input [15:0] Dr;
  input [3:0] St_Alu;
  output EO; 
  output Incr;
  output [15:0] data;
   
  reg [15:0] Data;

  always@(*)begin		
	if(!St_Alu) begin
		Data = (Ac & Dr);
	end else if(St_Alu == 1) begin
		Data = (Ac + Dr);
	end else if(St_Alu == 2) begin
		Data = Dr;
	end else if(St_Alu == 3) begin
		Data = ~Ac;
	end else if(St_Alu == 4) begin
		Data = {{EI},{Ac[15:1]}};
	end else if(St_Alu == 5) begin
		Data = {{Ac[14:0]},{EI}};
	end else if(St_Alu == 6) begin
		Data = 0;
	end else if(St_Alu == 7) begin
		Data = Ac + 1;
	end else begin
		Data = 16'bzzzzzzzzzzzzzzzz;
	end
  end
   
  assign EO = (St_Alu == 4) ? Ac[0] : (St_Alu == 5) ? Ac[15] : (St_Alu == 8) ? 0 :(St_Alu == 9) ? ~EI :Data[15];
  assign Incr = (St_Alu == 10) ? ~Ac[15] : (St_Alu == 11) ? Ac[15] : ( St_Alu == 12 && Ac == 0) ? 1 : (St_Alu == 13) ? ~EI : 0;
  assign data = Data;
endmodule


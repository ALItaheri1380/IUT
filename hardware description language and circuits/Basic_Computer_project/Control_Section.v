module Control_Section(CheckIncrPc , PrgrmCntr , mData , AluData , InstraDt , decoderDt , curntd , Control_of_Alu , ArIdt , IrIdt , DrIdat , AcIdat , Arw1 , Drw1 , Acw2 , PCINCR , Ven , Mw1);
		input [11:0] PrgrmCntr;
		input [15:0] mData, AluData, InstraDt;	
		input CheckIncrPc;			 
		input [15:0] decoderDt;			
		input [7:0] curntd;											
		output [3:0] Control_of_Alu;								
		output [11:0] ArIdt;								
		output [15:0] IrIdt, DrIdat, AcIdat;			
		output Arw1, Drw1, Acw2, PCINCR, Ven, Mw1; 
		wire Mrf = (~curntd[7]) & decoderDt[8];
		wire rRf1 = (~InstraDt[15]) & curntd[7] & decoderDt[6];
		wire RAc1 = rRf1 & (InstraDt[6] | InstraDt[5] | InstraDt[11] | InstraDt[9] | InstraDt[7]);
		wire mAlu1 = (~curntd[7]) & decoderDt[10];
		wire mSt1 = Mrf & curntd[3];
		wire MrfInd = (~curntd[7]) & InstraDt[15]  & decoderDt[6]; 	
        assign Control_of_Alu = (mAlu1 && curntd[0]) ? 0 : (mAlu1 && curntd[1]) ?  1 : (mAlu1 && curntd[2]) ? 2 : (rRf1 && InstraDt[11])  ?  6 :
		(rRf1 && InstraDt[9])   ?   3 :	(rRf1 && InstraDt[7])   ?   4  : (rRf1 && InstraDt[6])   ?   5 : (rRf1 && InstraDt[5])   ?   7 :
	    (rRf1 && InstraDt[10])  ?   8 :    (rRf1 && InstraDt[8])   ?   9  : (rRf1 && InstraDt[4])   ?   10 :
		(rRf1 && InstraDt[3])   ?   11:    (rRf1 && InstraDt[2])   ?   12 : (rRf1 && InstraDt[1])   ?   13 : 15;
        assign Ven = (mAlu1 && curntd[1]) | (rRf1 && (InstraDt[7] | InstraDt[6] | InstraDt[8] | InstraDt[10]));
		assign Mw1 = mSt1;
		assign Arw1 = decoderDt[0] | decoderDt[4] | MrfInd;
		assign ArIdt = decoderDt[0] ? PrgrmCntr : decoderDt[4] ? InstraDt[7:0] : MrfInd ? mData[7:0] : 0;
		assign IrIdt = decoderDt[2] ? mData : 0;	
		assign Drw1 = Mrf && (~curntd[3]);
        assign PCINCR = (CheckIncrPc | decoderDt[2]);
		assign DrIdat = Drw1 ? mData : 0;
		assign Acw2 = (mAlu1 | RAc1) & (~mSt1);
		assign AcIdat = Acw2 ? AluData : 0;
endmodule
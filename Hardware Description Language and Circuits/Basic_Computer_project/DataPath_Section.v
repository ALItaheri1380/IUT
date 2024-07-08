module DataPath(clk, reset , Enable , Ac);
  input clk , reset , Enable;
  output [15:0] Ac;
  
  wire Ade, IncrAr;  
  wire [11:0] cAd_data, coAr_data; 
  wire Pce, IncrPc;  
  wire [11:0] cPc_data, coPc_data;
  wire IncrIR;  
  wire [15:0] cIr_data, coIr_data;
  wire Ace, IncrAc;  
  wire [15:0] cAc_data, coAc_data;
  wire Dre, IncrDr;  
  wire [15:0] cDr_data, coDr_data;
  
  wire [15:0] mmryData;
  wire mmrye;
  
  wire [15:0] dcdrcg;
  wire [7:0] dcdrop;
  
  wire [15:0] Data;
  wire [3:0] AluControl;
  wire Ei, Eo, pcinc;
  
  wire eflp;
    
  memory mmry (clk , mmrye , coAr_data , coAc_data , mmryData);
  Call sig (reset, clk , Enable , dcdrcg);
    
  Register ar (IncrAr , Ade , reset , clk , cAd_data , coAr_data);
  Register pc (IncrPc , Pce , reset , clk , cPc_data , coPc_data);
  Register #(16) ir (IncrIR , dcdrcg[2] , reset , clk , cIr_data , coIr_data);
  Register #(16) dr (IncrDr , Dre , reset , clk , cDr_data , coDr_data);
  Register #(16) ac (IncrAc , Ace , reset , clk , cAc_data , coAc_data);
   
  ALU unit (coAc_data, coDr_data,AluControl,Ei,Eo,pcinc,Data);
  FilipFlop E (Eo , clk , reset , eflp , Ei);
  Opcode_Section  opcd(coIr_data[14:12] , dcdrop);
  
  Control_Section ctrl(pcinc , coPc_data , mmryData , Data , coIr_data , dcdrcg , dcdrop , AluControl , cAd_data , cIr_data , cDr_data , cAc_data , Ade , Dre , Ace , IncrPc , eflp , mmrye);
  assign Ac = coAc_data;
       
endmodule
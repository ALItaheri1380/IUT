
# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

create_project -name fpga_project -dir "D:/final_Fpga_project/fpga_project/planAhead_run_1" -part xc5vlx110tff1136-2
set_param project.pinAheadLayout yes
set srcset [get_property srcset [current_run -impl]]
set_property target_constrs_file "DataPath.ucf" [current_fileset -constrset]
add_files [list {ipcore_dir/Ind_Data.ngc}]
set hdlfile [add_files [list {../SequenceCounter_Section.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {ipcore_dir/Ind_Data.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {../Decoder_Section.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {../Register_Section.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {../Opcode_Section.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {../Memory_Section.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {../FilipFlop_Section.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {../Control_Section.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {../call_Section.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {../ALU_Section.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {../DataPath_Section.v}]]
set_property file_type Verilog $hdlfile
set_property library work $hdlfile
set_property top DataPath $srcset
add_files [list {DataPath.ucf}] -fileset [get_property constrset [current_run]]
add_files [list {ipcore_dir/Ind_Data.ncf}] -fileset [get_property constrset [current_run]]
open_rtl_design -part xc5vlx110tff1136-2

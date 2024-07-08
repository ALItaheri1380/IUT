module Register #(parameter WIDTH = 12)(increment, enable_write,clear, clock, input_data, output_data); 
	// Inputs
	input wire increment, enable_write, clear, clock;
	input wire [WIDTH-1:0] input_data;
	// Outputs
	output wire [WIDTH-1:0] output_data;

    reg [WIDTH-1:0] register_data; // Internal register to store data
    
    always @(posedge clock or posedge clear)
        if (clear) // Clear the register when the clear signal is asserted
	begin
            register_data = 0;
	end
        else if (increment) // Increment the register value when the increment signal is asserted
	begin
            register_data = register_data + 1;
	end
        else if (enable_write) // Update the register value with the input_data when the enable_write signal is asserted
	begin
            register_data = input_data;
			
	end
            
    assign output_data = register_data; // Assign the register value as the output

endmodule
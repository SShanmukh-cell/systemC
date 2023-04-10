`include "left_shift_1.sv"

module multiplier(
  input [15:0] multiplicand,
  input [15:0] multiplier,
  output reg [31:0] product,
  input clk
);
  
  reg [31:0] temp1;
  reg [31:0] temp2;
  reg [31:0] temp_product;
  reg [31:0] store0[0:15];
  reg [31:0] store1[0:15];
  reg [15:0] c[0:15];
  genvar i;
  

    assign temp1 = multiplicand;
    assign temp2 = multiplier;
  
    for(i = 0; i < 16; i = i + 1) begin
      assign c[i] = temp2[i] ? i : 1'b0;     
      left_shift_N left_shift_0(temp1, c[i], store0[i], clk);
      assign store1[i] = temp2[i] ? store0[i] : 1'b0;
    end
    
   
  always @(posedge clk or multiplicand or multiplier) begin
    temp_product = 0;
    for(int j = 0; j < 16; j = j + 1) begin
      temp_product = temp_product + store1[j];
    end
    product = temp_product;
  end 
  
endmodule

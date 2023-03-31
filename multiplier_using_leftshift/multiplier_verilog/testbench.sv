`include "design.sv"

module tb_multiplier;
  reg clk;
  reg [15:0] multiplicand;
  reg [15:0] multiplier;
  wire [31:0] product;
  reg [31:0] product_tb;
  
  multiplier dut(multiplicand, multiplier, product, clk);
  
  initial begin
    clk=1'b0;
    forever #5 clk=~clk;
  end
  initial begin
    repeat(10) begin
      {multiplicand, multiplier}=$random; 
      product_tb = multiplicand*multiplier;
      #10;
      //$display("%0t : inp=%0b, multiplier=%0d, out=%0b", $time, inp, shift_by, out);
      $display("%0t : multiplicand=%0d, multiplier=%0d, product_dut=%0d, multiplicand*multiplier=%0d", $time, multiplicand, multiplier, product, product_tb);
    end
    #200;
    $finish;
  end
  initial begin
    $dumpfile("test.vcd");
    $dumpvars(1);
  end
endmodule

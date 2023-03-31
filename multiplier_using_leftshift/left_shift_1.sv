module left_shift_N(
  input [15:0] inp,
  input [3:0] shift_by,
  output reg [31:0] out,
  input clk
);
  
  
  reg [31:0] temp1, temp2;

  always@(posedge clk or inp or shift_by) begin
    
    if(shift_by == 0) out = inp;
    else begin
      temp1 = inp;      
        for(int j  = 15; j>=0 ;j--) begin
          temp1[j+shift_by] = temp1[j]; 
          if(j==0) begin
            for(int i = shift_by-1 ; i>=0; i--) begin
              temp1[i] = 0;
            end
            
          end
        end
      out = temp1;
    end
  end
  
endmodule

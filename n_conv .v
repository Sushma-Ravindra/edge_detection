`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/23/2023 10:28:06 PM
// Design Name: 
// Module Name: conv
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module conv( input clka,input rst);
reg [7:0]res;

wire [23:0] A;
wire [23:0] B;
wire [23:0] C;

reg signed [12:0] t_res;
reg [15:0]addra;




wire[7:0] a11;
wire[7:0] a12;
wire[7:0] a13;
wire[7:0] a21;
wire[7:0] a22;
wire[7:0] a23;
wire[7:0] a31;
wire[7:0] a32;
wire[7:0] a33;


wire [7:0]k11;
wire [7:0]k12;
wire [7:0]k13;
wire [7:0]k21;
wire [7:0]k22;
wire [7:0]k23;
wire [7:0]k31;
wire [7:0]k32;
wire [7:0]k33;

assign a11 = A[23:16];
assign a12 = A[15:8];
assign a13 = A[7:0];

assign a21 = B[23:16];
assign a22 = B[15:8];
assign a23 = B[7:0];

assign a31 = C[23:16];
assign a32 = C[15:8];
assign a33 = C[7:0];

assign k11 = 1; assign k12 = 2; assign k13 = 1;
assign k21 = 0; assign k22 = 0; assign k23 = 0;
assign k31 = 1; assign k32 = 2; assign k33 = 1;

// bram instatiation of inputs 
// row 1 
blk_mem_gen_0  first_row(
  .clka(clka),    // input wire clka
  .addra(addra),  // input wire [15 : 0] addra
  .douta(A)  // output wire [23 : 0] douta
);

// row 2 
blk_mem_gen_1 second_row (
  .clka(clka),    // input wire clka
  .addra(addra),  // input wire [15 : 0] addra
  .douta(B)  // output wire [23 : 0] douta
);

// row 3 
blk_mem_gen_2 third_row (
  .clka(clka),    // input wire clka
  .addra(addra),  // input wire [15 : 0] addra
  .douta(C)  // output wire [23 : 0] douta
);

ila_0 my_probe (
	.clk(clka), // input wire clk


	.probe0(addra), // input wire [15:0]  probe0  
	.probe1(res), // input wire [7:0]  probe1
	.probe2(rst) // input wire [0:0]  probe2
);



always @(posedge clka)
begin
   if(rst) begin addra = 0; end
   else begin 
     (*DONT_TOUCH="YES"*)   t_res = (a31*k31 + a32*k32 + a33*k33)-(a11*k11 + a12*k12 + a13*k13);
        
        if(t_res<0) begin
            res = 12'd0;
        end
        
        else if(t_res>13'd255) begin
            res = 8'd255;            
        end
        
        else begin
            res = t_res;
        end
        if (addra < 16'd64517) addra = addra+1;
        else addra = addra;
    end
    
    
end


endmodule

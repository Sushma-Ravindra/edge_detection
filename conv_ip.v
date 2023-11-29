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


module conv( input clk,
    input [31:0]A,
    input [31:0]B,
    input [31:0]C,
    output reg [31:0]res
);

reg signed [12:0] t_res;




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


always @(posedge clk)
begin
   
        t_res = (a31*k31 + a32*k32 + a33*k33)-(a11*k11 + a12*k12 + a13*k13);
        
        if(t_res<0) begin
            res = 32'd0;
        end
        
        else if(t_res>13'd255) begin
            res = 32'd255;            
        end
        
        else begin
            res = t_res;
        end
    
    
end


endmodule

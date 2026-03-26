module mux(a, b, s, out, clock);
   input [31:0]  a;
   input [31:0]  b;
   input         s;
   input         clock;
   output [31:0] out;

   reg [31:0]    out;
   integer       i;

   always @ (posedge clock) begin
      out <= 0;
      for (i = 0; i < 32; i = i + 1) begin
         out[i] <= (a[i] & !s) | (b[i] & s);
      end
   end
endmodule // mux

module mux_tb;
   reg [31:0]  d1;
   reg [31:0]  d2;
   reg         s;
   wire [31:0] out_data;
   reg         clock;
   initial begin
      $monitor("a=")
   end
   
endmodule // mux_tb

   

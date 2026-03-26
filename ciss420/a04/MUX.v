module mux(a,b,s,out,clock);
   input [31:0]  a;
   input [31:0]  b;
   input         s;
   input         clock;
   output [31:0] out;

   reg [31:0]    out;
   integer       i;

   always @ (posedge clock) begin
      out = 0;
      for (i = 0; i < 32; i = i + 1) begin
         out[i] = (a[i] & !s) | (b[i] & s);
      end
   end
endmodule

module mux_tb;
   reg [31:0]  d1;
   reg [31:0]  d2;
   reg         s;
   wire [31:0] out_data;
   reg         clock;

   initial begin
      $monitor("a=%d, b=%d, s=%b, out=%d, clock=%b", d1, d2, s, out_data, clock);
      d1 = 0;
      d2 = 0;
      clock = 0;
      s = 0;

      #5 d1 = 107;
      #5 d2 = 230;
      #5 s = 1;
      #10 s = 0;
      #5 s = 1;
      #10 $finish;
   end // initial begin

   always begin
      #5 clock = !clock;
   end

   mux test_mux(
                .a(d1),
                .b(d2),
                .s (s),
                .out(out_data),
                .clock(clock)
                );
endmodule // mux_tb

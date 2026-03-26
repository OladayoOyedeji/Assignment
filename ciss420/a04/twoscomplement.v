module twoscomplement(b, out, clock);
   input [31:0]  b;
   input         clock;
   output [31:0] out;

   reg [31:0]    out;

   integer       i;
   reg           carry;
   always @ (posedge clock) begin
      carry = 1;
      for (i = 0; i < 32; i = i + 1) begin
         out[i] = !b[i] ^ carry;
         
         carry = carry & !b[i];
      end
   end
   
endmodule // twoscomplement

module twos_tb;
   reg [31:0] b;

   wire [31:0] out;
   wire signed [31:0] out_signed;
   
   reg                clock;

   assign out_signed = out;
   
   initial begin
      $monitor("b(bin): =%b, b(int): =%d\nout(bin): =%b, out(int): =%d\nclock=%b", b, b, out, out_signed, clock);
      
      clock = 0;

      @(posedge clock);
      b = 0;

      @(posedge clock);
      b = 5;

      @(posedge clock);
      b = 10;

      @(posedge clock);
      b = 32'd100;

      @(posedge clock);
      b = 32'd1;

      @(posedge clock);
      b = 32'd50;

      @(posedge clock);
      $finish;
   end

   always begin
      #5  clock = !clock;
      
   end
      
   twoscomplement test_twos(
                            .b(b),
                            .out(out),
                            .clock(clock)
                            );
endmodule // twos_tb

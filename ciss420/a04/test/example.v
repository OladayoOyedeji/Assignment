module NOT(a, b, clock);
   input a, clock;
   output b;
   reg    b;
   always @ (psedge clock) begin
      b <= !a;
   end
endmodule // NOT

module NOT_tb;
   reg a_;
   wire out;

   reg  clock;

   initial begin
      $monitor ("a=%b, b=%b, clock=%b", a_, out, clock);
      a_ = 0;
      clock = 0;
      #5 a_ = 1;
      #10 a_ = 0;
      #15 a_ = 1;
      #10 $finish;
   end

   always begin
      #5 clock = !clock;
      
   end

   NOT theNOT(
              .a (a_),
              .b (out),
              .clock (clock)
              );
endmodule; // NOT_tb

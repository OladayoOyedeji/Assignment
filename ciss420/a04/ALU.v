`include "twoscomplement.v"
`include "MUX.v"
`include "adder.v"

module smallALU(a, b, op, result, clock);
   input [31:0]  a;
   input [31:0]  b;
   input         op;
   input         clock;

   output [31:0] result;
   wire [31:0]   twos_b;
   wire [31:0]   sum;
   wire [31:0]   rhs;

   twoscomplement twos(.b(b), .out(twos_b), .clock(clock));
   mux choice(.a(b), .b(twos_b), .s(op), .out(rhs), .clock(clock));
   adder add1(.a(a), .b(rhs), .sum(result), .clock(clock));
endmodule // smallALU

module smallALU_tb;

   reg [31:0] a;
   reg [31:0] b;
   reg        op;
   wire [31:0] sum;
   reg         clock;


   // clock generator


   // monitor outputs
   initial begin
      $monitor("time=%0t | a=%b b=%b op=%b sum=%b clock=%b",
               $time, a, b, op, sum, clock);
      clock = 0;

      @(posedge clock);
      a = 10; b = 5; op = 1;   // addition

      @(posedge clock);
      a = 10; b = 5; op = 0;   // subtraction

      @(posedge clock);
      a = 5; b = 10; op = 1;   // negative result

      @(posedge clock);
      a = 100; b = 50; op = 0; // addition

      @(posedge clock);
      a = 100; b = 50; op = 1; // subtraction

      @(posedge clock);

      $finish;
   end
   
   always begin
      #5 clock = ~clock;
   end
   
   smallALU testALU(
                    .a(a),
                    .b(b),
                    .op(op),
                    .result(sum),
                    .clock(clock)
                    );
   
endmodule

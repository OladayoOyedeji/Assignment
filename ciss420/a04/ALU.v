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

module adder(a, b, sum, clock);
   input [31:0] a;
   input [31:0] b;

   input        clock;

   output [31:0] sum;

   reg [31:0]    sum;

   integer       i;
   reg           carry;

   always @ (posedge clock) begin
      carry = 0;
      
      for (i = 0; i < 32; i = i + 1) begin
         sum[i] = (a[i] ^ b[i]) ^ carry;
         carry = (a[i] & b[i]) | ((a[i] ^ b[i]) & carry);
         // $monitor("carry=%b",
         //          carry);
      end
   end
endmodule // adder

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
endmodule // mux

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
      $monitor("time=%0t | a=%d b=%d op=%d sum=%d clock=%b",
               $time, a, b, op, sum, clock);
      clock = 0;

      #5 a = 50;
      #5 b = 100; 
      #5 op = 0;   // addition
      
      // #5 a = 10;
      // #5 b = 5; op = 0;   // subtraction

      // @(posedge clock);
      // a = 5; b = 10; op = 1;   // negative result

      // @(posedge clock);
      // a = 100; b = 50; op = 0; // addition

      // @(posedge clock);
      // a = 100; b = 50; op = 1; // subtraction
      

      #12 $finish;
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

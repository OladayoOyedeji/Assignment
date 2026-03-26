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
endmodule

module adder_tb;
   reg [31:0] a;
   reg [31:0] b;
   wire [31:0] sum;
   reg         clock;

   initial begin
      $monitor("a=%d b=%d sum=%d clock=%b",
               a, b, sum, clock);
      clock = 0;

      @(posedge clock);
      a = 10; b = 5;   // addition

      @(posedge clock);
      a = 10; b = 5;  // subtraction

      @(posedge clock);
      a = 5; b = 10;  // negative result

      @(posedge clock);
      a = 100; b = 50; // addition

      @(posedge clock);
      a = 100; b = 50; // subtraction

      @(posedge clock);

      #10 $finish;
   end
   
   always begin
      #5 clock = ~clock;
   end
   
   adder testadder(
                    .a(a),
                    .b(b),
                    .sum(sum),
                    .clock(clock)
                    );
   
endmodule

module Decoder(code, decoded, clock);
   input [5:0]   code;
   input         clock;
   output [63:0] decoded;
   reg [63:0]    decoded;
   integer       i;

   always @ (posedge clock) begin
      for (i = 0; i < 64; i = i + 1) begin
         decoded[i] <= (
                        (((i % 2) && code[0]) || (!(i % 2) && !code[0]))
                        && ((((i/2) % 2) && code[1]) || (!((i/2) % 2) && !code[1]))
                        && ((((i/4) % 2) && code[2]) || (!((i/4) % 2) && !code[2]))
                        && ((((i/8) % 2) && code[3]) || (!((i/8) % 2) && !code[3]))
                        && ((((i/16) % 2) && code[4]) || (!((i/16) % 2) && !code[4]))
                        && ((((i/32) % 2) && code[5]) || (!((i/32) % 2) && !code[5]))
                        );
      end
   end // always @ (posedge clock)
endmodule

module SRAM(address, dout, din, writeEnable, 
            readEnable, clock);
   input [31:0]      address;
   input [31:0]      din;          // Added from your port list
   input             writeEnable;  // Added from your port list
   input             readEnable;   // Added from your port list
   input             clock;
   output reg [31:0] dout;      // Must be 'reg' because it's assigned in an always block

   // 64 x 32-bit array
   reg [31:0]        memory [0:63];

   // 1. Load the memory from a file at start-up
   initial begin
      $readmemb("test.mem", memory);
   end

   // 2. Synchronous Read/Write Logic
   always @(posedge clock) begin
      if (writeEnable) begin
         memory[address[5:0]] <= din; // Use lower 6 bits for 64 entries
      end
      
      if (readEnable) begin
         dout <= memory[address[5:0]];
      end
   end
endmodule // SRAM

module mem(PC, out, clock);
   input  [31:0] PC;
   input         clock; // Changed from int to input
   output [31:0] out;
   
   wire [5:0]    word_index = PC[7:2];
   // Instantiate the SRAM module
   // We map PC to address and out to dout
   SRAM instruction_storage (
      .address({26'b0, word_index}),
      .dout(out),
      .din(32'b0),          // Instruction memory is usually read-only
      .writeEnable(1'b0),   // Disable writing
      .readEnable(1'b1),    // Always enable reading
      .clock(clock)
   );

endmodule; // mem

module testMem;
   // 1. Signals
   reg [31:0] PC;
   reg        clock;
   wire [31:0] out;

   // 2. Instantiate the wrapper
   mem uut (
      .PC(PC),
      .clock(clock),
      .out(out)
   );

   // 3. Clock Generation (10 unit period)
   always #5 clock = ~clock;

   // 4. Stimulus
   initial begin
      // Initialize
      clock = 0;
      PC = 0;

      // Monitor changes
      $monitor("Time=%0t | PC=%d | Instruction(out)=%b", $time, PC, out);

      // Wait for initial load
      #10;

      // Cycle through addresses
      // Assuming PC increments by 1 for your 64-word SRAM
      repeat (5) begin
         #10 PC = PC + 4;
      end

      #20 $finish;
   end
endmodule // testMem

   

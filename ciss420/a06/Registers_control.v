module Decoder(code, decoded, clock);
   input [4:0]   code;
   input         clock;
   output [31:0] decoded;
   reg [31:0]    decoded;
   integer       i;

   always @ (posedge clock) begin
      for (i = 0; i < 32; i = i + 1) begin
         decoded[i] <= (
                        (((i % 2) && code[0]) || (!(i % 2) && !code[0]))
                     && ((((i/2) % 2) && code[1]) || (!((i/2) % 2) && !code[1]))
                     && ((((i/4) % 2) && code[2]) || (!((i/4) % 2) && !code[2]))
                     && ((((i/8) % 2) && code[3]) || (!((i/8) % 2) && !code[3]))
                     && ((((i/16) % 2) && code[4]) || (!((i/16) % 2) && !code[4]))
                        );
      end
   end // always @ (posedge clock)
endmodule

module Registerfile(read1, read2, write_register, 
                    write_data, read_data_1,
                    read_data_2, reg_write, clock);
   input [4:0]   read1, read2, write_register;

   input [31:0]  write_data;
   input         reg_write, clock;
   output [31:0] read_data_1, read_data_2;
   reg [31:0]    RF [31:0];
   integer       i;
   
   initial begin
      for (i = 0; i < 32; i = i + 1) begin
         RF[i] = 32'b0;
      end
   end
   assign read_data_1 = RF[read1];
   assign read_data_2 = RF[read2];

   always begin
        @(posedge clock) if (reg_write) RF[write_register] <= write_data;
   end
endmodule // Registerfile

module Datapath(instruction, RegDst, RegWrite, writeData, data1, data2, clock);
   input [31:0]  instruction;
   input [31:0]  writeData;

   input         RegDst;
   input         RegWrite;
   input         clock;
   output [31:0] data1;
   output [31:0] data2;
   
   
   wire [4:0]    readRegister1;
   wire [4:0]    readRegister2;
   wire [4:0]    readRegister3;
   wire [4:0]    writeRegister;

   assign readRegister1 = instruction[25:21]; // rs
   assign readRegister2 = instruction[20:16]; // rt
   assign readRegister3 = instruction[15:11]; // rd
   
   wire [4:0] writeReg = RegDst ? readRegister2: readRegister3;
   
   // Mux mux(
   //         .a(readRegister2), 
   //         .b(instruction[15:11]), 
   //         .s(RegDist),
   //         .out(writeRegister),
   //         .clock(clock)
   //         );

   Registerfile registers(
                    .read1(readRegister1),
                    .read2(readRegister2),
                    .write_register(writeRegister),
                    .write_data(writeData),
                    .read_data_1(data1),
                    .read_data_2(data2),
                    .reg_write(RegWrite),
                    .clock(clock)
                    );
   

endmodule // control

module testDatapath;
   // 1. Signals to drive the inputs (reg)
   reg [31:0]   instruction;
   reg          clock;
   reg          RegDst;
   reg          RegWrite;
   reg [31:0]   writeData;

   // 2. Wires to observe the outputs (wire)
   wire [31:0]  data1;
   wire [31:0]  data2;
   

   // 3. Clock Generation: Toggles every 5 time units
   always #5 clock = ~clock;

   // 4. Instantiate the Unit Under Test (UUT)
   
   // 5. Stimulus Block
   initial begin
      // Setup initial state
      clock = 0;
      instruction = 32'b0;
      writeData = 32'd0;
      RegDst = 0;
      RegWrite = 1;
      
      // Monitor key signals in the console
      $monitor("Time=%0t | clock=%b | Instr=%h | RegDst=%b | RegWrite=%b | WriteData=%d | Data1=%d | Data2=%d", 
                $time, clock, instruction, RegDst, RegWrite, writeData, data1, data2);
      // $monitor("Time=%0t | Instr=%b | data1=%d | data2=%d | WriteData=%d | clock=%b", 
      //           $time, instruction, data1, data2, writeData, clock);
      

      // Example Stimulus: Wait for a clock cycle, then change instruction
      // --- TEST CASE 1: R-Type Setup ---
      #10;
      instruction = 32'b000000_00000_00001_00000_00000_000000; // Example: add $t1, $s1, $s2
      //               opcode |  rs | rt  |  rd |shamt|funct
      writeData = 32'd500;
      RegDst = 1;                 // Manual: Route 'rd' to write register
      RegWrite = 1;               // Manual: Enable writing to register file
      
      #10;
      instruction = 32'b000000_00000_00001_00000_00000_000000; // Example: add $t1, $s1, $s2
      writeData = 32'd500;
      RegDst = 1;                 // Manual: Route 'rd' to write register
      RegWrite = 1;               // Manual: Enable writing to register file
      
      // --- TEST CASE 2: Turn off writing ---
      #10;
      RegWrite = 0;               // Stop writing to prevent accidental data corruption
      writeData = 32'd500;
      #50 $finish; // End simulation after 100 units
   end // initial begin
   
   Datapath uut (
      .instruction(instruction),
      .RegDst(RegDst),
      .RegWrite(RegWrite),
      .writeData(writeData),
      .data1(data1),
      .data2(data2),
      .clock(clock)
   );

endmodule // testDatapath

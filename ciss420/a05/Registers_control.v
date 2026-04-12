module Decoder(code, decoded, clock);
   input [4:0] code;
   input       clock;
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
   input [5:0] read1, read2, write_register;

   input [31:0] write_data;
   input        reg_write, clock;
   output [31:0] read_data_1, read_data_2;
   reg [31:0]    RF [31:0];

   assign read_data_1 = RF[read1];
   assign read_data_2 = RF[read2];

   always begin
        @(posedge clock) if (reg_write) RF[write_reg] <= write_data;
   end
endmodule // Registerfile

module Datapath(instruction, RegDst, RegWrite, writeData, clock);
   input [31:0] instruction;
   input [4:0]  writeData;

   input        RegDst;
   input        clock;
   
   
   wire [4:0]   readRegister1;
   wire [4:0]   readRegsister2;
   wire [4:0]   writeRegister;
   wire [31:0]  data1;
   wire [31:0]  data2;
   
   assign readRegister1 = instruction[25:21]; // rs
   assign readRegister2 = instruction[20:16]; // rt
   
   Mux mux(
           .a(readRegister2), 
           .b(instruction[15:11]), 
           .s(RegDist),
           .out(writeRegister),
           .clock(clock)
           );

   Reg Registerfile(
                    .read1(readRegister1),
                    .read2(readRegister2),
                    .write_register(writeRegister),
                    .read_data1(data1),
                    .read_data2(data2),
                    .reg_write(RegWrite),
                    .clock(clock)
                    );
   

endmodule // control


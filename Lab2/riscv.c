#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();

/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}



/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */

/* parse and execute a 32-bit RISC-V instruction, takes in char* instr (user input), returns true
 * if instruction is properly executed, false if it could not be parsed || parameters are bad.
 * Function will loop, asking for instr, parsing it, executing it, until instr == 'EOF' (CTRL + D),
 * and will print register values.
 * Registers = 32-bit int arrays
 * Memory = .txt file with memory address & 32-bit word (data)
 * Immediates = translate to normal C ints
*/
bool compare_strings(char* input, char* instr_name){
	//compare the first token of the input with an execution instruction
	char* in = input;
	char* name = instr_name;
	while(*in!= '\0'  || *name != '\0'){
		if (*in != *name){
			return false;
		}
		in++;
		name++;
	}
	return true;
}

bool interpret(char* instr){
	char** riscv_instr = tokenize(instr);						//tokenizing input
	print_all_tokens(riscv_instr);

	if(compare_strings(riscv_instr[0], "ADD")==true){			//interpreting ADD instruction
		//add syntax: ADD RD RS1 RS2

		//remove the X to get the register index
		char* index;
		int indices[3];
		for(int i = 1; i < 4; i++) {							//storing the reg indices of rd, rs1, and rs2
			index = riscv_instr[i];
			index++;
			indices[i-1] = atoi(index);
			
		}

		reg[indices[0]] = reg[indices[1]] + reg[indices[2]];	//rd = rs1 + rs2
		//free(riscv_instr);
		return true;
	}
	else if(compare_strings(riscv_instr[0], "ADDI")==1){		//interpreting ADDI instruction
		//addi syntax: ADDI RD RS1 IMM

		//remove the X to get the reg index
		char* index;
		int indices[3];
		for(int i = 1; i < 3; i++){
			index = riscv_instr[i];
			index++;
			indices[i-1] = atoi(index);
		}
		indices[2] = atoi(riscv_instr[3]);						//adding the immediate 
		reg[indices[0]] = reg[indices[1]] + indices[2];			//rd = rs1 + imm
		//free(riscv_instr);
		return true;
	}
	else if(compare_strings(riscv_instr[0], "LW")==1){			//interpreting LW instruction
		//lw syntax: LW RD IMM RS1 (LEFT TO RIGHT)
		int rd;
		int imm;
		int rs1;
		
		riscv_instr[1]++;
		riscv_instr[3]++;
		rd = atoi(riscv_instr[1]);
		imm = atoi(riscv_instr[2]);
		rs1 = atoi(riscv_instr[3]);	
		printf("rd: %d, imm: %d, rs1: %d\n", rd, imm, rs1);
		//rd = memory[rs1 + imm]
		//reg[rd]] = read_address(reg[rs1] + imm, "mem.txt");
		return true;
	}
	else if(compare_strings(riscv_instr[0], "SW")==1){
		//sw syntax: SW RD IMM RS1 (RIGHT TO LEFT)
		free(riscv_instr);
		riscv_instr = tokenize(instr);
		//riscv_instr = tokenize(riscv_instr);
		char* index;
		int indices[3];
		index = riscv_instr[1];					
		index++;
		indices[0] = atoi(index);								//rd index
		index = riscv_instr[2];			
		indices[1] = atoi(index);								//imm index
		index = riscv_instr[3];
		index++;
		indices[2] = atoi(index);								//rs1 index

		//memory[rs1 + imm] = rd
		write_address(reg[indices[0]],indices[1] + indices[2], "mem.txt");
		return true;
	}
	printf("Instruction is not valid. Type the instruction using uppercase letters and using a space as a delimeter.");
	//free(riscv_instr);
	return false;
}


/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", address);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}

void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
	}
}


/**
 * Your code goes in the main
 *
 */
int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	print_regs();

	// Below is a sample program to a write-read. Overwrite this with your own code.
	write_read_demo();

	printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");

	char* instruction = malloc(1000 * sizeof(char));
	bool is_null = false;
	// fgets() returns null if EOF is reached.
	is_null = fgets(instruction, 1000, stdin) == NULL;
	while(!is_null){
	/*	interpret(instruction);
		printf("\n");
		print_regs();
		printf("\n");

		is_null = fgets(instruction, 1000, stdin) == NULL;
	*/
		write_read_demo();
		char** tokens = tokenize(instruction);
		print_all_tokens(tokens);
		is_null = fgets(instruction, 1000, stdin) == NULL;

	}

	printf("Good bye!\n");

	return 0;
}

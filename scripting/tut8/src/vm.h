#ifndef _VM_H_
#define _VM_H_

// VM.H: Header file for VM.CPP
#include "stack.h"    // Stack template class
#include "mystring.h" // String class
#include "synttree.h"
#include "intcode.h"
/*
// The opcodes
enum Opcode  {
   OP_NOP,           // no operation
   OP_PUSH,          // push string [var]
   OP_GETTOP,        // get string from top of stack (=assign) [var]
   OP_DISCARD,       // discard top value from the stack
   OP_PRINT,         // print a string
   OP_INPUT,         // input a string [var]
   OP_JMP,           // unconditional jump [dest]
   OP_JMPF,          // jump if false [dest]
   OP_STR_EQUAL,     // test whether two strings are equal
   OP_BOOL_EQUAL,    // test whether two bools are equal
   OP_CONCAT,        // concatenate two strings
   OP_BOOL2STR,      // convert bool to string
   JUMPTARGET        // not an opcode but a jump target;
                     // the target field points to the jump instruction
};
*/

// Instruction class
class Instr {
public:
   Instr ()   {opcode = OP_NOP; operand = 0;}
   Instr (Opcode _opcode)   {opcode = _opcode; operand = 0;}
   Instr (Opcode _opcode, int _operand)  {opcode = _opcode; operand = _operand;}

   Opcode    opcode;    // the opcode
   int       operand;   // string number or target instruction
};

// Some defines and constants
typedef Stack<int> VM_Stack; // <  0 : boolean
                             // >= 0 : index to string table
const int ST_TRUE  = -1,  // stack codes for true/false
          ST_FALSE = -2;

const int MAX_STR = 100;  // max. num. of strings in memory (including temps)

// The virtual machine class
class VMachine  {
public:
   VMachine ();
   ~VMachine ();
   void Read ();
   void Execute ();
   void Reset ();
private:
   // functions to make temp.copies of strings
   int NewTempCopy ();
   int NewTempCopy (int j);
   int NewTempCopy (char *s);
   void DelTempCopy (int i);

   Instr   *instr;  // the instructions
   int      ninstr; // num. of instr.
   String  *str[MAX_STR];  // the string table (NULL=entry not used)
   VM_Stack stack;  // the stack
};

#endif

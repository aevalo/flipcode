// VM.CPP: The virtual machine
#include <iostream>
#include <cstring>
#include "vm.h"       // VMachine class definition

// VMachine constructor
VMachine::VMachine ()   {
   instr = NULL; ninstr = 0;
   int i;
   for (i=0; i<MAX_STR; i++)
      str[i]=NULL;
}

VMachine::~VMachine () {
   Reset();
}

// Reset the virtual machine
void VMachine::Reset ()   {
   int i;
   for (i=0; i<MAX_STR; i++)    {
      if (str[i] != NULL)   {delete str[i]; str[i] = NULL;}
   }
   if (instr != NULL)  {delete[] instr; instr = NULL; ninstr = 0;}
   stack.Empty();
}

// Read a program from stdin
// (hardwired for testing purposes)
void VMachine::Read ()   {
   str[0] = new String("Answer to the Ultimate Question"
      " of Life, the Universe and Everything > ");
   str[1] = new String;
   str[2] = new String("42");
   str[3] = new String("Right!\n");
   str[4] = new String("Wrong!\n");

   // A very simple program for testing purposes
   ninstr = 11;
   instr = new Instr[ninstr];
   instr[0] = Instr (OP_PUSH,  0);   // print "...";
   instr[1] = Instr (OP_PRINT);
   instr[2] = Instr (OP_INPUT, 1);   // input answer;
   instr[3] = Instr (OP_PUSH,  1);   // if (answer == "42")
   instr[4] = Instr (OP_PUSH,  2);
   instr[5] = Instr (OP_STR_EQUAL);
   instr[6] = Instr (OP_JMPF,  3);
   instr[7] = Instr (OP_PUSH,  3);   //      print "Right!\n";
   instr[8] = Instr (OP_JMP,   2);
   instr[9] = Instr (OP_PUSH,  4);   // else print "Wrong!\n";
   instr[10]= Instr (OP_PRINT);
}

// Execute the program in memory
void VMachine::Execute ()   {
   int ip; // instruction pointer
   VM_Stack stack;  // the stack
   int ipc; // instruction pointer change
   int i,j,k;

   ip = 0; // start at instruction 0
   while (ip < ninstr)   {
      ipc = 1; // default: add one to ip
      switch (instr[ip].opcode)   {
      case OP_NOP:
         // No OPeration
         break;
      case OP_PUSH:
         // Push a variable onto the stack
         stack.Push (NewTempCopy(instr[ip].operand));
         break;
      case OP_GETTOP:
         str[instr[ip].operand]->Assign (*str[stack.GetTop()]);
         break;
      case OP_DISCARD:
         DelTempCopy (stack.Pop());
         break;
      case OP_PRINT:
         i = stack.Pop();
         str[i]->Print();
         DelTempCopy (i);
         break;
      case OP_INPUT:
         str[instr[ip].operand]->Input ();
         break;
      case OP_JMP:
         ipc = instr[ip].operand;
         break;
      case OP_JMPF:
         i = stack.Pop();
         if (i == ST_FALSE)   ipc = instr[ip].operand;
         break;
      case OP_STR_EQUAL:
         i = stack.Pop(); j = stack.Pop();
         if (strcmp (str[i]->Val(), str[j]->Val()) == 0)   k = ST_TRUE; else k = ST_FALSE;
         DelTempCopy (i); DelTempCopy (j);
         stack.Push (k);
         break;
      case OP_BOOL_EQUAL:
         i = stack.Pop(); j = stack.Pop();
         if (i == j)   k = ST_TRUE; else k = ST_FALSE;
         stack.Push (k);
         break;
      case OP_CONCAT:
         i = stack.Pop(); j = stack.Pop();
         k = NewTempCopy (j); str[k]->Concatenate (*str[i]);
         DelTempCopy (i); DelTempCopy (j);
         stack.Push (k);
         break;
      case OP_BOOL2STR:
         i = stack.Pop();
         if (i == ST_FALSE)   i = NewTempCopy ("false"); else i = NewTempCopy("true");
         stack.Push (i);
         break;
      }
      ip += ipc;
   }
}

// Returns the index to a new temp. string
int VMachine::NewTempCopy ()  {
   int i;

   for (i=0; i < MAX_STR; i++)   {
      if (str[i] == NULL)  {
         str[i] = new String;
         break;
      }
   }
   if (i == MAX_STR)
      return -1;
   else return i;
}

// Returns the index to a new copy of string j
int VMachine::NewTempCopy (int j)  {
   int i = NewTempCopy();
   if (i>=0)  str[i]->Assign (*str[j]);
   return i;
}

// Returns the index to a new copy of string s
int VMachine::NewTempCopy (char *s)  {
   int i = NewTempCopy ();
   if (i>=0)  str[i]->Assign (s);
   return i;
}

// Deletes the previously generated temp. string
void VMachine::DelTempCopy (int i)  {
   if (str[i] != NULL)   {delete str[i]; str[i] = NULL;}
}


$include Operators.h

//-----------------------------------------------------------------------------
// Push the return address on the stack
// Jump to procedure
// On return, pop nargs-1 arguments off of stack
$def procedureCall nargs procedure
@RETURN
D=A
@returnAddress
M=D
$pushD
@procedure
0;JMP
(RETURN)

// for (i=0; i<nargs; i++) {
//     pop();
// }
@nargs       // A = nargs
D=A          // D = nargs
@R12         // A = 12  M = 0
M=D-1        // R12@12 = nargs - 1
D=M          // D = nargs - 1

// jump to end if no args need to be popped
@END
D;JEQ

(LOOP)
$popAD
@R12         // R12@12 = iter
M=M-1        // R12@12 = iter - 1
D=M          // D = iter - 1

// jump to LOOP if D > 0
@LOOP
D;JGT

(END)

// add nargs-1 to D
@nargs       // A = nargs
D=A-1        // D = nargs-1

// fix stack pointer
@SP
M=D+M
$end

//-----------------------------------------------------------------------------
// Return from procedure, pop return address off of stack and jump to it.
// Has the effect of returning control flow to the calling procedure
$def return
$popAD    // A = SP+1 D = ret_address
A=D       // A = ret_address
0;JMP
$end

//-----------------------------------------------------------------------------
// Push LCL, ARG, THIS, and THAT onto the stack
// adjust ARG pointer to point to argument variable segment
// adjust LCL pointer to point to local variable segment
$def pushFrame nargs nlocals
// push LCL, ARG, THIS, THAT to stack
@LCL
D=M
$pushD
@ARG
D=M
$pushD
@THIS
D=M
$pushD
@THAT
D=M
$pushD

// set LCL to SP
@SP
D=M
@LCL
M=D

// move SP down to make space for lcl vars // LCL - nlocals
@nlocals
D=A
@SP
M=M-D

// adjust ARG to point to first arg on stack // LCL + 5 + nargs
@5
D=A
@LCL
D=D+M
@ARG
M=D
@nargs
D=A
@ARG
M=D+M
$end

//-----------------------------------------------------------------------------
// Restore LCL, ARG, THIS and THAT pointers to Caller values
// reset SP to the same value as when pushFrame was executed
$def popFrame nargs nlocals
// set SP to LCL
@LCL
D=M
@SP
M=D

// pop THAT, THIS, ARG, and LCL
$popAD
$popAD
$popAD
$popAD

$return
$end

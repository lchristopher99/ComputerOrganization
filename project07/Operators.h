$include Stack.h

// use R12 for local vars so R1 (LCL), R2 (ARG), R3 (THIS), and R4 (THAT) are not overwritten

//-----------------------------------------------------------------------------
// pop two items off of the stack, add them and push the result on the stack
// eR12. 2 items in stack of values 1 and 2

$def add
// store first val in R1
$popAD   // A = 254 D = 2
@R12      // A = R12  M = 0
M=D      // R12@R12 = 2

// pop second val and add to first
$popAD   // A = 255 D = 1
@R12       // A = 12  M = 2
D=D+M    // D = 1 + 2

// clear local var
M=0      // R12@12 = 0

// push D to stack
$pushD
$end

//-----------------------------------------------------------------------------
// pop two items off of the stack and subtract them, push result onto stack
// eR12. 2 items in stack of values 1 and 2

$def sub
// store first val in R1
$popAD   // A = 254 D = 2
@R12       // A = 12  M = 0
M=D      // R12@12 = 2

// pop second val and subtract first
$popAD   // A = 255 D = 1
@R12       // A = 12  M = 2
D=D-M    // D = 1 - 2

// clear local var
M=0      // R12@12 = 0

// push D to stack
$pushD
$end

//-----------------------------------------------------------------------------
// Pop the top of the stack and push its bitwise complement on the stack
// eR12. 1 item in stack of value 1

$def not
// pop item off stack
$popAD   // A = 255 D = 1
D=!D     // D = -2

// push D to stack
$pushD
$end

//-----------------------------------------------------------------------------
// Pop the top of the stack and push its negation on the stack
// eR12. 1 item in stack of value 1

$def neg
// pop item off stack
$popAD   // A = 255 D = 1
D=-D     // D = -1

// push D to stack
$pushD
$end

// comparison operators
//-----------------------------------------------------------------------------
// pop two elements of off the stack and push -1 if they are equal, 0 otherwise
// eR12. 2 items in stack of values 1 and 1

$def eq
// store first val in R1
$popAD   // A = 254 D = 1
@R12       // A = 12  M = 0
M=D      // R12@12 = 1

// pop second val and subtract to find equality
$popAD   // A = 255 D = 1
@R12       // A = 12  M = 1
D=D-M    // D = 1 - 1

// clear local var
@R12       // A = 12  M = 1
M=0

// jump to EQ if D = 0
@EQ
D;JEQ

// push 0 if not equal
D=0
$pushD

// jump to end
@END
0;JMP

// push -1 if equal
(EQ)
D=-1
$pushD

(END)
$end

//-----------------------------------------------------------------------------
// Pop a, pop b if b<a push -1 else push 0
// eR12. 2 items in stack of values 1 and 2 // 1 < 2 = -1

$def lt
// store a val in R1
$popAD   // A = 254 D = 2
@R12       // A = 12  M = 0
M=D      // R12@12 = 2

// pop b val
$popAD   // A = 255 D = 1
@R12       // A = 12  M = 2

// subtract to find equality
// D = bVal - aVal
D=D-M    // D = 1 - 2

// clear local var
@R12       // A = 1   M = 2
M=0

// jump to LT if D < 0
@LT
D;JLT

// push 0 if greater than
D=0
$pushD

// jump to end
@END
0;JMP

// push -1 if less than
(LT)
D=-1
$pushD

(END)
$end

//-----------------------------------------------------------------------------
// Pop a, pop b if b>a push -1 else push 0
// eR12. 2 items in stack of values 2 and 1 // 2 > 1 = -1

$def gt
// store a val in R1
$popAD   // A = 254 D = 1
@R12       // A = 12  M = 0
M=D      // R12@12 = 1

// pop b val
$popAD   // A = 255 D = 2
@R12       // A = 12  M = 1

// subtract to find equality
// D = bVal - aVal
D=D-M    // D = 2 - 1

// clear local var
@R12       // A = 12  M = 1
M=0

// jump to GT if D > 0
@GT
D;JGT

// push 0 if less than
D=0
$pushD

// jump to end
@END
0;JMP

// push -1 if greater than
(GT)
D=-1
$pushD

(END)
$end

//-----------------------------------------------------------------------------
// pop two values of the stack and push their bitwise and
// eR12. 2 items in stack of values 1 and 2

$def and
// store first val in R1
$popAD   // A = 254 D = 2
@R12       // A = 12  M = 0
M=D      // R12@12 = 2

// pop second val and with first
$popAD   // A = 255 D = 1
@R12       // A = 12  M = 2
D=D&M    // D = 1 & 2

// clear local var
M=0      // R12@5 = 0

// push D to stack
$pushD
$end

//-----------------------------------------------------------------------------
// pop a, pop b, push a|b
// eR12. 2 items in stack of values 1 and 2

$def or
// store first val in R1
$popAD   // A = 254 D = 2
@R12       // A = 12  M = 0
M=D      // R12@12 = 2

// pop second val and with first
$popAD   // A = 255 D = 1
@R12       // A = 12  M = 2
D=D|M    // D = 1 | 2

// clear local var
M=0      // R12@12 = 0

// push D to stack
$pushD
$end

//-----------------------------------------------------------------------------
// Go into infinite loop to halt the program
$def halt
@HALT
(HALT)
0;JMP
$end

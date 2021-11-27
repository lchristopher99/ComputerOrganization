// Note for this the stack will be starting at the top of memory and building
// down.  These are the basic stack operations that will be implemented

//-----------------------------------------------------------------------------
// Push D register onto the stack, D remains unchanged by this operation
// ex. D = 1

$def pushD
// decrement stack pointer
@SP    // A = 0  M = 255
M=M-1  // SP@0 = 254

// push item to stack
A=M+1  // A = 254 + 1
M=D    // 255 = 1
$end

//-----------------------------------------------------------------------------
// Push A register onto the stack, D is value pushed on the stack after this
// operation
$def pushA
D=A
$pushD
$end

//-----------------------------------------------------------------------------
// Pop the top of stack into the A and D registers
// ex. 1 item is in the stack of value 1

$def popAD
// get address above stack pointer
@SP     // A = 0  M = 254
D=M+1   // D = 254 + 1

// increment stack pointer
M=D     // SP@0 = 255

// store value inD
A=D     // A = 255
D=M     // D = 1

// remove item from stack
M=0     // 255 = 0
A=D     // A = 1
$end

//-----------------------------------------------------------------------------
// Use push value, push ptr, setPTR pops these off of stack and
// sets *ptr=value
$def setPTR
$popAD   // A = 254 D = (ptr)
@R12      // A = 12   M = 0
M=D      // R12@12 = (ptr)

$popAD   // A = 255 D = value
@R12      // A = 12   M = (ptr)
A=M      // A = (ptr)
M=D      // *(ptr) = value

@R12      // A = 12 M = (ptr)
M=0
$end

//-----------------------------------------------------------------------------
// get pointer pops pointer off of the stack then push *ptr onto the
// stack
$def getPTR
$popAD  // A = 255 D = (ptr)
A=D     // A = (ptr)
D=M     // D = *(ptr)
$pushD
$end

//-----------------------------------------------------------------------------
// get the local variable id defined by *(LCL-id) into registers A and D
// ex. getLocal 0

$def getLocal id
@LCL    // A = 1  M = base_pointer
D=M     // D = base_pointer

@id     // A = id
D=D-A   // D = (LCL-id)

A=D     // A = (LCL-id)
D=M     // D = *(LCL-id)
A=M     // A = *(LCL-id)
$end

//-----------------------------------------------------------------------------
// store register D in the local variable id defined by *(LCL-id)
// @5
// D=A
// setLocal 1

$def setLocal id
// store D
@R12
M=D

// get base_pointer
@LCL    // A = 1  M = base_pointer
D=M     // D = base_pointer

// find memory location of lcl var
@id     // A = id
D=D-A   // D = (LCL-id)

// store address
@R13     // A = 13 M = 0
M=D     // R13@13 = (LCL-id)

// reset D
@R12     // A = 12 M = 5
D=M     // D = 5
// clear R12
M=0

// insert new val at address
@R13     // A = 13 M = (LCL-id)
A=M     // A = (LCL-id)
M=D     // *(LCL-id) = D

// clear R13
@R13
M=0
$end

//-----------------------------------------------------------------------------
// get argument id (defined by *(ARG-id)) and store in registers A and D
$def getArgument id
@ARG    // A = 2  M = base_pointer
D=M     // D = base_pointer

@id     // A = id
D=D-A   // D = (ARG-id)

A=D     // A = (ARG-id)
D=M     // D = *(ARG-id)
A=M     // A = *(ARG-id)
$end

//-----------------------------------------------------------------------------
// set the argument id (defined by *(ARG-id)) to the value stored in register D
$def setArgument id
// store D
@R12
M=D

// get base_pointer
@ARG    // A = 1  M = base_pointer
D=M     // D = base_pointer

// find memory location of lcl var
@id     // A = id
D=D-A   // D = (ARG-id)

// store address
@R13     // A = 13 M = 0
M=D     // R13@13 = (ARG-id)

// reset D
@R12     // A = 12 M = 5
D=M     // D = 5
// clear R12
M=0

// insert new val at address
@R13     // A = 13 M = (ARG-id)
A=M     // A = (ARG-id)
M=D     // *(ARG-id) = D

// clear R13
@R13
M=0
$end

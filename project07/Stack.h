// Note for this the stack will be starting at the top of memory and building
// down.  These are the basic stack operations that will be implemented

//-----------------------------------------------------------------------------
// Push D register onto the stack, D remains unchanged by ths operation
$def pushD
$end

//-----------------------------------------------------------------------------
// Push A register onto the stack, D is value pushed on the stack after this
// operation
$def pushA
$end

//-----------------------------------------------------------------------------
// Pop the top of stack into the A and D registers
$def popAD
$end

//-----------------------------------------------------------------------------
// Use push value, push ptr, setPTR pops these off of stack and
// sets *ptr=value
$def setPTR
$end

//-----------------------------------------------------------------------------
// get pointer pops pointer off of the stack then push *ptr onto the
// stack
$def getPTR
$end

//-----------------------------------------------------------------------------
// get the local variable id defined by *(LCL-id) into registers A and D
$def getLocal id
$end

//-----------------------------------------------------------------------------
// store register D in the local variable id defined by *(LCL-id)
$def setLocal id
$end

//-----------------------------------------------------------------------------
// get argument id (defined by *(ARG-id)) and store in registers A and D
$def getArgument id
$end

//-----------------------------------------------------------------------------
// set the argument id (defined by *(ARG-id)) to the value stored in register D
$def setArgument id
$end


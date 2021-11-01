$include Operators.h

//-----------------------------------------------------------------------------
// Push the return address on the stack
// Jump to procedure
// On return, pop nargs-1 arguments off of stack
$def procedureCall nargs procedure
$end

//-----------------------------------------------------------------------------
// Return from procedure, pop return address off of stack and jump to it.
// Has the effect of returning control flow to the calling procedure
$def return
$end

//-----------------------------------------------------------------------------
// Push LCL, ARG, THIS, and THAT onto the stack
// adjust ARG pointer to point to argument variable segment
// adjust LCL pointer to point to local variable segment
$def pushFrame nargs nlocals
$end

//-----------------------------------------------------------------------------
// Restore LCL, ARG, THIS and THAT pointers to Caller values
// reset SP to the same value as when pushFrame was executed
$def popFrame nargs nlocals
$end

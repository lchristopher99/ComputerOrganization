$include Stack.h

//-----------------------------------------------------------------------------
// pop two items off of the stack, add them and push the result on the stack
$def add
$end

//-----------------------------------------------------------------------------
// pop two items off of the stack and subtract them, push result onto stack
$def sub
$end

//-----------------------------------------------------------------------------
// Pop the top of the stack and push its bitwise complement on the stack
$def not
$end

//-----------------------------------------------------------------------------
// Pop the top of the stack and push its negation on the stack
$def neg
$end

// comparison operators
//-----------------------------------------------------------------------------
// pop two elements of off the stack and push -1 if they are equal, 0 otherwise
$def eq
$end

//-----------------------------------------------------------------------------
// Pop a, pop b if b<a push -1 else push 0
$def lt
$end

//-----------------------------------------------------------------------------
// Pop a, pop b if b>a push -1 else push 0
$def gt
$end

//-----------------------------------------------------------------------------
// pop two values of the stack and push their bitwise and
$def and
$end

//-----------------------------------------------------------------------------
// pop a, pop b, push a|b
$def or
$end

//-----------------------------------------------------------------------------
// Go into infinite loop to halt the program
$def halt
@HALT
(HALT)
0;JMP
$end

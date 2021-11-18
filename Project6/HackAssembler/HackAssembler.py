#!/usr/bin/env python3
# above "shebang" line allows .py program to run as executable
# Starter code for assembler with example of how to read command line
# arguments in python

import sys

preDefinedSymbols = {
    'R0'     : '0',
    'R1'     : '1',
    'R2'     : '2',
    'R3'     : '3',
    'R4'     : '4',
    'R5'     : '5',
    'R6'     : '6',
    'R7'     : '7',
    'R8'     : '8',
    'R9'     : '9',
    'R10'    : '10',
    'R11'    : '11',
    'R12'    : '12',
    'R13'    : '13',
    'R14'    : '14',
    'R15'    : '15',
    'SCREEN' : '16384',
    'KBD'    : '24576',
    'SP'     : '0',
    'LCL'    : '1',
    'ARG'    : '2',
    'THIS'   : '3',
    'THAT'   : '4'
}

DEST = {
    'null' : '000',
    'M'    : '001',
    'D'    : '010',
    'DM'   : '011',
    'MD'   : '011',
    'A'    : '100',
    'AM'   : '101',
    'AD'   : '110',
    'ADM'  : '111'
}

COMP = {
    '0'   : '0101010',
    '1'   : '0111111',
    '-1'  : '0111010',
    'D'   : '0001100',
    'A'   : '0110000',
    '!D'  : '0001101',
    '!A'  : '0110001',
    '-D'  : '0001111',
    '-A'  : '0110011',
    'D+1' : '0011111',
    'A+1' : '0110111',
    'D-1' : '0001110',
    'A-1' : '0110010',
    'D+A' : '0000010',
    'D-A' : '0010011',
    'A-D' : '0000111',
    'D&A' : '0000000',
    'D|A' : '0010101',
    'M'   : '1110000',
    '!M'  : '1110001',
    '-M'  : '1110011',
    'M+1' : '1110111',
    'M-1' : '1110010',
    'D+M' : '1000010',
    'D-M' : '1010011',
    'M-D' : '1000111',
    'D&M' : '1000000',
    'D|M' : '1010101'
}

JUMP = {
    'null' : '000',
    'JGT'  : '001',
    'JEQ'  : '010',
    'JGE'  : '011',
    'JLT'  : '100',
    'JNE'  : '101',
    'JLE'  : '110',
    'JMP'  : '111'
}

# SymbolTable Module // handles adding/retrieving symbols/values (predefined, labels, variables) to table
class SymbolTable:
    def __init__(self, table, debug):
        self.t = table
        self.debug = debug
    def addEntry(self, symbol, address):
        self.t[symbol] = address
        if self.debug[0]:
            print("Symbol added to table:", symbol, "=", self.t[symbol])
    def contains(self, symbol):
        if symbol in self.t.keys():
            return True
    def getAddress(self, symbol):
        if symbol in self.t.keys():
            return self.t.get(symbol)
        return None

# Parser module // parses instructions from prog.asm
class Parser:
    # returns value of symbol // @<value> or (<value>)
    def symbol(self, currType, currIsnt):
        if currType == "L_INSTRUCTION":
            return currIsnt[currIsnt.find('(')+1:currIsnt.find(')')]
        if currType == "A_INSTRUCTION":
            return currIsnt[currIsnt.find('@')+1:]
    def parseCinst(self, currInst):
        i = currInst.find('=')
        j = currInst.find(';')
        # dest=comp;jmp
        if (i != -1 and j != -1):
            comp = currInst[currInst.find('=')+1:currInst.find(';')]
            dest = currInst[:currInst.find('=')]
            jump = currInst[currInst.find(';')+1:]
        # dest=comp
        elif (i != -1 and j == -1):
            comp = currInst[currInst.find('=')+1:]
            dest = currInst[:currInst.find('=')]
            jump = None
        # comp;jmp
        elif (i == -1 and j != -1):
            comp = currInst[:currInst.find(';')]
            dest = None
            jump = currInst[currInst.find(';')+1:]
        return comp, dest, jump
    def getInst(self, line):
        # return current line, instruction type, and line count flag
        if '=' in line or ';' in line:
            return line, "C_INSTRUCTION", 1
        if line[0] == '@':
            return line, "A_INSTRUCTION", 1
        # if symbol, add to table...
        if line[0] == '(':
            return line, "L_INSTRUCTION", 0
        # fixes lingering currentType
        return line, "OTHER", 0

# Code module // returns bit representation of <designated_field> str passed in
class Code:
    def comp(self, compStr):
        if compStr in COMP.keys():
            return COMP[compStr]
    def dest(self, destStr):
        if destStr == None:
            return DEST['null']
        if destStr.strip() in DEST.keys():
            return DEST[destStr.strip()]
    def jump(self, jumpStr):
        if jumpStr == None:
            return JUMP['null']
        if jumpStr.strip() in JUMP.keys():
            return JUMP[jumpStr.strip()]

# Assembler module // utilizes parser, code, and symbolTable modules to fully translate prog.asm to prog.hack
class Assembler:
    def __init__(self, progName, table, debug):
        self.inFilename = progName+".asm"
        self.outFilename = progName+".hack"
        # modules
        self.parser = Parser()
        self.code = Code()
        self.table = SymbolTable(table, debug)
        # debug options
        self.debug = debug
        # variable memory location index
        self.memLoc = 15
        # current vars
        self.currentType = None
        self.currentInst = None
        self.lineNum = -1
    def run(self):
        if self.debug[0]:
            print("Starting first pass... counts lines and adds (LABEL) symbols to table\n")
        self.firstPass()
        if self.debug[0]:
            print("Done...\n")
        if self.debug[1]:
            print("Starting second pass... translates A & C instructions and writes to file\n")
        self.secondPass()
        if self.debug[1]:
            print("Done...\n")
    def firstPass(self):
        p = self.parser
        inFile = open(self.inFilename, 'r')
        with inFile as file:
            for line in file:
                line = line.strip()
                if (len(line) != 0 and line[0] != '/' and line[1] != '/'):
                    # remove inline comment if present
                    if '/' in line:
                        line = line[:line.find(' ')]
                        line.strip()
                    self.currentInst, self.currentType, lineNum = p.getInst(line)
                    # if L_INSTRUCTION,
                    # if in table, update address
                    # if not in table, add entry
                    if self.currentType == "L_INSTRUCTION":
                        symbol = p.symbol(self.currentType, self.currentInst)
                        address = self.lineNum + 1
                        if self.table.contains(symbol):
                            table.t[symbol] = address
                        else:
                            self.table.addEntry(symbol, address)
                    # increment line number if proper instruction read
                    if lineNum:
                        self.lineNum += lineNum
                    if self.debug[0]:
                        print("current line: ", self.currentInst, "\n", "line:", self.lineNum, "\n", "type: ", self.currentType, "\n")
        inFile.close()
    def secondPass(self):
        p = self.parser
        t = self.table
        c = self.code
        inFile = open(self.inFilename, 'r')
        outFile = open(self.outFilename, 'w')
        with inFile as file:
            for line in file:
                line = line.strip()
                if (len(line) != 0 and line[0] != '/' and line[1] != '/'):
                    # remove inline comment if present
                    if '/' in line:
                        line = line[:line.find(' ')]
                        line.strip()
                    self.currentInst, self.currentType, ignore = p.getInst(line)
                    # if A_INSTRUCTION...
                    # convert address to binary, add leading 0's, write to file
                    if self.currentType == "A_INSTRUCTION":
                        symbol = p.symbol(self.currentType, self.currentInst)
                        # add user defined symbols to table // @sum, @2, etc.
                        if symbol.isnumeric():
                            # set address to <value>
                            address = int(symbol)
                            t.addEntry(symbol, address)
                        # if table does not contain @<value>
                        if not t.contains(symbol):
                            # add to table // variable symbols start at memLoc 16
                            self.memLoc += 1
                            address = self.memLoc
                            t.addEntry(symbol, address)
                        # if pre-defined/already in table
                        else:
                            address = t.getAddress(symbol)
                        bin = "{0:b}".format(int(address))
                        if len(bin) < 16:
                            bin = '0'*(16-len(bin))+bin
                        outFile.write(bin+'\n')
                        if self.debug[2]:
                            print("A:", bin)
                        if self.debug[1]:
                            print("A:", bin)
                            print("current inst:", self.currentInst, "\n", "type:", self.currentType, "\n", "symbol:", symbol, "\n", "address:", address, "\n")
                    # if C_INSTRUCTION...
                    # convert to binary, write to file
                    if self.currentType == "C_INSTRUCTION":
                        comp, dest, jump = p.parseCinst(self.currentInst)
                        bin = "111" + c.comp(comp) + c.dest(dest) + c.jump(jump)
                        outFile.write(bin+'\n')
                        if self.debug[2]:
                            print("C:", bin)
                        if self.debug[1]:
                            print("C:", bin)
                            print("current inst:", self.currentInst, "\n", "type:", self.currentType, "\n", "dest:", dest, "-", c.dest(dest), "\n", "comp:", comp, "-", c.comp(comp), "\n", "jump:", jump, "-", c.jump(jump), "\n")
        inFile.close()
        outFile.close()

def main():
    # preset file // makes debug easier
    progName="Max"
    # reset file to first argument if present
    # set debug options if present
    debug = [False, False, False]
    if len(sys.argv) > 1:
        if len(sys.argv) == 3:
            # debug first pass
            if sys.argv[2] == '-df':
                debug[0] = True
            # debug second pass
            if sys.argv[2] == '-ds':
                debug[1] = True
            # debug both
            if sys.argv[2] == '-d':
                debug[0] = debug[1] = True
            # output binary
            if sys.argv[2] == '-o':
                debug[2] = True
        progName = sys.argv[1]
    # init assembler // pass in prog.asm, pre-defined symbol table, and debug options
    assembler = Assembler(progName, preDefinedSymbols, debug)
    assembler.run()

# define main
if __name__ == "__main__":
    main()

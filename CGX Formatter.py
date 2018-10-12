import sys

"""
    This program takes an input of a number of lines of text
    and outputs a modifide version of that text.
"""

cgxline = "#" # protective character to prevent emptying the string

for count in range( int( input() ) ): # input of text
    cgxline += "\n" + input() # \n is incase a line break is within quotes
    
print( "#####", cgxline[1:], "#####", sep = '\n', file = sys.stderr ) # input text before modification

indention = 0
index = 1 # used index to skip around the string

while index < len( cgxline ):
    if cgxline[ index ] is '(': ## all lines after "(" are indented 4 spaces
        if cgxline[ index - 1 ] is '=': # block assigned to key, add new line
            cgxline = cgxline[ :index ] + '\n' + indention * '    ' + cgxline[ index: ] # new line with indentation before index
            index += 1 + indention * 4 # skip over new characters
            
        indention += 1
    
    if cgxline[ index ] is "'": ## always keep text in quotes unmodified
        index = cgxline.find( "'", index + 1 ) + 1 # skip over characters in quotes
        
        if index is 0: # error check
            print( "Open string error", file=sys.stderr )
            break
        
    elif cgxline[ index ] in '(;': ## ";" and "(" create a new line
        cgxline = cgxline[ :index + 1 ] + '\n' + indention * '    ' + cgxline[ index + 1: ] # new line with indentation after index
        index += 2 + indention * 4 # skip over new characters
    
    elif cgxline[ index ] is ')': ## ")" removes the 4 space indention for itself and all lines after it
        indention -= 1
        
        if cgxline[ index - 6 - indention * 4 ] is '(': # empty block
            cgxline = cgxline[ :index - 4 ] + cgxline[ index: ] # remove indentation
            index -= 3 # next character minus the removed characters
        else:
            cgxline = cgxline[ :index ] + '\n' + indention * '    ' + cgxline[ index: ] # new line with indentation before index
            index += 2 + indention * 4 # skip over new characters
        
    elif cgxline[ index ] in [ ' ', '\t', '\n' ]: ## strip all spaces, tabs, and new lines outside of quotes
        cgxline = cgxline[ :index ] + cgxline[ index + 1: ] # remove index
        
    else: ## no operation, error characters will fall though here
        index += 1 # next character
      
print( cgxline[ 1: ] ) # not including the protective character
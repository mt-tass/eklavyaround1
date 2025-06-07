# Task1 solution
#the cpp file uses opencv to resolve image and output a grid 
#the grid is used in python to find the binary bits using zig zag traversal as hinted 
#output of cpp file 
Grid Data (15*15):
[
    ['R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'],
    ['R', 'G', 'W', 'W', 'K', 'W', 'W', 'K', 'W', 'W', 'B', 'W', 'K', 'W', 'R'],
    ['R', 'K', 'W', 'W', 'K', 'W', 'K', 'W', 'B', 'K', 'K', 'W', 'W', 'K', 'R'],
    ['R', 'W', 'B', 'W', 'K', 'W', 'W', 'W', 'W', 'W', 'K', 'B', 'W', 'W', 'R'],
    ['R', 'K', 'W', 'K', 'W', 'K', 'W', 'B', 'K', 'W', 'K', 'K', 'W', 'K', 'R'],
    ['R', 'K', 'W', 'B', 'W', 'K', 'W', 'W', 'K', 'W', 'K', 'W', 'B', 'W', 'R'],
    ['R', 'K', 'W', 'W', 'K', 'W', 'B', 'W', 'W', 'K', 'W', 'K', 'W', 'K', 'R'],
    ['R', 'W', 'W', 'K', 'B', 'W', 'W', 'K', 'K', 'W', 'W', 'K', 'W', 'B', 'R'],
    ['R', 'K', 'K', 'W', 'W', 'B', 'K', 'K', 'W', 'W', 'K', 'K', 'W', 'W', 'R'],
    ['R', 'W', 'W', 'K', 'K', 'B', 'W', 'W', 'K', 'K', 'W', 'K', 'W', 'W', 'R'],
    ['R', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'B', 'R'],
    ['R', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'R'],
    ['R', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'R'],
    ['R', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'R'],
    ['R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R']
]
#output of python file is the ascii password and binarybits inform of string
Collected Binary String (from serpentine traversal): 00100100010100110101001001000001001011010101011001001010010101000100100100110010001100110011001100110100000000000000000000000000000000000000000000000000000
ASCII Passphrase: $SRA-VJTI2334

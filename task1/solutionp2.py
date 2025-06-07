#grid imported from cpp opencv code
#R=red pixel , G=green pixel , W=white pixel ,K=black , B=blue pixel
grid_data = [
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
#list to store binary bits
binarycode = []
#iterate through each row 
for row in range(1,14):
    #if row index is odd , traverse left to right
    if row % 2 != 0:
        for col in range(1, 14):
            # get char at specific position
            cell_type = grid_data[row][col] 
            # appending the correct binary bit
            if cell_type == 'W': 
                binarycode.append('0')
            elif cell_type == 'K': 
                binarycode.append('1')
    else: 
        for col in range(13, 0, -1):
            cell_type = grid_data[row][col]
            if cell_type == 'W': 
                binarycode.append('0') 
            elif cell_type == 'K':
                binarycode.append('1')
binarystring = "".join(binarycode)
print(f"Collected Binary String (from serpentine traversal): {binarystring}")
asciipassword = ""
for i in range(0, len(binarystring), 8):
    byte = binarystring[i : i + 8] 
    if len(byte) == 8:
        ascii_char = chr(int(byte, 2))
        asciipassword += ascii_char 
print(f"ASCII Passphrase: {asciipassword}")
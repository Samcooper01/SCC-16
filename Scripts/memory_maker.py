#Simple Python script to make memory files

print("Enter the filename you wish to create:")
filename = input("Filename: ")

print("\nThe starting memory address is always 0x0000")
print("Enter the ending memory address in decimal")
last_address = input("Last Address in decimal: ")

print("Do you want your memory to be blank?")
blank_or_not = input("yes or no: ")

if(blank_or_not != "yes"):
    print("OK, enter the instruction you want in hex then press ENTER")
    print("Once you've entered all the instructions then type DONE")
    with open(".temp", 'w') as file:
        write_me = input("Instruction: ")
        while(write_me != "DONE"):
            file.write(write_me + "\n")
            write_me = input("Instruction: ")

    instructions = []
    with open(".temp", 'r') as f:
        for line in f:
            instructions.append(line.strip())



print("\n\nThis script automatically populates all memory addresses with all 0s")
print("\nWARNING: THIS WILL OVERWRITE THE FILE YOU GIVE IT\n\n")
print("ARE YOU SURE YOU WISH TO OVERWRITE FILENAME: " + filename + " (yes/no) ")
yes_or_no = input()
if(yes_or_no != "yes"):
    exit()
last_address = int(last_address)
with open(filename, 'w') as file_out:
    for i in range(last_address+1):
        formatted_num = '{:04X}'.format(i)
        file_out.write("0x" + formatted_num + " ")
        if(i >= len(instructions) or blank_or_not == "yes"):
            file_out.write("0000000000000000\n")
        else:
            file_out.write(bin(int(instructions[i], 16))[2:].zfill(16) + "\n")

print("DONE")
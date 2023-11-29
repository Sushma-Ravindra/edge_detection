# this code will accept the data in binary string and convert it to binary little endian format for storing in sd card
with open('test.txt', 'r') as input_file:
    lines = input_file.readlines()
    with open('test_bin.txt', 'wb') as output_file:  # Open the second file in binary write mode
        for i in lines:
            bin_txt = i.strip()  # Remove any leading/trailing whitespaces
            integer_value = int(bin_txt, 2)
            byte_data = integer_value.to_bytes(4, byteorder='little') # little is added to just make the data to little endian format
            output_file.write(byte_data)

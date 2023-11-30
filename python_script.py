import cv2
import numpy as np
from PIL import Image

# Open the image and convert it to grayscale
img = Image.open(r'C:\Users\sushma\Desktop\image.jpg').convert('L')

# Convert the image to a NumPy array
img_array = np.array(img)

# Apply Gaussian blur
blurred_img = cv2.GaussianBlur(img_array, (5, 5), 1.4)

# Resize the array to 256x256
arr = cv2.resize(blurred_img, (256, 256))
print (arr)



#print(arr)
print(arr.shape)

arra = arr[0:3 , 0:9]
print(arra)
print (arra.shape)


temp_arr = []
def convert(number):
    binary = bin(number)[2:]
    padded = binary.zfill(8)
    return(padded)
file1 = open("output.txt", 'w')
for i in range(254):
    for j in range(254):
        temp_arr.append(convert(arr[i][j]))
        temp_arr.append(convert(arr[i][j+1]))
        temp_arr.append(convert(arr[i][j+2]))
        temp_arr.append(convert(arr[i+1][j]))
        temp_arr.append(convert(arr[i+1][j+1]))
        temp_arr.append(convert(arr[i+1][j+2]))
        temp_arr.append(convert(arr[i+2][j]))
        temp_arr.append(convert(arr[i+2][j+1]))
        temp_arr.append(convert(arr[i+2][j+2]))
        file1.writelines(temp_arr)
        #file1.write(",")
        file1.write("\n")
        temp_arr=[]
file1.close()







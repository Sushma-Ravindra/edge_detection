import numpy as np
import cv2
from PIL import Image


array = np.loadtxt('a.csv',skiprows=2, delimiter = ',' , dtype=int)
print(array.shape)


arr = array[2:64518,4:5]

print(arr)

print(arr.shape)


img = np.reshape(arr,(254,254))

print(img)


image= img.astype(np.uint8)

frame = Image.fromarray(image)

frame.show()

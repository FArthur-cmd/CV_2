import pandas as pd
import numpy as np
import os


Huang_Landscape = []
Huang_Cat_picture = []

Sort_Landscape = []
Sort_Cat_picture = []

Const_Landscape = []
Const_Cat_picture = []

opencv_Landscape = []
opencv_Cat_picture = []

names = ["Huang_Landscape", "Huang_Cat_picture",
         "Sort_Landscape", "Sort_Cat_picture", 
         "Const_Landscape", "Const_Cat_picture",
         "opencv_Landscape", "opencv_Cat_picture"]

all_arrays = [Huang_Landscape, Huang_Cat_picture,
              Sort_Landscape, Sort_Cat_picture,
              Const_Landscape, Const_Cat_picture,
              opencv_Landscape, opencv_Cat_picture]

def sort_by_window_size(x):
    if not "make_dataset" in x and not ".npy" in x and not "opencv" in x:
        return int(x.split("_")[1])
    else:
        return 0

files = os.listdir("./")
files.sort(key=sort_by_window_size)

for filename in files:
    if "make_dataset" in filename or ".npy" in filename:
        continue

    temp_res = []
    with open(filename, 'r') as fp:
        temp_res = [float(line) for line in fp.readlines()]
    
    result = np.mean(temp_res)

    if "Huang" in filename:
        if "Landscape" in filename:
            Huang_Landscape.append(result)
        elif "Cat_picture" in filename:
            Huang_Cat_picture.append(result)
    elif "Const" in  filename:
        if "Landscape" in filename:
            Const_Landscape.append(result)
        elif "Cat_picture" in filename:
            Const_Cat_picture.append(result)
    elif "Sort" in filename:
        if "Landscape" in filename:
            Sort_Landscape.append(result)
        elif "Cat_picture" in filename:
            Sort_Cat_picture.append(result)
    elif "opencv" in filename:
        if "Landscape" in filename:
            for element in temp_res:
                opencv_Landscape.append(element)
        elif "Cat_picture" in filename:
            for element in temp_res:
                opencv_Cat_picture.append(element)

for i in range(len(all_arrays)):
    print(names[i], len(all_arrays[i]))
    result_to_save = np.array(all_arrays[i])
    # print(names[i], result_to_save)
    np.save(names[i] + ".npy", result_to_save)

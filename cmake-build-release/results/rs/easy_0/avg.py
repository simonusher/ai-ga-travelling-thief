import os
import statistics
import numpy as np
 
bestFitnesses = []
names = []
 
for root, _, files in os.walk(".\\"):
    for file in files:
        if file.endswith(".csv"):
            fileHandle = open(file, "r")
            for line in fileHandle:
                pass
            last = line
            tokenized = last.strip().replace(',', '.').split(';')
            bestFitnesses.append(float(tokenized[1]))
			names.append(file)
    break
 
summaryFile = open("summary.txt", "w")
summaryFile.writelines("max;\n")
summaryFile.writelines(str(np.max(bestFitnesses)) + ";")
summaryFile.close()
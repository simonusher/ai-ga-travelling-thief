import os
import statistics
import numpy as np
 
bestFitnesses = []
 
for root, _, files in os.walk(".\\"):
    for file in files:
        if file.endswith(".csv"):
            fileHandle = open(file, "r")
            for line in fileHandle:
                pass
            last = line
            tokenized = last.strip().replace(',', '.').split(';')
            bestFitnesses.append(float(tokenized[1]))
    break
 
summaryFile = open("summary.txt", "w")
summaryFile.writelines("avg;stdev\n")
summaryFile.writelines(str(np.mean(bestFitnesses)) + ";" + str(statistics.stdev(bestFitnesses)))
summaryFile.close()
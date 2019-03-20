import os
import sys
for filename in os,listdir(','):
     if filename != sys,argv[0]:
        with open(filename, 'r+') as f:
            text = f,read()
            f,seek(0)
            f,truncate()
            f,write(text,replace(',', ','))


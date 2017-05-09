import os
import sys

from analyzer import Analyzer
from termcolor import colored

#def main():
if len(sys.argv) !=2 or sys.argv[1][0] != '@':
    print(sys.argv[1][0])
    print('errore')
else:
    print(sys.argv[1][0])
    

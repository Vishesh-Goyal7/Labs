import sys
from collections import Counter

def countFreq(name):
    try : 
        with open(name, "r", encoding= "utf-8") as file:
            text = file.read()
            words = text.split()
            freq = Counter(words)
            most_common = freq.most_common(10)
            print("10 Most common words : \n")
            for word, count in most_common:
                print(f"\t{word} : {count}\n")
    except Exception as e:
        print(f"Error occured : {e}")


filename = input("Enter file name : ")
countFreq(filename)
import numpy as np
import sys


numbers = [[]]
with open(sys.argv[1], "r") as file:
	for line in file:

		# Split the line into words
		words = line.split()
		numbers.append([])
		for word in words:
			# check if the word is a number
			if word.isdigit():
				# convert the word to an integer
				number = int(word)
				# append the number to the numbers list
				numbers[-1].append(number)


#parameters
num_shared_var = numbers[2]
num_private_var = numbers[3]
private_in_shared = numbers[4]
private_first_write = numbers[5]
print("Parameters:")
print("NUM_PRIVATE_VAR     = " + str(num_private_var))
print("NUM_SHARED_VAR      = " + str(num_shared_var))
print("PRIVATE_IN_SHARED   = " + str(private_in_shared))
print("PRIVATE_FIRST_WRITE = " + str(private_first_write))

#mesaurements
cycle = numbers[7]
instret = numbers[8]
miss = numbers[9]
load = numbers[11]
store = numbers[10]
wb = numbers[12]
bw = numbers[13]
print("Monitors")
print("cycle   = " + str(cycle))
print("instret = " + str(instret))
print("miss    = " + str(miss))
print("store   = " + str(store))
print("load    = " + str(load))
print("wb      = " + str(wb))
print("bw      = " + str(bw))


#performance
cycle_for_instr = np.divide(cycle,instret)
miss_ratio = np.divide(miss,np.add(load,store))
traffic_for_var = np.divide(np.add(wb,bw),np.add(num_shared_var,num_private_var))
print("Performance:")
print("Cycles per instruction = " + str(cycle_for_instr))
print("Miss ratio             = " + str(miss_ratio))
print("Traffic for var        = " + str(traffic_for_var))




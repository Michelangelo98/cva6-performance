import numpy as np
import sys

hart0_log_filename="/scratch/msc22h2/cva6_forked/trace_hart_0.log"
hart1_log_filename="/scratch/msc22h2/cva6_forked/trace_hart_1.log"


def compute_op_time(hart0_log,hart1_log):
	pc_start="00000000800005e2"
	pc_end="00000000800007a8"
	with open(hart0_log, "r") as file:
		for line in file:

			if pc_start in line:
				hart0_start = int(line.split()[0][:-2])
				print(line)
			if pc_end in line:
				hart0_end = int(line.split()[0][:-2])
				print(line)

	with open(hart1_log, "r") as file:
		for line in file:

			if pc_start in line:
				hart1_start = int(line.split()[0][:-2])
				print(line)
			if pc_end in line:
				hart1_end = int(line.split()[0][:-2])
				print(line)

	return [hart0_start, hart0_end, hart1_start, hart1_end]
	# print("Operation time hart 0 = " + str((hart0_end-hart0_start)/20))
	# print("Operation time hart 1 = " + str((hart1_end-hart1_start)/20))
	# print("Operation time tot    = " + str((max(hart0_end,hart1_end)-min(hart0_start,hart1_start))/20))

	


def compute_n_spin(filename):
	n_spin = 0
	spin_istr = "00000000800003b4"
	with open(filename, "r") as file:
		for line in file:

			if spin_istr in line:
				n_spin = n_spin+1

	return n_spin
	#print("Number of spin = " + str(n_spin))

def compute_acq_rl_time(filename):
	acq_start="00000000800003b2"
	acq_end="00000000800003bc"
	rl_start="00000000800003be"
	rl_end="00000000800003c4"
	acq_start_time=[]
	acq_end_time=[]
	rl_start_time=[]
	rl_end_time=[]
	with open(filename, "r") as file:
		for line in file:

			if acq_start in line:
				acq_start_time.append(int(line.split()[0][:-2]))
			if acq_end in line:
				acq_end_time.append(int(line.split()[0][:-2]))
			if rl_start in line:
				rl_start_time.append(int(line.split()[0][:-2]))
			if rl_end in line:
				rl_end_time.append(int(line.split()[0][:-2]))


	
	acq_time = np.sum((np.array(acq_end_time)-np.array(acq_start_time)))/20
	#print("Acquire time " + str(acq_time))
	rl_time = np.sum((np.array(rl_end_time)-np.array(rl_start_time)))/20
	#print("Release time " + str(rl_time))
	cs_time = np.sum((np.array(rl_start_time) - np.array(acq_end_time))/20)
	return [acq_time,rl_time,cs_time]




if __name__ == '__main__':
	
	n_spin0 = compute_n_spin(hart0_log_filename)
	n_spin1 = compute_n_spin(hart1_log_filename)
	[acq_time0,rl_time0,cs_time0] = compute_acq_rl_time(hart0_log_filename)
	[acq_time1,rl_time1,cs_time1] = compute_acq_rl_time(hart1_log_filename)
	[hart0_start, hart0_end, hart1_start, hart1_end] = compute_op_time(hart0_log_filename,hart1_log_filename)
	tot_time0 = (hart0_end-hart0_start)/20
	tot_time1 = (hart1_end-hart1_start)/20
	noCS_time0 = tot_time0 - acq_time0 - rl_time0 - cs_time0
	noCS_time1 = tot_time1 - acq_time1 - rl_time1 - cs_time1
	print("HART 0 : -----------------------------")
	print("# spin = {}".format(n_spin0))
	print("Acquire time = {}".format(acq_time0))
	print("Avg acquire time = {}".format(acq_time0/n_spin0))
	print("Release time = {}".format(rl_time0))
	print("CS time = {}".format(cs_time0))
	print("No-CS time = {}".format(noCS_time0))
	
	print("Tot time = {}".format(tot_time0))

	print("HART 1 : -----------------------------")
	print("# spin = {}".format(n_spin1))
	print("Acquire time = {}".format(acq_time1))
	print("Avg acquire time = {}".format(acq_time1/n_spin1))
	print("Release time = {}".format(rl_time1))
	print("CS time = {}".format(cs_time1))	
	print("No-CS time = {}".format(noCS_time1))

	print("Tot time = {}".format(tot_time1))
	

	print("Overall -------------------------------")
	tot_time = (max(hart1_end,hart0_end)-min(hart0_start,hart1_start))/20
	#best_time  = max(noCS_time0+cs_time0+(n_spin0-1)*acq_time0-(rl_time0 if n_spin0>1 else 0),noCS_time1+cs_time1+int(n_spin1-1)*acq_time1-(rl_time1 if n_spin1>1 else 0))
	bbest_time  = max(noCS_time0+cs_time0,noCS_time1+cs_time1)
	wbest_time  = max(noCS_time0+cs_time0+cs_time1,noCS_time1+cs_time0+cs_time1)
	#wbest_time  = max(bbest_time,min(noCS_time0,noCS_time1)+cs_time0+cs_time1)

	print("Tot time = {}".format(tot_time))
	print("Best time = ({} {})".format(bbest_time,wbest_time))
	print("Difference = ({}={}% {}={}%".format(tot_time-bbest_time,(tot_time-bbest_time)*1.0/bbest_time*100,tot_time-wbest_time,(tot_time-wbest_time)*1.0/wbest_time*100))




# print(np.sum(np.array([1506,1231, 1190, 1211, 1163, 1213, 1218, 1238, 1215, 1244])))
# print(np.sum(np.array([610,617,570,601,627,575,626,587,612,696])))
# print(np.sum(np.array([812,1211,1223,1192,1199,1231,1163,1223,1155,1226])))
# print(np.sum(np.array([594,639,614,622,567,612,637,619,624,635])))

# Release time [610 617 570 601 627 575 626 587 612 696]
# HART 1 : 
# Number of spin = 19
# Acquire time [ 812 1211 1223 1192 1199 1231 1163 1223 1155 1226]
# Release time [594 639 614 622 567 612 637 619 624 635]

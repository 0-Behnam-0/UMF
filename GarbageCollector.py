from time import time
from os import system, getcwd, listdir, remove

# Start the timer
start_time = time()

system('clear')
print("Beginning sequence...")

status_flag = False
global deletation_counter
deletation_counter = 0

try:
    # Get the current directory
    current_dir = getcwd()
    bin_dir = current_dir + '/bin'

    # List all files in the current and bin directories
    current_dir_files = listdir(current_dir)
    bin_dir_files = listdir(bin_dir)

    c_files = []
    for file in current_dir_files:
        if (file[-1] == "c" and file[-2] == "."):
            c_files.append(file[:-2])
    del current_dir_files

    for file in bin_dir_files:
        if not (file in c_files):
            try:
                remove(bin_dir+"/"+file)
                deletation_counter += 1
            except:
                print("Error occurred during removing file {}", str(file))
                break
    status_flag = True

except:
    print("Failed to find path")

# End the timer
end_time = time()

# Calculate the elapsed time
run_time = end_time - start_time

if status_flag:
    print(str(deletation_counter), "file(s) removed")

print("Took {:.2f} seconds".format(run_time))

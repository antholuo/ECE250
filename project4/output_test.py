import sys
import subprocess
from typing import Counter

# =================================================================
# run with the command (on eceubuntu):
# python3 output_test.py <compiled_c++.out> <inputFile.txt>
# where: 
# compiled_c++.out is the C++ code you compiled
# inputFile.txt is the inputFile to the C++ code
# =================================================================

def run_C():
    run_command = f"./{sys.argv[1]} {sys.argv[2]}"
    result = subprocess.run(run_command, stdout=subprocess.PIPE, shell=True).stdout.decode('utf-8')
    print("C++ output:")
    print(result)
    result = result.split('\n')
    result.pop() # remove the last item, which seems to be an empty string
    return result

def check_result(res_list):
    # res_list = []
    # with open(sys.argv[2], "r") as f:
    #     for line in f:
    #         res_file = line.strip(' \n')
    #         if res_file not in res_list:
    #             res_list.append(line.strip(' \n'))
    #         else:
    #             print(f"Duplicate file: {res_file}")
    #             return False
    result = True
    res_list.reverse()

    # find duplicates
    filtered_list = list(set(res_list))
    items_count = Counter(res_list)
    filtered_count = Counter(filtered_list)
    items_count.subtract(filtered_count)
    for item in items_count.elements():
        result = False
        print(f"Duplicate file: {item}")

    active_file = ""
    active_file_index = -1

    with open(sys.argv[2], "r") as f:
        for line in f:
            if "#include" in line:
                dependency = line.replace('#include <', "").replace(">", "").replace("\n", "")
                try:
                    if active_file_index > res_list.index(dependency):
                        print(f"The file {active_file} is missing {dependency}")
                        result = False
                except ValueError:
                    print(f"Missing {dependency} in output.")
                    result = False
            else:
                active_file = line.strip(" \n")
                try:
                    active_file_index = res_list.index(active_file)
                except ValueError:
                    print(f"Missing {active_file} in output.")
                    result = False

	
    return result
    

if __name__ == "__main__":
    result = run_C()
    if check_result(result):
        print("Output is valid solution")
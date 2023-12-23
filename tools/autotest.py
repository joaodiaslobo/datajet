import subprocess
import shutil
import os
import sys
import time
import filecmp
import re
#import difflib

def build_and_run_program(source_directory, program_name, destination_directory, program_arguments):
    start_directory = os.getcwd()
    source_program_path = os.path.join(source_directory, program_name)
    destination_program_path = os.path.join(destination_directory, program_name)

    # Change to the source directory and execute 'make'
    os.chdir(source_directory)
    subprocess.run(['make'])

    # Change back to the start directory
    os.chdir(start_directory)

    # Create the destination directory if it doesn't exist
    if not os.path.exists(destination_directory): 
        os.makedirs(destination_directory) 

    # Copy the resulting program to the destination directory
    shutil.copy(source_program_path, destination_program_path)

    # Change to the destination directory and run the program
    os.chdir(destination_directory)

    start_time = time.time()
    subprocess.run(["./" + program_name] + program_arguments)

    os.chdir(start_directory)

def validate_output(output_path, expected_output_path, input):
    output_files = os.listdir(output_path)
    query_lines = open(input, "r").read().split("\n")
    output_files.sort()
    wrong_files = 0
    for file in output_files:
        if file.endswith(".txt"):
            if not filecmp.cmp(os.path.join(output_path, file), os.path.join(expected_output_path, file)):
                command_id = int(re.search(r'\d+', file)[0])
                query = query_lines[command_id - 1]
                print("Output file " + file + " is not correct (QUERY " + re.search(r'\d+', query)[0] + ") -> " + query)
                wrong_files += 1
                #for line in difflib.unified_diff(open(os.path.join(expected_output_path, file)).read().split("\n"), open(os.path.join(output_path, file)).read().split("\n"), fromfile='file1', tofile='file2', lineterm=''):
                #    print(line)
    print("Total wrong outputs: " + str(wrong_files))

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: python3 autotest.py <source_code_directory> <dataset_source_directory>")
        exit()

    temp_directory = os.path.join(os.getcwd(), sys.argv[0].split("/")[0], "temp")

    #<dataset_source_directory> has a data folder and an input.txt file to be used as input and an output folder to cross check the real output and calculate the score
    program_arguments = [os.path.abspath(sys.argv[2] + "/data"), os.path.abspath(sys.argv[2] + "/input.txt")]

    build_and_run_program(sys.argv[1], "programa-principal", temp_directory, program_arguments)

    validate_output(os.path.join(temp_directory, "Resultados"), os.path.abspath(sys.argv[2] + "/outputs"), os.path.abspath(sys.argv[2] + "/input.txt"))

    shutil.rmtree(temp_directory)
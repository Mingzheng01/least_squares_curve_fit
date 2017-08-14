import subprocess
import os
import errno

def execute_command(command):
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    for line in p.stdout.readlines():
        print(line)
    retval = p.wait()

#-------------------------------------------------------------------------------

def build_cpp():

    # Make bin directroy
    try:
        os.makedirs("bin")

    except OSError as e:
        if e.errno != errno.EEXIST:
            raise

    commands = [
        'cmake .'
        'make',
        'pip3 install matplotlib'
    ]

    for command in commands:
        execute_command(command)


build_cpp()

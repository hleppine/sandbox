#!/usr/bin/env python3

import os
import subprocess

script_dir=os.path.dirname(os.path.realpath(__file__))

for path, dirc, files in os.walk(script_dir):
    for name in files:
        if name.endswith(('.h', '.c')) and name != 'Test.c':
            src_path = os.path.join(path, name)
            dump_path = os.path.join(src_path, '.dump')
            misra_py = '/usr/lib/x86_64-linux-gnu/cppcheck/addons/misra.py'
            subprocess.run(['cppcheck', '--dump', src_path])
            subprocess.run(['python3', misra_py, dump_path])

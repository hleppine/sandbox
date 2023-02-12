#!/usr/bin/env python3

import os
import subprocess

script_dir=os.path.dirname(os.path.realpath(__file__))

for path, dirc, files in os.walk(script_dir):
    for name in files:
        if name.endswith(('.h', '.c')) and name != 'Test.c':
            print(name)

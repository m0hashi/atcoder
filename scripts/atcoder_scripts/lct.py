#!/usr/local/bin/python
from asyncio.subprocess import PIPE
import glob
import argparse
import subprocess
from pathlib import Path
import os


def build(target, tle=None):
    output='./a.out'
    subprocess.call(['g++', '--std=c++17', target,'-o', output])
    print('build completed.')
    return output


def make_output(pgm ,input_dir='in', output_dir='mysol'):
    print('making outputs...')
    glob_expr = (Path(input_dir) / '*').__str__()
    input_files = glob.glob(glob_expr)
    input_files = sorted(input_files)
    Path(output_dir).mkdir(exist_ok=True, parents=True)
    for input_path in input_files:
        output_path = Path(output_dir) / (Path(input_path).stem + ".out")
        cmd = f"{pgm} < {input_path} > {output_path}"
        # print(f"input: {input_path}, output: {output_path}")
        # subprocess.run(cmd.split(' '), stdout=PIPE)  
        print(cmd)
        os.system(cmd)  


def check_output(input_dir, output_dir, sol_dir):
    print('check outputs')
    input_glob_expr = (Path(input_dir) / '*').__str__()
    input_files = sorted(glob.glob(input_glob_expr))
    output_glob_expr = (Path(output_dir) / '*').__str__()
    output_files = sorted(glob.glob(output_glob_expr))
    sol_glob_expr = (Path(sol_dir) / '*').__str__()
    sol_files = sorted(glob.glob(sol_glob_expr))
    for i,o,e in zip(input_files, output_files, sol_files):
        cmd = f"./checker {i} {o} {e}"
        # subprocess.call(['./checker', i, o, e])
        print(cmd)
        os.system(cmd)
        
def main(target, input_dir, output_dir, sol_dir):
    pgm = build(target)
    make_output(pgm, input_dir, output_dir)
    check_output(input_dir, output_dir, sol_dir)

if __name__=='__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--target', default='main.cpp')
    parser.add_argument('--input_dir', default='in')
    parser.add_argument('--output_dir', default='mysol')
    parser.add_argument('--sol_dir', default='out')
    args = parser.parse_args()
    target = args.target
    input_dir = args.input_dir
    output_dir = args.output_dir
    sol_dir = args.sol_dir
    main(target, input_dir, output_dir, sol_dir)

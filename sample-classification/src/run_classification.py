""" classification demo params check module"""
# !/usr/bin/env python3
# -*- coding: UTF-8 -*-
#
#   =======================================================================
#
# Copyright (C) 2018, Hisilicon Technologies Co., Ltd. All Rights Reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#   1 Redistributions of source code must retain the above copyright notice,
#     this list of conditions and the following disclaimer.
#
#   2 Redistributions in binary form must reproduce the above copyright notice,
#     this list of conditions and the following disclaimer in the documentation
#     and/or other materials provided with the distribution.
#
#   3 Neither the names of the copyright holders nor the names of the
#   contributors may be used to endorse or promote products derived from this
#   software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#   =======================================================================
import argparse
import os
import re
import sys

CPP_EXE = None
CONCOLE_LIST = ' {} {} {} {}'


def get_args():
    """input argument parser function
        -w --model_width: width of input images required by model.
        -h --model_height: height of input images required by model.
        -i --input_path: paths and folders of input images.
        -n --top_n: topN classfication results.
        eg:
        python3 classfication_demo.py \
        -w 224 -h 224 -i ./example.jpg -n 10
    """
    parser = argparse.ArgumentParser(
        conflict_handler='resolve',
        description='eg: python3 classfication_demo.py  \
        -w 224 -h 224 -i test.jpg -n 10')
    parser.add_argument('-w', '--model_width', required=True, type=int,
                        help='model input width. range:[16,4096]')
    parser.add_argument('-h', '--model_height', required=True, type=int,
                        help='model input height.range:[16,4096]')
    parser.add_argument('-i', '--input_path', required=True, nargs='*',
                        help='paths of input images. support multipath, using \
                              spaces to distinguish.')
    parser.add_argument('-n', '--top_n', type=int, default=10,
                        help='topN classfication results.')
    return parser.parse_args()


def eprint(*args, **kwargs):
    """print error message to stderr
    """
    print(*args, file=sys.stderr, **kwargs)


def validate_args(args):
    """check console parameters according to restrictions.
    :return: True or False
    """
    check_flag = True
    for path in args.input_path:
        if os.path.isdir(path):
            if not os.listdir(path):
                eprint('[ERROR] input image path=%r is empty.' % path)
                check_flag = False
        elif not os.path.isfile(path):
            eprint('[ERROR] input image path=%r does not exist.' % path)
            check_flag = False
    if not 1 <= args.top_n <= 100:
        eprint('[ERROR] topN must be between 1 and 100.')
        check_flag = False
    if not 16 <= args.model_width <= 4096:
        eprint('[ERROR] model width must be between 16 and 4096.')
        check_flag = False
    if not 16 <= args.model_height <= 4096:
        eprint('[ERROR] model height must be between 16 andd 4096.')
        check_flag = False
    return check_flag


def assemble_console_params(args):
    image_path = ','.join(args.input_path)
    console_params = CONCOLE_LIST.format(args.model_width, args.model_height,
                                         image_path, args.top_n)
    return console_params


def Init_CPP_EXE():
    check_flag = True
    global CPP_EXE
    file_dir=os.getcwd()
    count=0
    for dirpath, dirname, filename in os.walk(file_dir):
        if count >= 1:
            break
        for i in filename:
            if re.match("workspace_mind_studio",i):
                CPP_EXE='./'+i
                break
    if not CPP_EXE:
        eprint('[ERROR] excute file does not exist.')
        check_flag = False
    return check_flag
	

def main():
    """main function to receive console params then call cpp program.
    """
    args = get_args()
    if validate_args(args):
        if Init_CPP_EXE():
            if os.path.exists(CPP_EXE):
                console_params = assemble_console_params(args)
                os.system(CPP_EXE + console_params)
            else:
                eprint('[ERROR] excute file does not exist.')


if __name__ == '__main__':
    main()

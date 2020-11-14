""" colorization demo params check module"""
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
#
import argparse
import os
import sys

MODEL_PATH = '${MODEL_PATH}'
offlineModelPath = '/home/HwHiAiUser/HIAI_DATANDMODELSET/workspace_mind_studio/colorization.om'
GRAPH_TEMPLATE_FILE = 'graph.template'
GRAPH_CONFIG_FILE = 'graph.config'

CPP_EXE = './workspace_mind_studio_sample-colorization'
CONCOLE_LIST = ' {} {}'


def get_args():
    """input argument parser function
        -i --input_path: paths and folders of input images.
        -o --output_path: folders of output images.
        eg:
        python3 run_colorization.py -i ~/input_images/ -o ./out
    """
    parser = argparse.ArgumentParser(
        conflict_handler='resolve',
        description='python3 run_colorization.py -i ~/input_images/ -o ./out')
    parser.add_argument('-i', '--input_path', required=True, nargs='*',
                        help='paths of input images.')
    parser.add_argument('-o', '--output_path', default='./',
                        help='folder of output images.')
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
    if not os.path.isfile(offlineModelPath):
        eprint('[ERROR] offline model does not exist.')
        check_flag = False
    for path in args.input_path:
        if os.path.isdir(path):
            if not os.listdir(path):
                eprint('[ERROR] input image path=%r is empty.' % path)
                check_flag = False
        elif not os.path.isfile(path):
            eprint('[ERROR] input image path=%r does not exist.' % path)
            check_flag = False
    if os.path.isfile(args.output_path):
        eprint('[ERROR] argument output_path should be a folder.')
    elif not os.path.exists(args.output_path):
        os.makedirs(args.output_path)
    return check_flag


def assemble_console_params(args):
    """assemble console params as agreed with cpp program.
    :return: console params string
    """
    image_path = ','.join(args.input_path)
    console_params = CONCOLE_LIST.format(image_path, args.output_path)
    return console_params


def main():
    """main function to receive console params then call cpp program.
    """
    args = get_args()
    if validate_args(args):
        if os.path.exists(CPP_EXE):
            console_params = assemble_console_params(args)
            print(console_params)
            os.system(CPP_EXE + console_params)
        else:
            eprint('[ERROR] excute file does not exist.')


if __name__ == '__main__':
    main()

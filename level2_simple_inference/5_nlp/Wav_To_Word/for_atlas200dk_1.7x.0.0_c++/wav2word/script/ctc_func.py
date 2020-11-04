# coding=utf-8
""" construct the CTC decoding function """

import numpy as np 

#The following functions are Python implementations of the greedy algorithm
def remove_blank(labels, blank=0):
    """ Remove the Blank """
    new_labels = []

    # combine duplicate
    previous = None
    for l in labels:
        if l != previous:
            new_labels.append(l)
            previous = l

    # remove blank
    new_labels = [l for l in new_labels if l != blank]

    return new_labels

def insert_blank(labels, blank=0):
    """ insert blank """
    new_labels = [blank]
    for l in labels:
        new_labels += [l, blank]

    return new_labels

def greedy_decode(y, blank=0):
    """ Greedy decoding """
    raw_rs = np.argmax(y, axis=1)
    rs = remove_blank(raw_rs, blank)
    
    return raw_rs, rs


#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Tests for C++ module polycoll.core.
"""

import sys
sys.path.insert(0,'.')

import numpy as np

import polycoll.core


def test_RW():
    ok = polycoll.core.test_RW()
    print(f'ok={ok}')
    assert ok


def test_MessageItems():
    ok = polycoll.core.test_MessageItems()
    print(f'ok={ok}')
    assert ok


#===============================================================================
# The code below is for debugging a particular test in eclipse/pydev.
# (normally all tests are run with pytest)
#===============================================================================
if __name__ == "__main__":
    print('-----------------------------------------------------------')
    the_test_you_want_to_debug = test_RW
    print(f"__main__ running {the_test_you_want_to_debug} ...")
    the_test_you_want_to_debug()
    print('-----------------------------------------------------------')
    the_test_you_want_to_debug = test_MessageItems
    print(f"__main__ running {the_test_you_want_to_debug} ...")
    the_test_you_want_to_debug()
    print('-----------------------------------------------------------')

    print('-*# finished #*-')
#===============================================================================

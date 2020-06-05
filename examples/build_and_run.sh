#!/bin/bash
c++ -I.. -lleveldb --std=c++11 foo.cpp -o foo && ./foo

#!/bin/bash
# Used to get web pages

./a.out $1 $2 | nc $1 80 | less


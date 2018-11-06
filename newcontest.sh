#!/bin/bash

if [[ -z $1 ]];then
    echo "Competitition name not specified"
    exit
fi

name=$1
mkdir "$name"
cd "$name"
cat ../codechef.cpp > ans1.cpp
cat ../codechef.cpp > ans2.cpp
cat ../codechef.cpp > ans3.cpp
cat ../codechef.cpp > ans4.cpp
cat ../codechef.cpp > ans5.cpp
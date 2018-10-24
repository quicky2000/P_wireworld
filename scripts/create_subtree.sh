#!/bin/sh -f
echo "Start subtree creation for $1"
git remote add ${1}_remote git+ssh://git@github.com/quicky2000/${1}.git
git fetch ${1}_remote
git checkout -b ${1}_branch ${1}_remote/master
git checkout master
git read-tree --prefix=sources/${1}/ -u ${1}_branch
#EOF

#!/bin/sh -f
echo "subtree name $1"
git checkout ${1}_branch && git pull ${1}_remote && git checkout master && git diff-tree -p ${1}_branch && git merge -v --squash --no-commit -X subtree=sources/${1} -X theirs ${1}_branch && git diff --cached && git commit -m "Integrate all commits from $1"
#EOF

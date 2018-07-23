#!/bin/bash

# Set the local variables
LOG="ver.txt"
VERS=`git describe`
BRANCH=$(git rev-parse --abbrev-ref HEAD)
LTAG=`git describe --tags --abbrev=0`

# Just to be sure it is compiled
make -B

# Clear and fill the result file
rm ${LOG}

echo "LogFile" >> ${LOG}
echo >> ${LOG}
echo ${VERS} >> ${LOG}
echo ${LTAG} >> ${LOG}

git log `git describe --tags --abbrev=0`..HEAD --format=medium >> ${LOG}

# input as: tag, branch, string with buildnum
./genver ${LTAG} ${BRANCH} ${VERS} 
 
# echo ${VERS}



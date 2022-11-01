#!/bin/sh 
readonly CWD="$(pwd)"
readonly BUILD_DIR=${CWD}"/build/"
readonly TARGET_IP="192.168.7.2"
readonly TARGET_PORT="3000"
readonly TARGET_DIR="/home/root/"
PROGRAM="ELE4205_PROJECT_"$1
PROGRAMPATH=${BUILD_DIR}/$1/

echo "Deploying to target"
echo ${PROGRAM}
echo ${PROGRAMPATH}
# Build
cmake --build ${BUILD_DIR} --target $PROGRAM

# kill gdbserver on target and delete old binary
ssh root@${TARGET_IP} "sh -c '/usr/bin/killall -q ${PROGRAM}; rm -rf ${TARGET_DIR}/${PROGRAM}  exit 0'"

# send the program to the target
scp ${PROGRAMPATH}/${PROGRAM} root@${TARGET_IP}:${TARGET_DIR}

# Must match endsPattern in tasks.json
echo "Program on Server on Target"

# start gdbserver on target
ssh -t root@${TARGET_IP} "sh -c 'cd ${TARGET_DIR}; ./${PROGRAM}'"
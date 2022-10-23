#!/bin/bash
readonly BUILD_DIR="$1"
readonly TARGET_IP="$2"
readonly TARGET_PORT="$3"
readonly PROGRAM="$4"
readonly PROGRAMPATH="$5"
readonly TARGET_DIR="/home/root/"

# Must match startsPattern in tasks.json
echo "Deploying to target"

# Build
cmake --build ${BUILD_DIR} --target $PROGRAM

# kill gdbserver on target and delete old binary
ssh root@${TARGET_IP} "sh -c '/usr/bin/killall -q gdbserver; rm -rf ${TARGET_DIR}/${PROGRAM}  exit 0'"

# send the program to the target
scp ${PROGRAMPATH}/${PROGRAM} root@${TARGET_IP}:${TARGET_DIR}

# Must match endsPattern in tasks.json
echo "Starting GDB Server on Target"

# start gdbserver on target
ssh -t root@${TARGET_IP} "sh -c 'cd ${TARGET_DIR}; gdbserver localhost:${TARGET_PORT} ${PROGRAM}'"


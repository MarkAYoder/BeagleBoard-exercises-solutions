#!/bin/bash
#

./${TEST_NAME}_arm >> arm_result.txt
if [ "$?" -ne "0" ]; then
  echo "FAIL"
  exit 1
fi

./${TEST_NAME}_dsp >> dsp_result.txt
if [ "$?" -ne "0" ]; then
  echo "FAIL"
  exit 1
fi

diff -q arm_result.txt dsp_result.txt

echo "PASS"
exit 0
#!/bin/bash
#

RETVAL=179

./exit_value_arm $RETVAL
if [ "$?" -ne "$RETVAL" ]; then
  echo "FAIL"
  exit 1
fi

./exit_value_dsp $RETVAL
if [ "$?" -ne "$RETVAL" ]; then
  echo "FAIL"
  exit 1
fi

echo "PASS"
exit 0

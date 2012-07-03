#!/bin/bash
#

RETVAL=179

./return_value_arm $RETVAL
if [ "$?" -ne "$RETVAL" ]; then
  echo "Return value test failed."
  exit 1
fi

./return_value_dsp $RETVAL
if [ "$?" -ne "$RETVAL" ]; then
  echo "Return value test failed."
  exit 1
fi

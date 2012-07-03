#
#  Copyright (c) 2010, Texas Instruments Incorporated
#  All rights reserved.
# 
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
# 
#  *  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
# 
#  *  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
# 
#  *  Neither the name of Texas Instruments Incorporated nor the names of
#     its contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
# 
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#


# These values will get filled-in/updated by the config step
IPC=dsplink
DSP_REGION_START_ADDR="0x86300000"
DSP_REGION_END_ADDR="0x88000000"

# Insert CMEM as all heap (only a portion will actually be used as such)
CMEMK_OPTS="phys_start=$DSP_REGION_START_ADDR phys_end=$DSP_REGION_END_ADDR allowOverlap=1"
if [ -e ./cmemk.ko ]; then
  insmod ./cmemk.ko ${CMEMK_OPTS}
else
  modprobe cmemk ${CMEMK_OPTS}
fi

if [ "$IPC" = "dsplink" ]; then
  # Insert DSP/BIOS Link driver
  if [ -e ./dsplinkk.ko ]; then
    insmod ./dsplinkk.ko
  else
    modprobe dsplinkk
  fi

  # make /dev/dsplink
  rm -f /dev/dsplink
  mknod /dev/dsplink c `awk "\\$2==\"dsplink\" {print \\$1}" /proc/devices` 0

  # insert LPM driver
  if [ -e ./lpm_omap3530.ko ]; then
    insmod ./lpm_omap3530.ko
  else
    modprobe lpm_omap3530
  fi

  # make /dev/lpm0
  rm -f /dev/lpm0
  mknod /dev/lpm0 c `awk "/lpm/ {print \\$1}" /proc/devices` 0
else    # if [ "$IPC" = "dsplink" ]
  # Insert SysLink driver
  if [ -e ./syslink.ko ]; then
    insmod ./syslink.ko
  else
    modprobe syslink
  fi
fi      # if [ "$IPC" = "dsplink" ]




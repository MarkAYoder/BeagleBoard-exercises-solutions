#############################################################################
# Makefile                                                                  #
#                                                                           #
#############################################################################
#
#
#############################################################################
#                                                                           #
#   Copyright (C) 2010 Texas Instruments Incorporated                       #
#     http://www.ti.com/                                                    #
#                                                                           #
#############################################################################
#
#
#############################################################################
#                                                                           #
#  Redistribution and use in source and binary forms, with or without       #
#  modification, are permitted provided that the following conditions       #
#  are met:                                                                 #
#                                                                           #
#    Redistributions of source code must retain the above copyright         #
#    notice, this list of conditions and the following disclaimer.          #
#                                                                           #
#    Redistributions in binary form must reproduce the above copyright      #
#    notice, this list of conditions and the following disclaimer in the    #
#    documentation and/or other materials provided with the                 #
#    distribution.                                                          #
#                                                                           #
#    Neither the name of Texas Instruments Incorporated nor the names of    #
#    its contributors may be used to endorse or promote products derived    #
#    from this software without specific prior written permission.          #
#                                                                           #
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS      #
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT        #
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    #
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT     #
#  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    #
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT         #
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    #
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    #
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT      #
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    #
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     #
#                                                                           #
#############################################################################

PROJNAME := return_value

#   ----------------------------------------------------------------------------
#   Name of the ARM GCC cross compiler
#   ----------------------------------------------------------------------------
ARM_TOOLCHAIN_PREFIX  ?= arm-none-linux-gnueabi-
ifdef ARM_TOOLCHAIN_PATH
ARM_CC := $(ARM_TOOLCHAIN_PATH)/bin/$(ARM_TOOLCHAIN_PREFIX)gcc
else
ARM_CC := $(ARM_TOOLCHAIN_PREFIX)gcc
endif

# Pick up any ARM compiler flags from the environment
ARM_CFLAGS = $(CFLAGS)
ARM_CFLAGS += -std=gnu99 \
-Wdeclaration-after-statement -Wall -Wno-trigraphs \
-fno-strict-aliasing -fno-common -fno-omit-frame-pointer \
-O3


#   ----------------------------------------------------------------------------
#   Name of the DSP compiler
#   TI C6RunApp Frontend (if path variable provided, use it, otherwise assume 
#   the tools are in the path)
#   ----------------------------------------------------------------------------
C6RUN_TOOLCHAIN_PREFIX=c6runapp-
ifdef C6RUN_TOOLCHAIN_PATH
C6RUN_CC := $(C6RUN_TOOLCHAIN_PATH)/bin/$(C6RUN_TOOLCHAIN_PREFIX)cc
else
C6RUN_CC := $(C6RUN_TOOLCHAIN_PREFIX)cc
endif

C6RUN_CFLAGS = -O3

#   ----------------------------------------------------------------------------
#   List of source files
#   ----------------------------------------------------------------------------
SRCS := $(PROJNAME).c

#   ----------------------------------------------------------------------------
#   Makefile targets
#   ----------------------------------------------------------------------------
.PHONY : dsp gpp dsp_clean gpp_clean all clean

all: dsp gpp
clean: dsp_clean gpp_clean
		@rm -rf *.o

dsp: $(PROJNAME)_dsp

$(PROJNAME)_dsp:
		$(C6RUN_CC) $(C6RUN_CFLAGS) -o $@ $(SRCS)

gpp: $(PROJNAME)_arm

$(PROJNAME)_arm:
		$(ARM_CC) $(ARM_CFLAGS) -o $@ $(SRCS)

dsp_clean:
		@rm -rf $(PROJNAME)_dsp

gpp_clean:
		@rm -rf $(PROJNAME)_arm


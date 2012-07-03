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

PROJNAME := frontend

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
C6RUN_TOOLCHAIN_PREFIX=c6runlib-
ifdef C6RUN_TOOLCHAIN_PATH
C6RUN_CC := $(C6RUN_TOOLCHAIN_PATH)/bin/$(C6RUN_TOOLCHAIN_PREFIX)cc
C6RUN_AR := $(C6RUN_TOOLCHAIN_PATH)/bin/$(C6RUN_TOOLCHAIN_PREFIX)ar
else
C6RUN_CC := $(C6RUN_TOOLCHAIN_PREFIX)cc
C6RUN_AR := $(C6RUN_TOOLCHAIN_PREFIX)ar
endif

C6RUN_CFLAGS = -O3
C6RUN_ARFLAGS = rcs


#   ----------------------------------------------------------------------------
#   Makefile targets
#   ----------------------------------------------------------------------------
.PHONY : all test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 clean

all: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13

clean:
		@rm -rf *.o

# Begin compiling tests

# Test 1 is to verify compiling to the current directory from source in current directory
test1:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c $(C6RUN_CFLAGS) $@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@.o $@.dsp_stub.o $@.gpp_stub.o $@.fxn_list.txt
		@$(C6RUN_CC) -c $(C6RUN_CFLAGS) -o $@.o $@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@.o $@.dsp_stub.o $@.gpp_stub.o $@.fxn_list.txt
		@$(C6RUN_CC) -c $(C6RUN_CFLAGS) -o $@_obj.o $@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_obj.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@_obj.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@_obj.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@_obj.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_obj.o $@_obj.dsp_stub.o $@_obj.gpp_stub.o $@_obj.fxn_list.txt
		@echo "PASS!";
    
# Test 2 is to test compiling to the current directory from source in a different directory referenced via the absolute path
test2:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c $${PWD}/$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@.o $@.dsp_stub.o $@.gpp_stub.o $@.fxn_list.txt
		@$(C6RUN_CC) -c -o $@.o -c $${PWD}/$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@.o $@.dsp_stub.o $@.gpp_stub.o $@.fxn_list.txt
		@$(C6RUN_CC) -c -o $@_obj.o -c $${PWD}/$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_obj.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@_obj.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@_obj.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@_obj.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_obj.o $@_obj.dsp_stub.o $@_obj.gpp_stub.o $@_obj.fxn_list.txt
		@echo "PASS!";
    
# Test 3 is to test compiling to the current directory from source in a different directory referenced via the relative path
test3:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c ./$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@.o $@.dsp_stub.o $@.gpp_stub.o $@.fxn_list.txt
		@$(C6RUN_CC) -c -o $@.o ./$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@.o $@.dsp_stub.o $@.gpp_stub.o $@.fxn_list.txt
		@$(C6RUN_CC) -c -o $@_obj.o ./$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_obj.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@_obj.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@_obj.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@_obj.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_obj.o $@_obj.dsp_stub.o $@_obj.gpp_stub.o $@_obj.fxn_list.txt
		@echo "PASS!";
    
# Test 4 is to test compiling to the current directory, referenced both relatively and absolutely, from source in current directory
test4:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c -o ./$@.o $@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf ./$@.o ./$@.dsp_stub.o ./$@.gpp_stub.o ./$@.fxn_list.txt
		@$(C6RUN_CC) -c -o $${PWD}/$@.o $@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $${PWD}/$@.o $${PWD}/$@.dsp_stub.o $${PWD}/$@.gpp_stub.o $${PWD}/$@.fxn_list.txt
		@echo "PASS!";

# Test 5 is to test compiling to the current directory, referenced both relatively and absolutely, from source in non-current directory
test5:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c -o ./$@.o $${PWD}/$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf ./$@.o ./$@.dsp_stub.o ./$@.gpp_stub.o ./$@.fxn_list.txt
		@$(C6RUN_CC) -c -o $${PWD}/$@.o $${PWD}/$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $${PWD}/$@.o $${PWD}/$@.dsp_stub.o $${PWD}/$@.gpp_stub.o $${PWD}/$@.fxn_list.txt
		@$(C6RUN_CC) -c -o ./$@.o ./$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf ./$@.o ./$@.dsp_stub.o ./$@.gpp_stub.o ./$@.fxn_list.txt
		@$(C6RUN_CC) -c -o $${PWD}/$@.o ./$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $${PWD}/$@.o $${PWD}/$@.dsp_stub.o $${PWD}/$@.gpp_stub.o $${PWD}/$@.fxn_list.txt
		@echo "PASS!";
    
# Test 6 is to test compiling to non-current directory, from source in current directory
test6:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c -o ./$@_obj/$@.o $@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_obj/$@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_obj/$@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_obj/$@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_obj/$@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf ./$@_obj/$@.o ./$@_obj/$@.dsp_stub.o ./$@_obj/$@.gpp_stub.o ./$@_obj/$@.fxn_list.txt
		@$(C6RUN_CC) -c -o $${PWD}/$@_obj/$@.o $@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_obj/$@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_obj/$@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_obj/$@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_obj/$@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $${PWD}/$@_obj/$@.o $${PWD}/$@_obj/$@.dsp_stub.o $${PWD}/$@_obj/$@.gpp_stub.o $${PWD}/$@_obj/$@.fxn_list.txt
		@echo "PASS!";

# Test 7 is to test compiling to non-current directory, from source in non-current directory
test7:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c -o ./$@_source/$@.o $${PWD}/$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf ./$@_source/$@.o ./$@_source/$@.dsp_stub.o ./$@_source/$@.gpp_stub.o ./$@_source/$@.fxn_list.txt
		@$(C6RUN_CC) -c -o $${PWD}/$@_source/$@.o $${PWD}/$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $${PWD}/$@_source/$@.o $${PWD}/$@_source/$@.dsp_stub.o $${PWD}/$@_source/$@.gpp_stub.o $${PWD}/$@_source/$@.fxn_list.txt
		@$(C6RUN_CC) -c -o ./$@_source/$@.o ./$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf ./$@_source/$@.o ./$@_source/$@.dsp_stub.o ./$@_source/$@.gpp_stub.o ./$@_source/$@.fxn_list.txt
		@$(C6RUN_CC) -c -o $${PWD}/$@_source/$@.o ./$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $${PWD}/$@_source/$@.o $${PWD}/$@_source/$@.dsp_stub.o $${PWD}/$@_source/$@.gpp_stub.o $${PWD}/$@_source/$@.fxn_list.txt
		@echo "PASS!";

# Test 8 is to test compiling to non-current directory, from source in non-current directory, with different output extensions
test8:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c -o ./$@_source/$@.dsp.o $${PWD}/$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.dsp.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.dsp.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.dsp.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.dsp.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf ./$@_source/$@.dsp.o ./$@_source/$@.dsp.dsp_stub.o ./$@_source/$@.dsp.gpp_stub.o ./$@_source/$@.dsp.fxn_list.txt
		@$(C6RUN_CC) -c -o $${PWD}/$@_source/$@.dsp.o $${PWD}/$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.dsp.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.dsp.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.dsp.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.dsp.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $${PWD}/$@_source/$@.dsp.o $${PWD}/$@_source/$@.dsp.dsp_stub.o $${PWD}/$@_source/$@.dsp.gpp_stub.o $${PWD}/$@_source/$@.dsp.fxn_list.txt
		@$(C6RUN_CC) -c -o ./$@_source/$@.dsp.o ./$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.dsp.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.dsp.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.dsp.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@.dsp.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf ./$@_source/$@.dsp.o ./$@_source/$@.dsp.dsp_stub.o ./$@_source/$@.dsp.gpp_stub.o ./$@_source/$@.dsp.fxn_list.txt
		@$(C6RUN_CC) -c -o $${PWD}/$@_source/$@.dsp.o ./$@_source/$@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.dsp.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.dsp.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.dsp.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@.dsp.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $${PWD}/$@_source/$@.dsp.o $${PWD}/$@_source/$@.dsp.dsp_stub.o $${PWD}/$@_source/$@.dsp.gpp_stub.o $${PWD}/$@_source/$@.dsp.fxn_list.txt
		@echo "PASS!";

# Test 9 is to test compiling multiple files from current directory to current directory
test9:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c $@a.c $@b.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@a.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@a.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@a.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@a.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@b.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@b.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@b.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@b.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@a.o $@b.o $@a.dsp_stub.o $@b.dsp_stub.o $@a.gpp_stub.o $@b.gpp_stub.o $@a.fxn_list.txt $@b.fxn_list.txt
		@echo "PASS!";

# Test 10 is to test compiling multiple files from relative and absolute paths to current directory
test10:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c ./$@_source/$@a.c ./$@_source/$@b.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@a.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@a.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@a.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@a.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@b.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@b.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@b.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@b.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@a.o $@b.o $@a.dsp_stub.o $@b.dsp_stub.o $@a.gpp_stub.o $@b.gpp_stub.o $@a.fxn_list.txt $@b.fxn_list.txt
		@$(C6RUN_CC) -c $${PWD}/$@_source/$@a.c $${PWD}/$@_source/$@b.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@a.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@a.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@a.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@a.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@b.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@b.dsp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@b.gpp_stub.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@b.fxn_list.txt ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@a.o $@b.o $@a.dsp_stub.o $@b.dsp_stub.o $@a.gpp_stub.o $@b.gpp_stub.o $@a.fxn_list.txt $@b.fxn_list.txt
		@echo "PASS!";

# Begin archiving tests

# Test 11 is to test generating archive from one input object file
test11:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c $@.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@$(C6RUN_AR) $(C6RUN_ARFLAGS) $@_dsp.lib $@.o; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_dsp.lib ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_dsp.lib *.o *.fxn_list.txt
		@echo "PASS!";

# Test 12 is to test generating archive from multiple input object files
test12:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c $@a.c $@b.c $@c.c ; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@$(C6RUN_AR) $(C6RUN_ARFLAGS) $@_dsp.lib $@a.o $@b.o $@c.o; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_dsp.lib ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_dsp.lib *.o *.fxn_list.txt
		@echo "PASS!";

# Test 13 is to test generating archive outside of the current directory from multiple input object files not in the current directory
test13:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c -o ./$@_obj/$@a.o $@a.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@$(C6RUN_CC) -c -o ./$@_obj/$@b.o $@b.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@$(C6RUN_AR) $(C6RUN_ARFLAGS) ./$@_obj/$@_dsp.lib ./$@_obj/$@a.o ./$@_obj/$@b.o; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_obj/$@_dsp.lib ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf ./$@_obj/$@_dsp.lib ./$@_obj/*.o ./$@_obj/*.fxn_list.txt
		@echo "PASS!";


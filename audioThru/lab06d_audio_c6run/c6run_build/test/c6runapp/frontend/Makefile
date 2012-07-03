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
C6RUN_TOOLCHAIN_PREFIX=c6runapp-
ifdef C6RUN_TOOLCHAIN_PATH
C6RUN_CC := $(C6RUN_TOOLCHAIN_PATH)/bin/$(C6RUN_TOOLCHAIN_PREFIX)cc
else
C6RUN_CC := $(C6RUN_TOOLCHAIN_PREFIX)cc
endif


#   ----------------------------------------------------------------------------
#   Makefile targets
#   ----------------------------------------------------------------------------
.PHONY : all test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 clean

all: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13
clean:
		@rm -rf *.o

# Begin compiling tests

test1:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c $@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -o $@_main.o -c $@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -o $@_obj.o -c $@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_obj.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_obj.o
		@echo "PASS!";
    
test2:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c $${PWD}/$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -c -o $@_main.o -c $${PWD}/$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -c -o $@_obj.o -c $${PWD}/$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_obj.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_obj.o
		@echo "PASS!";
    
test3:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c ./$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -c -o $@_main.o ./$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -c -o $@_obj.o ./$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_obj.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_obj.o
		@echo "PASS!";
    
test4:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c -o ./$@_main.o $@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -c -o $${PWD}/$@_main.o $@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@echo "PASS!";

test5:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c -o ./$@_main.o $${PWD}/$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -c -o $${PWD}/$@_main.o $${PWD}/$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -c -o ./$@_main.o ./$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -c -o $${PWD}/$@_main.o ./$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@echo "PASS!";
    
test6:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c -o ./$@_obj/$@_main.o $@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_obj/$@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -c -o $${PWD}/$@_obj/$@_main.o $@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_obj/$@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@echo "PASS!";

test7:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c -o ./$@_source/$@_main.o $${PWD}/$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -c -o $${PWD}/$@_source/$@_main.o $${PWD}/$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -c -o ./$@_source/$@_main.o ./$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -c -o $${PWD}/$@_source/$@_main.o ./$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@echo "PASS!";

test8:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c -o ./$@_source/$@_main.dsp.o $${PWD}/$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@_main.dsp.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -c -o $${PWD}/$@_source/$@_main.dsp.o $${PWD}/$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@_main.dsp.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -c -o ./$@_source/$@_main.dsp.o ./$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e ./$@_source/$@_main.dsp.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@$(C6RUN_CC) -c -o $${PWD}/$@_source/$@_main.dsp.o ./$@_source/$@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $${PWD}/$@_source/$@_main.dsp.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o
		@echo "PASS!";

test9:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c $@_main.c $@_extra.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@_extra.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o $@_extra.o
		@echo "PASS!";
    
test10:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -c ./$@_source/$@_main.c ./$@_source/$@_extra.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@_extra.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o $@_extra.o
		@$(C6RUN_CC) -c $${PWD}/$@_source/$@_main.c $${PWD}/$@_source/$@_extra.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@if [ ! -e $@_extra.o ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.o $@_extra.o
		@echo "PASS!";

# Begin linking tests

test11:
		@echo -n "Running $@..."
		@$(C6RUN_CC) $@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e a.out ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf a.out
		@echo "PASS!";

test12:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -o ./$@_main.exe $@_main.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.exe ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.exe
		@echo "PASS!";

test13:
		@echo -n "Running $@..."
		@$(C6RUN_CC) -o ./$@_main.exe $@_main.c $@_extra.c; \
    retVal=$$?; \
    if [ $$retVal -ne 0 ]; then \
      echo "FAIL with status = $$retVal!"; \
      exit 1; \
    fi
		@if [ ! -e $@_main.exe ]; then \
      echo "FAIL!"; \
      exit 1; \
    fi
		@rm -Rf $@_main.exe
		@echo "PASS!";


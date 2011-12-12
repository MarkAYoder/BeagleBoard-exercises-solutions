#############################################################################
# Makefile                                                                  #
#                                                                           #
# Builds the emqbit benchmark source for ARM and DSP                        #
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


#   ----------------------------------------------------------------------------
#   Name of the ARM GCC cross compiler & archiver
#   ----------------------------------------------------------------------------
ARM_TOOLCHAIN_PREFIX  ?= arm-none-linux-gnueabi-
ifdef ARM_TOOLCHAIN_PATH
ARM_CC := $(ARM_TOOLCHAIN_PATH)/bin/$(ARM_TOOLCHAIN_PREFIX)gcc
ARM_AR := $(ARM_TOOLCHAIN_PATH)/bin/$(ARM_TOOLCHAIN_PREFIX)ar
else
ARM_CC := $(ARM_TOOLCHAIN_PREFIX)gcc
ARM_AR := $(ARM_CROSS_COMPILE)ar
endif

# Get any compiler flags from the environment
ARM_CFLAGS = $(CFLAGS)
ARM_CFLAGS += -std=gnu99 \
-Wdeclaration-after-statement -Wall -Wno-trigraphs \
-fno-strict-aliasing -fno-common -fno-omit-frame-pointer \
-c -O3
ARM_LDFLAGS = $(LDFLAGS)
ARM_LDFLAGS+=-lm -lpthread
ARM_ARFLAGS = rcs

#   ----------------------------------------------------------------------------
#   Name of the DSP C6RUN compiler & archiver
#   TI C6RunLib Frontend (if path variable provided, use it, otherwise assume 
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

C6RUN_CFLAGS = -c -O3
C6RUN_ARFLAGS = rcs --C6Run:replace_malloc


#   ----------------------------------------------------------------------------
#   List of source files
#   ----------------------------------------------------------------------------
EXEC_SRCS := main_cfft.c main_bench.c
EXEC_ARM_OBJS := $(EXEC_SRCS:%.c=gpp/%.o)
EXEC_DSP_OBJS := $(EXEC_SRCS:%.c=dsp/%.o)

LIB_SRCS := cfft.c distance.c
LIB_ARM_OBJS := $(LIB_SRCS:%.c=gpp_lib/%.o)
LIB_DSP_OBJS := $(LIB_SRCS:%.c=dsp_lib/%.o)

#   ----------------------------------------------------------------------------
#   Makefile targets
#   ----------------------------------------------------------------------------
.PHONY : dsp_exec gpp_exec dsp_lib gpp_lib dsp_clean gpp_clean all clean

all: dsp_exec gpp_exec
clean: gpp_clean dsp_clean


gpp_exec: gpp/.created gpp_lib $(EXEC_ARM_OBJS)
	$(ARM_CC) $(ARM_LDFLAGS) $(CINCLUDES) -o bench_arm gpp/main_bench.o bench_arm.lib
	$(ARM_CC) $(ARM_LDFLAGS) $(CINCLUDES) -o cfft_arm gpp/main_cfft.o cfft_arm.lib

gpp_lib: gpp_lib/.created $(LIB_ARM_OBJS)
	$(ARM_AR) $(ARM_ARFLAGS) bench_arm.lib gpp_lib/distance.o
	$(ARM_AR) $(ARM_ARFLAGS) cfft_arm.lib gpp_lib/cfft.o

gpp/%.o : %.c
	$(ARM_CC) $(ARM_CFLAGS) $(CINCLUDES) -o $@ $<
  
gpp_lib/%.o : %.c
	$(ARM_CC) $(ARM_CFLAGS) $(CINCLUDES) -o $@ $<

gpp/.created:
	@mkdir -p gpp
	@touch gpp/.created
  
gpp_lib/.created:
	@mkdir -p gpp_lib
	@touch gpp_lib/.created
  
gpp_clean:
	@rm -Rf bench_arm cfft_arm bench_arm.lib cfft_arm.lib
	@rm -Rf gpp gpp_lib

  
dsp_exec: dsp/.created dsp_lib $(EXEC_DSP_OBJS)
	$(ARM_CC) $(ARM_LDFLAGS) $(CINCLUDES) -o bench_dsp dsp/main_bench.o bench_dsp.lib
	$(ARM_CC) $(ARM_LDFLAGS) $(CINCLUDES) -o cfft_dsp dsp/main_cfft.o cfft_dsp.lib

dsp_lib: dsp_lib/.created $(LIB_DSP_OBJS)
	$(C6RUN_AR) $(C6RUN_ARFLAGS) bench_dsp.lib dsp_lib/distance.o
	$(C6RUN_AR) $(C6RUN_ARFLAGS) cfft_dsp.lib dsp_lib/cfft.o

dsp/%.o : %.c
	$(ARM_CC) $(ARM_CFLAGS) $(CINCLUDES) -o $@ $<
  
dsp_lib/%.o : %.c
	$(C6RUN_CC) $(C6RUN_CFLAGS) $(CINCLUDES) -o $@ $<

dsp/.created:
	@mkdir -p dsp
	@touch dsp/.created

dsp_lib/.created:
	@mkdir -p dsp_lib
	@touch dsp_lib/.created

dsp_clean:
	@rm -Rf bench_dsp cfft_dsp bench_dsp.lib cfft_dsp.lib
	@rm -Rf dsp dsp_lib

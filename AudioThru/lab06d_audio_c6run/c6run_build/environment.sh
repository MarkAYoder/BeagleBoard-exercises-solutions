#!/bin/bash
# /home/user/C6Run_0_97_03_03/environment.sh environment script
: ${CODEGEN_INSTALL_DIR='/opt/toolchains/TI_CGT_C6000_7.2.0'}
export CODEGEN_INSTALL_DIR
: ${C6RUN_TOOLCHAIN_PATH='/opt/toolchains/c6run_binary'}
export C6RUN_TOOLCHAIN_PATH
: ${DSP_CFLAGS='-mv64+'}
export DSP_CFLAGS
: ${ARM_TOOLCHAIN_PATH='/usr'}
export ARM_TOOLCHAIN_PATH
: ${ARM_TOOLCHAIN_PREFIX=''}
export ARM_TOOLCHAIN_PREFIX
: ${CFLAGS='-march=armv7-a -mtune=cortex-a8 -mlittle-endian -mfloat-abi=softfp'}
export CFLAGS
: ${PLATFORM_CFLAGS='-DDSP_REGION_BASE_ADDR=0x86300000 -DDSP_REGION_CMEM_SIZE=0x01000000 -DDSP_REGION_CODE_SIZE=0x00D00000 -DLPM_REQUIRED -DDSP_HAS_MMU'}
export PLATFORM_CFLAGS

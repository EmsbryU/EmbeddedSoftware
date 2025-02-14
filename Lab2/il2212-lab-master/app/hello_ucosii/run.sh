#!/bin/bash

# File: run_hello_world.sh

# This script
#   - creates a board support package for the hardware platform
#   - compiles the application and generates an executable 
#   - downloads the hardware to the board
#   - starts a terminal window
#   - downloads the software and starts the application
# 
# Start the script with sh ./run.sh

CORE_DIR=../../hardware/de2_nios2_mpsoc
CORE_FILE=$CORE_DIR/nios2_mpsoc.sopcinfo
SOF_FILE=$CORE_DIR/de2_nios2_mpsoc.sof
JDI_FILE=$CORE_DIR/de2_nios2_mpsoc.jdi
BSP_PATH=../../bsp/mpsoc_hello_ucosii
SRC_PATH=./src

APP_NAME=hello_ucosii
CPU_NAME=cpu_0

# checking if the core or the run script has been modified, to avoid
# unnecessary recompilation of the BSP.
SOPC_BASE=$CORE_DIR/$(basename $CORE_FILE .sopcinfo)
if [[ `md5sum $SOPC_BASE.*` == `cat $CORE_DIR/.update.md5` ]] && \
       [[ `md5sum $(basename $0)` == `cat .run.md5` ]]; then 
    echo "Will not rebuild the bsp files."
    REMAKE_BSP=false
else
    echo "Will build the BSP files."
    REMAKE_BSP=true
    md5sum $md5sum $SOPC_BASE.* > $CORE_DIR/.update.md5
    md5sum $(basename $0) > .run.md5
fi


# Create BSP-Package
if [ ! -d $BSP_PATH ] || [ "$REMAKE_BSP" = true ]; then
    echo ""
    echo "***********************************************"
    echo "Building BSP: $BSP_PATH"
    echo "***********************************************"
    echo ""
    nios2-bsp ucosii $BSP_PATH $CORE_FILE \
	      --cpu-name $CPU_NAME \
	      --default_sections_mapping sram \
	      --set hal.sys_clk_timer timer_0_A \
	      --set hal.make.bsp_cflags_debug -g \
	      --set hal.make.bsp_cflags_optimization -Os \
	      --set hal.enable_sopc_sysid_check 1 \
	      --set ucosii.os_tmr_en 1
fi

# Create Application

nios2-app-generate-makefile \
    --bsp-dir $BSP_PATH \
    --elf-name $APP_NAME.elf \
    --src-dir $SRC_PATH \
    --set APP_CFLAGS_OPTIMIZATION -Os

echo "" > log.txt
echo "[Compiling code for $CPU_NAME]" > log.txt
echo "" >> log.txt

# Create ELF-file
make 
if [ $? -ne 0 ]; then
  echo "ABORTING: Compile Error"
  exit 1
fi

# Download Hardware to Board

echo ""
echo "***********************************************"
echo "Download hardware to board"
echo "***********************************************"
echo ""

nios2-configure-sof $SOF_FILE

# Start Nios II Terminal

echo ""
echo "Start NiosII terminal ..."

xterm -e "nios2-terminal -i 0" &

echo ""
echo "***********************************************"
echo "Download software to board"
echo "***********************************************"
echo ""

nios2-download -g $APP_NAME.elf --cpu_name $CPU_NAME --jdi $JDI_FILE

echo ""
echo "[Statistics]"
nios2-elf-size $APP_NAME.elf


echo ""
echo "Code compilation errors are logged in 'log.txt'"

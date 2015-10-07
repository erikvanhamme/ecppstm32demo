# Copyright 2015 Erik Van Hamme
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# -----------------------------------------------------------------------------
# Select target board by uncommenting the appropriate line.
# -----------------------------------------------------------------------------
#board := stm32f3discovery
board := stm32f4discovery

# -----------------------------------------------------------------------------
# Common settings.
# -----------------------------------------------------------------------------
project := ecppstm32demo
buildmode ?= release

module_dirs := . ecpp ecppstm32

# -----------------------------------------------------------------------------
# Settings for stm32f3discovery board.
# -----------------------------------------------------------------------------
ifeq ($(board),stm32f3discovery)
module_dirs += stm32f3

chip := stm32f303xc

defines += -Dstm32f3 -DSTM32F303xC

arch := -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16

oocdcfgs := -f "interface/stlink-v2.cfg" -f "target/stm32f3x_stlink.cfg" 
oocdcmds = -c "init" \
	-c "reset halt" \
	-c "flash erase_sector 0 0 4" \
	-c "flash write_bank 0 $(binfile) 0" \
	-c "reset run" \
	-c "shutdown"

endif

# -----------------------------------------------------------------------------
# Settings for stm32f4discovery board.
# -----------------------------------------------------------------------------
ifeq ($(board),stm32f4discovery)
module_dirs += stm32f4

chip := stm32f407xx

defines += -Dstm32f4 -DSTM32F407xx

arch := -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16

oocdcfgs := -f "interface/stlink-v2.cfg" -f "target/stm32f4x_stlink.cfg" 
oocdcmds = -c "init" \
	-c "reset halt" \
	-c "flash erase_sector 0 0 1" \
	-c "flash write_bank 0 $(binfile) 0" \
	-c "reset run" \
	-c "shutdown"

endif

# -----------------------------------------------------------------------------
# Import make rules.
# -----------------------------------------------------------------------------
include buildscripts/stm32project.mk

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

project := ecppstm32demo
buildmode ?= debug

module_dirs := . ecpp stm32f4

chip := stm32f407

oocdcfgs := -f "interface/stlink-v2.cfg" -f "target/stm32f4x_stlink.cfg" 
oocdcmds = -c "init" \
	-c "reset halt" \
	-c "flash erase_sector 0 0 1" \
	-c "flash write_bank 0 $(binfile) 0" \
	-c "reset run" \
	-c "shutdown"

include buildscripts/stm32project.mk

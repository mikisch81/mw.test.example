################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

default : build

# All of the sources participating in the build are defined here

-include config.mk

ifeq ($(GCC_PATH),)
    GCC_PATH := " "
endif

ifeq ($(GCC_PREFIX),)
	GCC_PREFIX := arm-none-eabi-gcc
endif

GCC_PRE := $(GCC_PATH)
GCC_PRE += $(GCC_PREFIX)	

CXX     := $(GCC_PATH)/$(GCC_PREFIX)g++
CC      := $(GCC_PATH)/$(GCC_PREFIX)gcc
AR      := $(GCC_PATH)/$(GCC_PREFIX)ar
RANLIB  := $(GCC_PATH)/$(GCC_PREFIX)ranlib
NM      := $(GCC_PATH)/$(GCC_PREFIX)nm
DBG     := $(GCC_PATH)/$(GCC_PREFIX)gdb

SIZE    := $(GCC_PATH)/$(GCC_PREFIX)size
OBJCOPY := $(GCC_PATH)/$(GCC_PREFIX)objcopy

MW-WRAP := $(MW_TEST_PATH)/mw-wrap
MW-DBG-RUNNER := $(MW_TEST_PATH)/mw-dbg-runner

SEMIHOSTING := --specs=nano.specs --specs=rdimon.specs
MW-INCLUDE := $(MW_TEST_PATH)/include

OPENOCD_CMD := --other "$(OPENOCD) $(OPENOCD_OPT)"
QEMU_CMD := $(QEMU) $(QEMU_OPT) -s --image


-include sources.mk
-include test/subdir.mk
-include sys/src/stm32f4-hal/subdir.mk
-include sys/src/newlib/subdir.mk
-include sys/src/diag/subdir.mk
-include sys/src/cortexm/subdir.mk
-include sys/src/cmsis/subdir.mk
-include src/subdir.mk
-include mw/subdir.mk
-include objects.mk

clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(OBJS)$(BLINKY_OBJS)$(TEST_BLINK_OBJS)$(TEST_STATE_OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(CPP_DEPS) blinky-traced.elf test_state.elf test_blink.elf
	-@echo '

# Tool invocation for runnig with output
blinky.elf : $(BLINKY_OBJS) $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	$(CXX) -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og --coverage -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra --specs=nano.specs -g3 -T mem.ld -T libs.ld -T sections.ld -nostartfiles -Xlinker --gc-sections -L"./bin" -L"../ldscripts" -Wl,-Map,"blinky.map" -o blinky.elf $(BLINKY_OBJS) $(OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	
test_blink.elf : $(TEST_BLINK_OBJS) $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	$(CXX) -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og --coverage -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra --specs=nano.specs -g3 -T mem.ld -T libs.ld -T sections.ld -nostartfiles -Xlinker --gc-sections -L"./bin" -L"../ldscripts" -Wl,-Map,"test_blink.map" -o test_blink.elf $(TEST_BLINK_OBJS) $(OBJS)     
	@echo 'Finished building target: $@'
	@echo ' '
	
test_state.elf : $(TEST_STATE_OBJS) $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	$(CXX) -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og --coverage -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -finstrument-functions -Wall -Wextra --specs=nano.specs -g3 -T mem.ld -T libs.ld -T sections.ld -nostartfiles -Xlinker --gc-sections -L"./bin" -L"../ldscripts" -Wl,-Map,"test_state.map" -o test_state.elf $(TEST_STATE_OBJS) $(OBJS) @wrap.opt
	@echo 'Finished building target: $@'
	@echo ' '	
	
%.hex: %.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	$(OBJCOPY) -O ihex "$<"  "$@"
	$(SIZE) --format=berkeley $@
	@echo 'Finished building: $@'
	@echo ' '	
	
build : blinky.hex test_blink.hex test_state.hex
	
blinky_openocd : blinky.elf
	$(MW-DBG-RUNNER) $(DBG) --exe blinky.elf $(OPENOCD_CMD) --log blinky_openocd.run --remote localhost:3333 --init-script openocd --lib mw-exitcode mw-newlib-syscalls mw-calltrace --debug --mw-calltrace-all --mw-calltrace-timestamp  --mw-calltrace-depth 4 --timeout 60
	echo dummy > blinky_openocd

test_blink_openocd : test_blink.elf
	$(MW-DBG-RUNNER) $(DBG) --exe test_blink.elf $(OPENOCD_CMD) --log test_blink_openocd.run  --remote localhost:3333 --init-script openocd --lib mw-exitcode mw-newlib-syscalls mw-test-backend mw-calltrace --debug --timeout 60
	echo dummy > test_blink_openocd

test_state_openocd : test_state.elf
	$(MW-DBG-RUNNER) $(DBG) --exe test_state.elf $(OPENOCD_CMD) --log test_state_openocd.run --remote localhost:3333 --init-script openocd --lib mw-exitcode mw-newlib-syscalls mw-test-backend mw-calltrace --debug --timeout 60
	echo dummy > test_state_openocd

openocd : blinky_openocd test_blink_openocd test_state_openocd

blinky_qemu : blinky.elf
	$(MW-DBG-RUNNER) $(DBG) --exe blinky.elf --other "$(QEMU_CMD) blinky.elf" --log blinky_qemu.run --remote localhost:1234 --init-script qemu --lib mw-exitcode mw-newlib-syscalls mw-calltrace --debug --mw-calltrace-all --mw-calltrace-timestamp  --mw-calltrace-depth 4 --timeout 60
	echo dummy > blinky_qemu

test_blink_qemu : test_blink.elf
	$(MW-DBG-RUNNER) $(DBG) --exe test_blink.elf --other "$(QEMU_CMD) test_blink.elf" --log test_blink_qemu.run  --remote localhost:1234 --init-script qemu --lib mw-exitcode mw-newlib-syscalls mw-test-backend mw-calltrace --debug --timeout 60
	echo dummy > test_blink_qemu

test_state_qemu : test_state.elf
	$(MW-DBG-RUNNER) $(DBG) --exe test_state.elf --other "$(QEMU_CMD) test_state.elf" --log test_state_qemu.run --remote localhost:1234 --init-script qemu --lib mw-exitcode mw-newlib-syscalls mw-test-backend mw-calltrace --debug --timeout 60
	echo dummy > test_state_qemu

qemu : blinky_qemu test_blink_qemu test_state_qemu

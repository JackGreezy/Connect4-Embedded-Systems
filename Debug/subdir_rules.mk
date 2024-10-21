################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs1240/ccs/tools/compiler/ti-cgt-armllvm_2.1.3.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9" -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9/Debug" -I"/Applications/ti/mspm0_sdk_1_10_01_05/source/third_party/CMSIS/Core/Include" -I"/Applications/ti/mspm0_sdk_1_10_01_05/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Clock.o: /Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/inc/Clock.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs1240/ccs/tools/compiler/ti-cgt-armllvm_2.1.3.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9" -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9/Debug" -I"/Applications/ti/mspm0_sdk_1_10_01_05/source/third_party/CMSIS/Core/Include" -I"/Applications/ti/mspm0_sdk_1_10_01_05/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

LaunchPad.o: /Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/inc/LaunchPad.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs1240/ccs/tools/compiler/ti-cgt-armllvm_2.1.3.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9" -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9/Debug" -I"/Applications/ti/mspm0_sdk_1_10_01_05/source/third_party/CMSIS/Core/Include" -I"/Applications/ti/mspm0_sdk_1_10_01_05/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

SPI.o: /Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/inc/SPI.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs1240/ccs/tools/compiler/ti-cgt-armllvm_2.1.3.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9" -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9/Debug" -I"/Applications/ti/mspm0_sdk_1_10_01_05/source/third_party/CMSIS/Core/Include" -I"/Applications/ti/mspm0_sdk_1_10_01_05/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ST7735.o: /Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/inc/ST7735.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs1240/ccs/tools/compiler/ti-cgt-armllvm_2.1.3.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9" -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9/Debug" -I"/Applications/ti/mspm0_sdk_1_10_01_05/source/third_party/CMSIS/Core/Include" -I"/Applications/ti/mspm0_sdk_1_10_01_05/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TExaS.o: /Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/inc/TExaS.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs1240/ccs/tools/compiler/ti-cgt-armllvm_2.1.3.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9" -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9/Debug" -I"/Applications/ti/mspm0_sdk_1_10_01_05/source/third_party/CMSIS/Core/Include" -I"/Applications/ti/mspm0_sdk_1_10_01_05/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Timer.o: /Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/inc/Timer.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs1240/ccs/tools/compiler/ti-cgt-armllvm_2.1.3.LTS/bin/tiarmclang" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9" -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9/Debug" -I"/Applications/ti/mspm0_sdk_1_10_01_05/source/third_party/CMSIS/Core/Include" -I"/Applications/ti/mspm0_sdk_1_10_01_05/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"/Users/jackgreenberg/Desktop/UT/Fall_2023/ECE319K/MSPM0_ValvanoWare/ECE319K_Lab9/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



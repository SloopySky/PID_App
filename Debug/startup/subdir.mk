################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -I"/home/marek/Ac6/workspace/PID_App_RTOS/HAL_Driver/Inc/Legacy" -I"/home/marek/Ac6/workspace/PID_App_RTOS/CMSIS/device" -I"/home/marek/Ac6/workspace/PID_App_RTOS/CMSIS/core" -I"/home/marek/Ac6/workspace/PID_App_RTOS/HAL_Driver/Inc" -I"/home/marek/Ac6/workspace/PID_App_RTOS/FreeRTOS/Source/include" -I"/home/marek/Ac6/workspace/PID_App_RTOS/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"/home/marek/Ac6/workspace/PID_App_RTOS/FreeRTOS/Source/CMSIS_RTOS" -I"/home/marek/Ac6/workspace/PID_App_RTOS/Source/Inc" -I"/home/marek/Ac6/workspace/PID_App_RTOS/Source/ApplicationLayer" -I"/home/marek/Ac6/workspace/PID_App_RTOS/Source/HardwareLayer" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



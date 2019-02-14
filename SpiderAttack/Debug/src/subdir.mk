################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GPIO.cpp \
../src/GPIOController.cpp \
../src/PWM.cpp \
../src/PosixTimer.cpp \
../src/Pthread.cpp \
../src/SpiderAttack.cpp \
../src/TimerHandler.cpp 

OBJS += \
./src/GPIO.o \
./src/GPIOController.o \
./src/PWM.o \
./src/PosixTimer.o \
./src/Pthread.o \
./src/SpiderAttack.o \
./src/TimerHandler.o 

CPP_DEPS += \
./src/GPIO.d \
./src/GPIOController.d \
./src/PWM.d \
./src/PosixTimer.d \
./src/Pthread.d \
./src/SpiderAttack.d \
./src/TimerHandler.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"C:\SysGCC\raspberry\arm-linux-gnueabihf\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MapUtils/Grid.cpp \
../src/MapUtils/lodepng.cpp \
../src/MapUtils/pngUtil.cpp 

OBJS += \
./src/MapUtils/Grid.o \
./src/MapUtils/lodepng.o \
./src/MapUtils/pngUtil.o 

CPP_DEPS += \
./src/MapUtils/Grid.d \
./src/MapUtils/lodepng.d \
./src/MapUtils/pngUtil.d 


# Each subdirectory must supply rules for building sources it contributes
src/MapUtils/%.o: ../src/MapUtils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



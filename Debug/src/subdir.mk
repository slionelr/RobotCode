################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ConfigurationManager.cpp \
../src/Map.cpp \
../src/Particle.cpp \
../src/Position.cpp \
../src/Robot.cpp \
../src/State.cpp \
../src/main.cpp 

OBJS += \
./src/ConfigurationManager.o \
./src/Map.o \
./src/Particle.o \
./src/Position.o \
./src/Robot.o \
./src/State.o \
./src/main.o 

CPP_DEPS += \
./src/ConfigurationManager.d \
./src/Map.d \
./src/Particle.d \
./src/Position.d \
./src/Robot.d \
./src/State.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


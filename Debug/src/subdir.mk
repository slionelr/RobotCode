################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ConfigurationManager.cpp \
../src/LocalizationManager.cpp \
../src/Map.cpp \
../src/Particle.cpp \
../src/PathPlanner.cpp \
../src/Point.cpp \
../src/Position.cpp \
../src/Robot.cpp \
../src/WaypointsManager.cpp \
../src/main.cpp 

OBJS += \
./src/ConfigurationManager.o \
./src/LocalizationManager.o \
./src/Map.o \
./src/Particle.o \
./src/PathPlanner.o \
./src/Point.o \
./src/Position.o \
./src/Robot.o \
./src/WaypointsManager.o \
./src/main.o 

CPP_DEPS += \
./src/ConfigurationManager.d \
./src/LocalizationManager.d \
./src/Map.d \
./src/Particle.d \
./src/PathPlanner.d \
./src/Point.d \
./src/Position.d \
./src/Robot.d \
./src/WaypointsManager.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



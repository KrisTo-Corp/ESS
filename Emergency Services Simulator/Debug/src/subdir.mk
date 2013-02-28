################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Coordinate.cpp \
../src/Roads.cpp \
../src/Structures.cpp \
../src/Vehicles.cpp \
../src/test_main.cpp 

OBJS += \
./src/Coordinate.o \
./src/Roads.o \
./src/Structures.o \
./src/Vehicles.o \
./src/test_main.o 

CPP_DEPS += \
./src/Coordinate.d \
./src/Roads.d \
./src/Structures.d \
./src/Vehicles.d \
./src/test_main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/tom/Dropbox/Software_Engineering/gtest-1.6.0/include -O0 -g3 -Wall -c -pthread -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



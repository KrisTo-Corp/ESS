################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/City.cpp \
../src/CityObjects.cpp \
../src/Coordinate.cpp \
../src/Matrix.cpp \
../src/OutputObject.cpp \
../src/Roads.cpp \
../src/Simulator.cpp \
../src/Structures.cpp \
../src/Vehicles.cpp \
../src/helpers.cpp \
../src/main.cpp \
../src/tinystr.cpp \
../src/tinyxml.cpp \
../src/tinyxmlerror.cpp \
../src/tinyxmlparser.cpp \
../src/xmlparser.cpp 

OBJS += \
./src/City.o \
./src/CityObjects.o \
./src/Coordinate.o \
./src/Matrix.o \
./src/OutputObject.o \
./src/Roads.o \
./src/Simulator.o \
./src/Structures.o \
./src/Vehicles.o \
./src/helpers.o \
./src/main.o \
./src/tinystr.o \
./src/tinyxml.o \
./src/tinyxmlerror.o \
./src/tinyxmlparser.o \
./src/xmlparser.o 

CPP_DEPS += \
./src/City.d \
./src/CityObjects.d \
./src/Coordinate.d \
./src/Matrix.d \
./src/OutputObject.d \
./src/Roads.d \
./src/Simulator.d \
./src/Structures.d \
./src/Vehicles.d \
./src/helpers.d \
./src/main.d \
./src/tinystr.d \
./src/tinyxml.d \
./src/tinyxmlerror.d \
./src/tinyxmlparser.d \
./src/xmlparser.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



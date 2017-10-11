################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ArrayListUnitTest.cpp \
../Eclipse.cpp \
../EclipseR.cpp 

OBJS += \
./ArrayListUnitTest.o \
./Eclipse.o \
./EclipseR.o 

CPP_DEPS += \
./ArrayListUnitTest.d \
./Eclipse.d \
./EclipseR.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



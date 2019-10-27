################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Affinity.cpp \
../src/PreferredMeetingTimes.cpp \
../src/Project.cpp \
../src/Skills.cpp \
../src/Student.cpp \
../src/US45Task65.cpp 

OBJS += \
./src/Affinity.o \
./src/PreferredMeetingTimes.o \
./src/Project.o \
./src/Skills.o \
./src/Student.o \
./src/US45Task65.o 

CPP_DEPS += \
./src/Affinity.d \
./src/PreferredMeetingTimes.d \
./src/Project.d \
./src/Skills.d \
./src/Student.d \
./src/US45Task65.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



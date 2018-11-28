################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/PDCP_v10.1.0/pdcp_control_primitive.c \
../include/PDCP_v10.1.0/pdcp_netlink.c \
../include/PDCP_v10.1.0/pdcp_primitives.c \
../include/PDCP_v10.1.0/pdcp_security.c \
../include/PDCP_v10.1.0/pdcp_sequence_manager.c \
../include/PDCP_v10.1.0/pdcp_util.c 

OBJS += \
./include/PDCP_v10.1.0/pdcp_control_primitive.o \
./include/PDCP_v10.1.0/pdcp_netlink.o \
./include/PDCP_v10.1.0/pdcp_primitives.o \
./include/PDCP_v10.1.0/pdcp_security.o \
./include/PDCP_v10.1.0/pdcp_sequence_manager.o \
./include/PDCP_v10.1.0/pdcp_util.o 

C_DEPS += \
./include/PDCP_v10.1.0/pdcp_control_primitive.d \
./include/PDCP_v10.1.0/pdcp_netlink.d \
./include/PDCP_v10.1.0/pdcp_primitives.d \
./include/PDCP_v10.1.0/pdcp_security.d \
./include/PDCP_v10.1.0/pdcp_sequence_manager.d \
./include/PDCP_v10.1.0/pdcp_util.d 


# Each subdirectory must supply rules for building sources it contributes
include/PDCP_v10.1.0/%.o: ../include/PDCP_v10.1.0/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/user/alam_development/common_header -I/home/user/alam_development/pdcp_feeder/include -I/home/user/alam_development/pdcp_feeder/include/PDCP_v10.1.0 -I/home/user/alam_development/pdcp_feeder/include/Rel10 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



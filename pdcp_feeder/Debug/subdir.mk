################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../pdcp_feeder_main.c \
../report_write.c \
../rohc_preparation.c \
../test_pdcp.c 

OBJS += \
./pdcp_feeder_main.o \
./report_write.o \
./rohc_preparation.o \
./test_pdcp.o 

C_DEPS += \
./pdcp_feeder_main.d \
./report_write.d \
./rohc_preparation.d \
./test_pdcp.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/user/alam_development/common_header -I/home/user/alam_development/pdcp_feeder/include -I/home/user/alam_development/pdcp_feeder/include/PDCP_v10.1.0 -I/home/user/alam_development/pdcp_feeder/include/Rel10 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



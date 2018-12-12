################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cldMng_msg.c \
../msg_handle.c \
../osa_key_deriver.c \
../pdcp_load_main.c \
../pdcp_report_write.c \
../pdcp_rohc_comp.c \
../pdcp_rohc_decomp.c \
../pdcp_uplink.c \
../test_pdcp.c 

OBJS += \
./cldMng_msg.o \
./msg_handle.o \
./osa_key_deriver.o \
./pdcp_load_main.o \
./pdcp_report_write.o \
./pdcp_rohc_comp.o \
./pdcp_rohc_decomp.o \
./pdcp_uplink.o \
./test_pdcp.o 

C_DEPS += \
./cldMng_msg.d \
./msg_handle.d \
./osa_key_deriver.d \
./pdcp_load_main.d \
./pdcp_report_write.d \
./pdcp_rohc_comp.d \
./pdcp_rohc_decomp.d \
./pdcp_uplink.d \
./test_pdcp.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/user/alam_development/common_header -I/home/user/alam_development/pdcp_load_test/include -I/home/user/alam_development/pdcp_load_test/include/PDCP_v10.1.0 -I/home/user/alam_development/pdcp_load_test/include/Rel10 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



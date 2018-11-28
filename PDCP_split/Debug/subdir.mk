################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../msg_handle.c \
../pdcp_main.c \
../pdcp_rohc_comp.c \
../pdcp_rohc_decomp.c \
../test_pdcp.c 

OBJS += \
./msg_handle.o \
./pdcp_main.o \
./pdcp_rohc_comp.o \
./pdcp_rohc_decomp.o \
./test_pdcp.o 

C_DEPS += \
./msg_handle.d \
./pdcp_main.d \
./pdcp_rohc_comp.d \
./pdcp_rohc_decomp.d \
./test_pdcp.d 


# Each subdirectory must supply rules for building sources it contributes
msg_handle.o: ../msg_handle.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/user/Downloads/rohc-master -I/home/user/alam_development/common_header -I/home/user/alam_development/PDCP_split/include -I/home/user/alam_development/PDCP_split/include/PDCP_v10.1.0 -I/home/user/alam_development/PDCP_split/include/Rel10 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"msg_handle.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/user/alam_development/common_header -I/home/user/alam_development/PDCP_split/include -I/home/user/alam_development/PDCP_split/include/PDCP_v10.1.0 -I/home/user/alam_development/PDCP_split/include/Rel10 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
ussSWLib/source/%.obj: ../ussSWLib/source/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/home/nikhil/ti/ccs1210/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/cl430" -vmspx --data_model=large -O3 --use_hw_mpy=F5 --include_path="/home/nikhil/ti/ccs1210/ccs/ccs_base/msp430/include" --include_path="/home/nikhil/ti/msp/USS_02_40_00_00/USS/examples/FR6047_USSSWLib_template_example" --include_path="/home/nikhil/ti/msp/USS_02_40_00_00/USS/examples/FR6047_USSSWLib_template_example/ussSWLib/USS_HAL" --include_path="/home/nikhil/ti/msp/USS_02_40_00_00/USS/examples/FR6047_USSSWLib_template_example/ussSWLib/source" --include_path="/home/nikhil/ti/msp/USS_02_40_00_00/USS/include" --include_path="/home/nikhil/ti/ccs1210/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/include" --advice:power="none" --advice:hw_config=all --define=__MSP430FR6047__ --define=_MPU_ENABLE --define=USS_PULSE_MODE=0 --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --large_memory_model --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="ussSWLib/source/$(basename $(<F)).d_raw" --obj_directory="ussSWLib/source" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '



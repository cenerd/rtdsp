################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
DSK6713_Support.obj: ../DSK6713_Support.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.12/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="c:/ti/ccsv6/tools/compiler/c6000_7.4.12/include" --include_path="C:/ti/C6xCSL/include" --include_path="C:/ti/CCStudio/c6000/dsk6713/include" --define=CHIP_6713 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="DSK6713_Support.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ISRs.obj: ../ISRs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.12/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="c:/ti/ccsv6/tools/compiler/c6000_7.4.12/include" --include_path="C:/ti/C6xCSL/include" --include_path="C:/ti/CCStudio/c6000/dsk6713/include" --define=CHIP_6713 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="ISRs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.12/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="c:/ti/ccsv6/tools/compiler/c6000_7.4.12/include" --include_path="C:/ti/C6xCSL/include" --include_path="C:/ti/CCStudio/c6000/dsk6713/include" --define=CHIP_6713 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

vectors.obj: ../vectors.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c6000_7.4.12/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="c:/ti/ccsv6/tools/compiler/c6000_7.4.12/include" --include_path="C:/ti/C6xCSL/include" --include_path="C:/ti/CCStudio/c6000/dsk6713/include" --define=CHIP_6713 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="vectors.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '



#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Bustel_V21.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Bustel_V21.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=--mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=SourceCode/main.c SourceCode/battery.c SourceCode/button.c SourceCode/configHW.c SourceCode/duskGuard.c SourceCode/flash.c SourceCode/ledBlink.c SourceCode/ledLight.c SourceCode/motionSensor.c SourceCode/rtc.c SourceCode/solarPanel.c SourceCode/transceiver.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/SourceCode/main.p1 ${OBJECTDIR}/SourceCode/battery.p1 ${OBJECTDIR}/SourceCode/button.p1 ${OBJECTDIR}/SourceCode/configHW.p1 ${OBJECTDIR}/SourceCode/duskGuard.p1 ${OBJECTDIR}/SourceCode/flash.p1 ${OBJECTDIR}/SourceCode/ledBlink.p1 ${OBJECTDIR}/SourceCode/ledLight.p1 ${OBJECTDIR}/SourceCode/motionSensor.p1 ${OBJECTDIR}/SourceCode/rtc.p1 ${OBJECTDIR}/SourceCode/solarPanel.p1 ${OBJECTDIR}/SourceCode/transceiver.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/SourceCode/main.p1.d ${OBJECTDIR}/SourceCode/battery.p1.d ${OBJECTDIR}/SourceCode/button.p1.d ${OBJECTDIR}/SourceCode/configHW.p1.d ${OBJECTDIR}/SourceCode/duskGuard.p1.d ${OBJECTDIR}/SourceCode/flash.p1.d ${OBJECTDIR}/SourceCode/ledBlink.p1.d ${OBJECTDIR}/SourceCode/ledLight.p1.d ${OBJECTDIR}/SourceCode/motionSensor.p1.d ${OBJECTDIR}/SourceCode/rtc.p1.d ${OBJECTDIR}/SourceCode/solarPanel.p1.d ${OBJECTDIR}/SourceCode/transceiver.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/SourceCode/main.p1 ${OBJECTDIR}/SourceCode/battery.p1 ${OBJECTDIR}/SourceCode/button.p1 ${OBJECTDIR}/SourceCode/configHW.p1 ${OBJECTDIR}/SourceCode/duskGuard.p1 ${OBJECTDIR}/SourceCode/flash.p1 ${OBJECTDIR}/SourceCode/ledBlink.p1 ${OBJECTDIR}/SourceCode/ledLight.p1 ${OBJECTDIR}/SourceCode/motionSensor.p1 ${OBJECTDIR}/SourceCode/rtc.p1 ${OBJECTDIR}/SourceCode/solarPanel.p1 ${OBJECTDIR}/SourceCode/transceiver.p1

# Source Files
SOURCEFILES=SourceCode/main.c SourceCode/battery.c SourceCode/button.c SourceCode/configHW.c SourceCode/duskGuard.c SourceCode/flash.c SourceCode/ledBlink.c SourceCode/ledLight.c SourceCode/motionSensor.c SourceCode/rtc.c SourceCode/solarPanel.c SourceCode/transceiver.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Bustel_V21.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16F887
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/SourceCode/main.p1: SourceCode/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/main.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/main.p1  SourceCode/main.c 
	@-${MV} ${OBJECTDIR}/SourceCode/main.d ${OBJECTDIR}/SourceCode/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/battery.p1: SourceCode/battery.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/battery.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/battery.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/battery.p1  SourceCode/battery.c 
	@-${MV} ${OBJECTDIR}/SourceCode/battery.d ${OBJECTDIR}/SourceCode/battery.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/battery.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/button.p1: SourceCode/button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/button.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/button.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/button.p1  SourceCode/button.c 
	@-${MV} ${OBJECTDIR}/SourceCode/button.d ${OBJECTDIR}/SourceCode/button.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/button.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/configHW.p1: SourceCode/configHW.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/configHW.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/configHW.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/configHW.p1  SourceCode/configHW.c 
	@-${MV} ${OBJECTDIR}/SourceCode/configHW.d ${OBJECTDIR}/SourceCode/configHW.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/configHW.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/duskGuard.p1: SourceCode/duskGuard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/duskGuard.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/duskGuard.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/duskGuard.p1  SourceCode/duskGuard.c 
	@-${MV} ${OBJECTDIR}/SourceCode/duskGuard.d ${OBJECTDIR}/SourceCode/duskGuard.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/duskGuard.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/flash.p1: SourceCode/flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/flash.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/flash.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/flash.p1  SourceCode/flash.c 
	@-${MV} ${OBJECTDIR}/SourceCode/flash.d ${OBJECTDIR}/SourceCode/flash.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/flash.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/ledBlink.p1: SourceCode/ledBlink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/ledBlink.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/ledBlink.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/ledBlink.p1  SourceCode/ledBlink.c 
	@-${MV} ${OBJECTDIR}/SourceCode/ledBlink.d ${OBJECTDIR}/SourceCode/ledBlink.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/ledBlink.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/ledLight.p1: SourceCode/ledLight.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/ledLight.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/ledLight.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/ledLight.p1  SourceCode/ledLight.c 
	@-${MV} ${OBJECTDIR}/SourceCode/ledLight.d ${OBJECTDIR}/SourceCode/ledLight.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/ledLight.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/motionSensor.p1: SourceCode/motionSensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/motionSensor.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/motionSensor.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/motionSensor.p1  SourceCode/motionSensor.c 
	@-${MV} ${OBJECTDIR}/SourceCode/motionSensor.d ${OBJECTDIR}/SourceCode/motionSensor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/motionSensor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/rtc.p1: SourceCode/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/rtc.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/rtc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/rtc.p1  SourceCode/rtc.c 
	@-${MV} ${OBJECTDIR}/SourceCode/rtc.d ${OBJECTDIR}/SourceCode/rtc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/rtc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/solarPanel.p1: SourceCode/solarPanel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/solarPanel.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/solarPanel.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/solarPanel.p1  SourceCode/solarPanel.c 
	@-${MV} ${OBJECTDIR}/SourceCode/solarPanel.d ${OBJECTDIR}/SourceCode/solarPanel.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/solarPanel.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/transceiver.p1: SourceCode/transceiver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/transceiver.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/transceiver.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/transceiver.p1  SourceCode/transceiver.c 
	@-${MV} ${OBJECTDIR}/SourceCode/transceiver.d ${OBJECTDIR}/SourceCode/transceiver.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/transceiver.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/SourceCode/main.p1: SourceCode/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/main.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/main.p1  SourceCode/main.c 
	@-${MV} ${OBJECTDIR}/SourceCode/main.d ${OBJECTDIR}/SourceCode/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/battery.p1: SourceCode/battery.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/battery.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/battery.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/battery.p1  SourceCode/battery.c 
	@-${MV} ${OBJECTDIR}/SourceCode/battery.d ${OBJECTDIR}/SourceCode/battery.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/battery.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/button.p1: SourceCode/button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/button.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/button.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/button.p1  SourceCode/button.c 
	@-${MV} ${OBJECTDIR}/SourceCode/button.d ${OBJECTDIR}/SourceCode/button.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/button.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/configHW.p1: SourceCode/configHW.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/configHW.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/configHW.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/configHW.p1  SourceCode/configHW.c 
	@-${MV} ${OBJECTDIR}/SourceCode/configHW.d ${OBJECTDIR}/SourceCode/configHW.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/configHW.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/duskGuard.p1: SourceCode/duskGuard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/duskGuard.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/duskGuard.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/duskGuard.p1  SourceCode/duskGuard.c 
	@-${MV} ${OBJECTDIR}/SourceCode/duskGuard.d ${OBJECTDIR}/SourceCode/duskGuard.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/duskGuard.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/flash.p1: SourceCode/flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/flash.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/flash.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/flash.p1  SourceCode/flash.c 
	@-${MV} ${OBJECTDIR}/SourceCode/flash.d ${OBJECTDIR}/SourceCode/flash.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/flash.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/ledBlink.p1: SourceCode/ledBlink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/ledBlink.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/ledBlink.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/ledBlink.p1  SourceCode/ledBlink.c 
	@-${MV} ${OBJECTDIR}/SourceCode/ledBlink.d ${OBJECTDIR}/SourceCode/ledBlink.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/ledBlink.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/ledLight.p1: SourceCode/ledLight.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/ledLight.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/ledLight.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/ledLight.p1  SourceCode/ledLight.c 
	@-${MV} ${OBJECTDIR}/SourceCode/ledLight.d ${OBJECTDIR}/SourceCode/ledLight.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/ledLight.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/motionSensor.p1: SourceCode/motionSensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/motionSensor.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/motionSensor.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/motionSensor.p1  SourceCode/motionSensor.c 
	@-${MV} ${OBJECTDIR}/SourceCode/motionSensor.d ${OBJECTDIR}/SourceCode/motionSensor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/motionSensor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/rtc.p1: SourceCode/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/rtc.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/rtc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/rtc.p1  SourceCode/rtc.c 
	@-${MV} ${OBJECTDIR}/SourceCode/rtc.d ${OBJECTDIR}/SourceCode/rtc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/rtc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/solarPanel.p1: SourceCode/solarPanel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/solarPanel.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/solarPanel.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/solarPanel.p1  SourceCode/solarPanel.c 
	@-${MV} ${OBJECTDIR}/SourceCode/solarPanel.d ${OBJECTDIR}/SourceCode/solarPanel.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/solarPanel.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SourceCode/transceiver.p1: SourceCode/transceiver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/SourceCode" 
	@${RM} ${OBJECTDIR}/SourceCode/transceiver.p1.d 
	@${RM} ${OBJECTDIR}/SourceCode/transceiver.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SourceCode/transceiver.p1  SourceCode/transceiver.c 
	@-${MV} ${OBJECTDIR}/SourceCode/transceiver.d ${OBJECTDIR}/SourceCode/transceiver.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SourceCode/transceiver.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Bustel_V21.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/Bustel_V21.0.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     --rom=default,-1f00-1ffe --ram=default,-0-0,-70-70,-80-80,-f0-f0,-100-100,-170-170,-180-180,-1e5-1f0  $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/Bustel_V21.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/Bustel_V21.0.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Bustel_V21.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/Bustel_V21.0.X.${IMAGE_TYPE}.map  --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/Bustel_V21.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif

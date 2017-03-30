##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=FlockingDemo
ConfigurationName      :=Debug
WorkspacePath          :=/home/dante/codelite/test
ProjectPath            :=/home/dante/codelite/test/FlockingDemo
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Dante
Date                   :=30/03/17
CodeLitePath           :=/home/dante/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="FlockingDemo.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -O0 -lSDL2 -lSDL2_image
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). $(LibraryPathSwitch)Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -Wall -std=c++11 $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/objects_prop.cpp$(ObjectSuffix) $(IntermediateDirectory)/objects_object.cpp$(ObjectSuffix) $(IntermediateDirectory)/objects_actor.cpp$(ObjectSuffix) $(IntermediateDirectory)/objects_agent.cpp$(ObjectSuffix) $(IntermediateDirectory)/objects_flock.cpp$(ObjectSuffix) $(IntermediateDirectory)/utilities_timer.cpp$(ObjectSuffix) $(IntermediateDirectory)/utilities_vector2.cpp$(ObjectSuffix) $(IntermediateDirectory)/utilities_texture_flyweight.cpp$(ObjectSuffix) $(IntermediateDirectory)/window_window.cpp$(ObjectSuffix) \
	



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/dante/codelite/test/FlockingDemo/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix)main.cpp

$(IntermediateDirectory)/objects_prop.cpp$(ObjectSuffix): objects/prop.cpp $(IntermediateDirectory)/objects_prop.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/dante/codelite/test/FlockingDemo/objects/prop.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/objects_prop.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/objects_prop.cpp$(DependSuffix): objects/prop.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/objects_prop.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/objects_prop.cpp$(DependSuffix) -MM objects/prop.cpp

$(IntermediateDirectory)/objects_prop.cpp$(PreprocessSuffix): objects/prop.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/objects_prop.cpp$(PreprocessSuffix)objects/prop.cpp

$(IntermediateDirectory)/objects_object.cpp$(ObjectSuffix): objects/object.cpp $(IntermediateDirectory)/objects_object.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/dante/codelite/test/FlockingDemo/objects/object.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/objects_object.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/objects_object.cpp$(DependSuffix): objects/object.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/objects_object.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/objects_object.cpp$(DependSuffix) -MM objects/object.cpp

$(IntermediateDirectory)/objects_object.cpp$(PreprocessSuffix): objects/object.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/objects_object.cpp$(PreprocessSuffix)objects/object.cpp

$(IntermediateDirectory)/objects_actor.cpp$(ObjectSuffix): objects/actor.cpp $(IntermediateDirectory)/objects_actor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/dante/codelite/test/FlockingDemo/objects/actor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/objects_actor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/objects_actor.cpp$(DependSuffix): objects/actor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/objects_actor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/objects_actor.cpp$(DependSuffix) -MM objects/actor.cpp

$(IntermediateDirectory)/objects_actor.cpp$(PreprocessSuffix): objects/actor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/objects_actor.cpp$(PreprocessSuffix)objects/actor.cpp

$(IntermediateDirectory)/objects_agent.cpp$(ObjectSuffix): objects/agent.cpp $(IntermediateDirectory)/objects_agent.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/dante/codelite/test/FlockingDemo/objects/agent.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/objects_agent.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/objects_agent.cpp$(DependSuffix): objects/agent.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/objects_agent.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/objects_agent.cpp$(DependSuffix) -MM objects/agent.cpp

$(IntermediateDirectory)/objects_agent.cpp$(PreprocessSuffix): objects/agent.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/objects_agent.cpp$(PreprocessSuffix)objects/agent.cpp

$(IntermediateDirectory)/objects_flock.cpp$(ObjectSuffix): objects/flock.cpp $(IntermediateDirectory)/objects_flock.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/dante/codelite/test/FlockingDemo/objects/flock.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/objects_flock.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/objects_flock.cpp$(DependSuffix): objects/flock.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/objects_flock.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/objects_flock.cpp$(DependSuffix) -MM objects/flock.cpp

$(IntermediateDirectory)/objects_flock.cpp$(PreprocessSuffix): objects/flock.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/objects_flock.cpp$(PreprocessSuffix)objects/flock.cpp

$(IntermediateDirectory)/utilities_timer.cpp$(ObjectSuffix): utilities/timer.cpp $(IntermediateDirectory)/utilities_timer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/dante/codelite/test/FlockingDemo/utilities/timer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/utilities_timer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utilities_timer.cpp$(DependSuffix): utilities/timer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/utilities_timer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/utilities_timer.cpp$(DependSuffix) -MM utilities/timer.cpp

$(IntermediateDirectory)/utilities_timer.cpp$(PreprocessSuffix): utilities/timer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/utilities_timer.cpp$(PreprocessSuffix)utilities/timer.cpp

$(IntermediateDirectory)/utilities_vector2.cpp$(ObjectSuffix): utilities/vector2.cpp $(IntermediateDirectory)/utilities_vector2.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/dante/codelite/test/FlockingDemo/utilities/vector2.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/utilities_vector2.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utilities_vector2.cpp$(DependSuffix): utilities/vector2.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/utilities_vector2.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/utilities_vector2.cpp$(DependSuffix) -MM utilities/vector2.cpp

$(IntermediateDirectory)/utilities_vector2.cpp$(PreprocessSuffix): utilities/vector2.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/utilities_vector2.cpp$(PreprocessSuffix)utilities/vector2.cpp

$(IntermediateDirectory)/utilities_texture_flyweight.cpp$(ObjectSuffix): utilities/texture_flyweight.cpp $(IntermediateDirectory)/utilities_texture_flyweight.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/dante/codelite/test/FlockingDemo/utilities/texture_flyweight.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/utilities_texture_flyweight.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utilities_texture_flyweight.cpp$(DependSuffix): utilities/texture_flyweight.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/utilities_texture_flyweight.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/utilities_texture_flyweight.cpp$(DependSuffix) -MM utilities/texture_flyweight.cpp

$(IntermediateDirectory)/utilities_texture_flyweight.cpp$(PreprocessSuffix): utilities/texture_flyweight.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/utilities_texture_flyweight.cpp$(PreprocessSuffix)utilities/texture_flyweight.cpp

$(IntermediateDirectory)/window_window.cpp$(ObjectSuffix): window/window.cpp $(IntermediateDirectory)/window_window.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/dante/codelite/test/FlockingDemo/window/window.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/window_window.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/window_window.cpp$(DependSuffix): window/window.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/window_window.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/window_window.cpp$(DependSuffix) -MM window/window.cpp

$(IntermediateDirectory)/window_window.cpp$(PreprocessSuffix): window/window.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/window_window.cpp$(PreprocessSuffix)window/window.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/



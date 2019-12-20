SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

INCLUDE_DIR = 

CXXFLAGS := $(CXXFLAGS) $(WARNINGFLAGS)

TARGET = utils.so

$(TARGET): $(OBJ)
	@$(CXX) $(CXXFLAGS) -o $@ -shared $(OBJ)
	@echo "    	generated	$(TARGET) File"
	@mv $(TARGET) $(OBJ_DIR)/
	@echo "    	$(TARGET) move to $(OBJ_DIR)"

FileUtils.o: fileutils.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

## Quand vous rajoutez un fichier, suivre le même format que ci dessous pour chaque fichier :
##Cible: dépendances
##	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
##	@echo "    	CXX        $@"

clean:
	@$(RM) -f $(OBJ)
	@$(RM) -f *.expand
	@echo "    Remove Objects:   $(OBJ)"

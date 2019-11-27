SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

INCLUDE_DIR =  

TARGET = graphics.so

$(TARGET): $(OBJ)
	@$(CXX) $(CXXFLAGS) -o $@ -shared $(OBJ)
	@echo "    	generated	$(TARGET) File"
	@mv $(TARGET) $(OBJ_DIR)/
	@echo "    	$(TARGET) move to $(OBJ_DIR)"

Shader.o: shader.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

Program.o: program.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

VAOHandler.o: vaohandler.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

vbohandler.o: vbohandler.cpp
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

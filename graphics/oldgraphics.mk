SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

INCLUDE_DIR =  

CXXFLAGS := $(CXXFLAGS) $(WARNINGFLAGS) -Wno-old-style-cast

TARGET = graphics.so

$(TARGET): $(OBJ)
	@$(CXX) $(CXXFLAGS) -o $@ -shared $(OBJ)
	@echo "    	generated	$(TARGET) File"
	@mv $(TARGET) $(OBJ_DIR)/
	@echo "    	$(TARGET) move to $(OBJ_DIR)"

Camera.o: camera.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX       $@"

EBOHandler.o: ebohandler.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

GLUtils.o: glutils.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

Mesh.o: mesh.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

OpenGLObjectHandler.o: openglobjecthandler.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

Program.o: programhandler.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

Shader.o: shaderhandler.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

TextureHandler.o: texturehandler.cpp
	@$(CXX) $(CXXFLAGS) -Wno-sign-conversion $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

VAOHandler.o: vaohandler.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

VBOhandler.o: vbohandler.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

Vertex.o: vertex.cpp
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

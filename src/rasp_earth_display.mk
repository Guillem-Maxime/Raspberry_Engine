SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

INCLUDE_DIR =

RASP_EARTH_DISPLAY_LIB = $(OBJ_DIR)/*

$(EXEC):$(OBJ) $(RASP_EARTH_DISPLAY_LIB)
	$(CXX) -o $(EXEC) $(OBJ) $(RASP_EARTH_DISPLAY_LIB) $(LIBS)
	@echo "    Generate Program $(notdir $(PROG)) from $^"
	@mv -v $(EXEC) $(MAKE_DIR)

main.o:	main.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $<
	@echo "   	CXX      $@"

.PHONY: clean
clean:
	@$(RM) -f $(OBJ)
	@echo "    Remove Objects:   $(OBJ)"
	@$(RM) -f $(MAKE_DIR)/$(EXEC)
	@echo "    Remove Objects:   $(EXEC)"
	@$(RM) -f $(RASP_EARTH_DISPLAY_LIB)
	@echo "    Remove Objects:   $(RASP_EARTH_DISPLAY_LIB)"
	

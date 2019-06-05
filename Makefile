CLANG = clang++
CXX_FLAGS = -c -Wall -Wextra -Werror -std=c++11
#-O3 -flto=thin -Ofast -march=native -mtune=native
HOCKEY_FLAGS = -F frameworks/ -framework SDL2 -framework SDL2_mixer -framework SDL2_ttf

SOURCES = source/main.cpp\
          source/Game.cpp\
          source/Player.cpp\
          source/Bot.cpp\
          source/exceptions.cpp\
          source/Puck.cpp\
          source/Object.cpp\
          source/math_functions.cpp\
          source/Music.cpp

HEADERS = includes/Game.hpp\
          includes/Player.hpp\
          includes/Bot.hpp\
          includes/exceptions.hpp\
          includes/headers.hpp\
          includes/Puck.hpp\
          includes/Object.hpp\
          includes/math_functions.hpp\
          includes/Music.hpp

INCLUDES_SDL = -I frameworks/SDL2.framework/Versions/A/Headers/ \
				-I frameworks/SDL2_mixer.framework/Versions/A/Headers/\
				-I frameworks/SDL2_image.framework/Versions/A/Headers/\
				-I frameworks/SDL2_ttf.framework/Versions/A/Headers/

INCLUDES = -I includes/

OBJ = $(addprefix $(OBJDIR), $(notdir $(SOURCES:.cpp=.o)))
OBJDIR = obj/

NAME = AirHockey

C_RED = \033[31m
C_GREEN = \033[32m
C_MAGENTA = \033[35m
C_NONE = \033[0m

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(HEADERS) $(SOURCES)
	@$(CLANG) $(OBJ) $(HOCKEY_FLAGS) -o $@
	@printf "$(C_MAGENTA)AirHockey:   $(C_NONE) %-50s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJDIR)%.o: source/%.cpp  $(HEADERS)
	@$(CLANG) $(CXX_FLAGS) $(INCLUDES_SDL) -c $< -o  $@ $(INCLUDES)

$(OBJDIR): $(HEADERS)
	@mkdir -p $(OBJDIR)

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJDIR)
	@printf "$(C_MAGENTA)AirHockey:   $(C_NONE) %-50s$(C_RED)[done]$(C_NONE)\n" $@

fclean: clean
	@echo $(OBJ)
	@rm -f $(NAME)
	@printf "$(C_MAGENTA)AirHockey:   $(C_NONE) %-50s$(C_RED)[done]$(C_NONE)\n" $@

re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcha <mcha@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/26 13:55:55 by mcha              #+#    #+#              #
#    Updated: 2022/08/01 15:32:38 by mcha             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX					= c++
ifdef DEBUG
	CXXFLAGS		= -std=c++98 -g
else 
	CXXFLAGS		= -std=c++98 -Wall -Wextra -Werror
endif
NAME				= container

RM					= rm -rf

# Directory
INC_DIR				=	./include/
SRC_DIR				=	./src/

# Source
SRC					= $(addprefix $(SRC_DIR), \
											main.cpp \
											)

OBJ					= $(SRC:%.cpp=%.o)

%.o 				: %.cpp
					@echo "[+] Compile $< using $(CXXFLAGS) -I$(INC_DIR)"
					@$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME)				: $(OBJ)
					@$(CXX) $(CXXFLAGS) -o $@ $(OBJ) -I$(INC_DIR)
					@echo "[+] Create $(NAME) with linking"

all					: $(NAME)

clean				: 
					@$(RM) $(OBJ)
					@echo "[-] Delete object files"

fclean				: clean
					@echo "[-] Delete run files"
					@$(RM) $(NAME)

re					:
					make fclean
					make all

debug				:
					@make DEBUG=1
					@echo "[-] DEBUG PROCESS"

.PHONY 				: all clean fclean re debug
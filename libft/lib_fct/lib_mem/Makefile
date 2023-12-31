# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estelamb <estelamb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 12:59:41 by eslamber          #+#    #+#              #
#    Updated: 2023/12/21 09:55:47 by estelamb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#
### Definitions of variables
#

# Definitions of compilation options
FLAGS := -Wall -Werror -Wextra -fsanitize=address -fno-omit-frame-pointer
CC := gcc

# Definition of variable librairie
LIB := lib_mem.a

LIB_MEM_SRC := src/
LIB_MEM_OBJ := obj/

# Definition of variables needed to librairie's compilation

MEM_LIB := ft_bzero.c \
		   ft_calloc.c \
		   ft_memchr.c \
		   ft_memcmp.c \
		   ft_memcpy.c \
		   ft_memmove.c \
		   ft_memset.c \
		   free_db_array.c \
		   free_db_void_array.c
MEM_LIB_H := $(LIB_MEM)lib_mem.h
MEM_OBJ_LIB := $(MEM_LIB:%.c=$(LIB_MEM_OBJ)%.o)

# Definitions of differents printed colors
LIGHTBLUE := '\e[0;32m'
RED := '\e[0;31m'
NEUTRAL := '\e[0m'
#
### Compilations rules
#

all: $(LIB)

$(LIB): $(MEM_OBJ_LIB)
	ar rc $@ $^
	ranlib $@

$(MEM_OBJ_LIB): $(LIB_MEM_OBJ)%.o: $(LIB_MEM_SRC)%.c $(MEM_LIB_H)
	$(CC) $(FLAGS) -c $< -o $@

#
### Debug rules
#

debug:
	make -C ./ "FLAGS+= -Wall -Werror -Wextra -fsanitize=address \
	-fno-omit-frame-pointer" print

valgrind_deb:
	make -C ./ "FLAGS+= -Wall -Werror -Wextra -g" print

#
### Directories rules
#

make_dir:
	@echo -e $(LIGHTBLUE)make librairies directories$(NEUTRAL)
	mkdir -p $(LIB_MEM_OBJ)
	@echo -e $(LIGHTBLUE)done$(NEUTRAL)
	@echo

#
### Prints rules
#

# Compilation of librairie with print options
print: print_ob $(MEM_OBJ_LIB) print_lb $(LIB) print_le

print_ob:
	@echo -e $(LIGHTBLUE)compilation lib objects files$(NEUTRAL)

print_oe:
	@echo -e $(LIGHTBLUE)compilation lib objetcs files done$(NEUTRAL)
	@echo

print_lb: print_oe
	@echo -e $(LIGHTBLUE)compilation librairie$(NEUTRAL)

print_le:
	@echo -e $(LIGHTBLUE)compilation librairie done$(NEUTRAL)
	@echo

#
### Cleanup rules
#

# Classiques cleaning rules
clean:
	@echo -e $(LIGHTBLUE)remove all $(RED)objects files$(NEUTRAL)
	@rm -rfv $(MEM_OBJ_LIB)
	@echo

cleanlib: 
	@echo -e $(LIGHTBLUE)remove $(RED)lib file$(NEUTRAL)
	@rm -rfv $(LIB)
	@echo

cleandir: 
	@echo -e $(LIGHTBLUE)remove all $(RED)directories$(NEUTRAL)
	@rm -rfv $(LIB_MEM_OBJ)
	@echo

clean_git:
	@echo -e $(LIGHTBLUE)remove all $(RED)gitignore files$(NEUTRAL)
	@rm -rfv ./obj/.gitignore
	@echo

gitignor: 
	@echo -e $(LIGHTBLUE)reediting of differents $(RED)gitignores$(NEUTRAL)
	touch ./obj/.gitignore
	@echo "*" > ./obj/.gitignore
	@echo !.gitignore >> ./obj/.gitignore
	@echo

# Full cleaning rules
fclean: clean cleanlib clean_git cleandir make_dir gitignor

# Remake rules
re: fclean all

re_deb: fclean debug

re_val: fclean valgrind_deb

# Remakes rules with print options
reprint: fclean print

.PHONY: all make_dir print print_ob print_oe print_lb print_le clean cleandir
.PHONY: clean_git gitignor flcean re reprint cleanlib debug valgrind_deb re_deb
.PHONY: re_val

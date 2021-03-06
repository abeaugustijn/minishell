# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: aaugusti <aaugusti@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/23 13:07:19 by aaugusti      #+#    #+#                  #
#    Updated: 2020/11/13 15:34:16 by aaugusti      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

all: $(NAME)

# All source of the application
SRCS			=	\
					builtin/builtin_cd\
					builtin/builtin_echo\
					builtin/builtin_env\
					builtin/builtin_exit\
					builtin/builtin_export\
					builtin/builtin_pwd\
					builtin/builtin_unset\
					env\
					env_utils\
					error\
					free\
					get_cmd\
					init\
					parser/parser\
					parser/parser_utils\
					parser/cases/parser_case_dquote\
					parser/cases/parser_case_end\
					parser/cases/parser_case_env\
					parser/cases/parser_case_escape\
					parser/cases/parser_case_input\
					parser/cases/parser_case_pipe\
					parser/cases/parser_case_rest\
					parser/cases/parser_case_semicolon\
					parser/cases/parser_case_squote\
					parser/cases/parser_case_whitespace\
					parser/cases/parser_case_write\
					parser/parser_check\
					parser/parser_functions\
					path\
					perror\
					perror_utils\
					prompt\
					run_cmd/find_builtin\
					run_cmd/free_cmds\
					run_cmd/handle_redirs\
					run_cmd/run_cmd\
					run_cmd/run_cmd_utils\
					run_cmd/start_proc\
					signal\
					utils/free_str_arr\
					utils/get_cwd\
					utils/replace_env\
					utils/zalloc\

# Sources which are just needed for the bonus part
BONUS_SRCS		=	\

# These are files that need to be recompiled when the bonus is made
BONUS_RECOMP	=	\

OFILES			=	$(SRCS:%=src/%.o)
BONUS_OFILES	=	$(BONUS_SRCS:%=src/%.o)
BONUS_RECOMP_O	=	$(BONUS_RECOMP:%=src/%.o)


# Paths to the headeres which are needed
INCLUDES		=	\
					-I include\
					-I lib/libft\
					-I lib/libftprintf\
					-I lib/libgnl\
					-I lib/liblist\
					-I lib/libstring\
					-I lib/libvla\

# The location of al libraries
LIB_SRCS		=	\
					lib/libft/libft.a\
					lib/libftprintf/libftprintf.a\
					lib/libgnl/libgnl.a\
					lib/liblist/liblist.a\
					lib/libstring/libstring.a\
					lib/libvla/libvla.a\

FLAGS			=	-Wall -Werror -Wextra -DNOLIST

# Ability to compile with maximum optimization
ifeq ($(DEBUG),1)
FLAGS			+= -g -Og -fno-stack-protector
ifeq ($(ASAN),1)
FLAGS			+= -fsanitize=address
endif #noasan
else
FLAGS			+= -Ofast
endif #debug

# OS detection for libs and headers
UNAME_S			:=	$(shell uname -s)

ifeq ($(UNAME_S),Linux)
FLAGS			+=	-DLINUX
endif #Linux

ifeq ($(UNAME_S),Darwin)
endif #Darwin


TARGETS			=	$(OFILES) $(LIB_SRCS)

ifeq ($(BONUS),1)
TARGETS			+=	$(BONUS_OFILES)
FLAGS			+=	-DBONUS
endif #Bonus

# This means that the build before this one was indeed bonus, so we need to
# recompile the bonus-specific files and remove the bonus file.
ifeq ($(shell ls bonus 2> /dev/null),bonus)
TARGETS_EXTRA	= clean_bonus
endif #Last was bonus

# Another case in which we need to recompile the bonus files. This is true when
# we build the bonus, but the previous build was not bonus.
ifeq ($(BONUS),1)
ifneq ($(shell ls bonus 2> /dev/null),bonus)
TARGETS_EXTRA	= clean_bonus
endif #Last was bonus
endif #Bonus 

clean_bonus:
	rm -f $(BONUS_RECOMP_O)
	rm -f bonus


$(NAME): $(TARGETS_EXTRA) $(TARGETS) src/main.o
	$(CC) $(TARGETS) src/main.o $(FLAGS) -o $(NAME)

# Rule for compiling the bonus part of the program. We just remove the existing
# executable and recompile the normal program with the BONUS env. variable set
# to 1.
bonus:
	rm -f $(NAME)
	@BONUS=1 make $(NAME)
	@touch bonus

# Generic rule for compiling any C-file into an object file
%.o: %.c
	$(CC) -o $@ -c $< $(FLAGS) $(INCLUDES)

# Generic rule for compiling libraries
%.a:
	make -C $(@D)

lib/libft/libft.a:
	make bonus -C $(@D)

# Rules for cleaning files
clean:
	make clean -C lib/libft
	make clean -C lib/libftprintf
	make clean -C lib/libgnl
	make clean -C lib/liblist
	make clean -C lib/libstring
	make clean -C lib/libvla
	rm -f $(OFILES) $(BONUS_OFILES) src/main.o

fclean: clean
	make fclean -C lib/libft
	make fclean -C lib/libftprintf
	make fclean -C lib/libgnl
	make fclean -C lib/liblist
	make fclean -C lib/libstring
	make fclean -C lib/libvla
	rm -f $(NAME)
	rm -f bonus

re: fclean all

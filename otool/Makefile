# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/07 16:55:33 by mbarbari          #+#    #+#              #
#    Updated: 2017/04/10 18:42:49 by mbarbari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC ?= clang
CX ?= clang++

NAME = ft_otool

CFLAGS += -g -Wall -Wextra -Werror

SOURCES_FILES = ./sources
HEADERS_FILES = ./includes
OBJECTS_FILES = ./objects

LIBSDIR = ../libs/libft
LIBS = -L$(LIBSDIR) -lft
LIBSNAME = libft.a
LIBFT = $(LIBSDIR)/$(LIBSNAME)

INC = -I./includes -I$(LIBSDIR)/include

CLI_SRCS = 	$(SOURCES_FILES)/main.c 		\
			$(SOURCES_FILES)/error.c		\
			$(SOURCES_FILES)/error_file.c	\
			$(SOURCES_FILES)/error_header.c	\
			$(SOURCES_FILES)/handle_open.c	\
			$(SOURCES_FILES)/handle_parse.c	\
			$(SOURCES_FILES)/handle_sym.c	\
			$(SOURCES_FILES)/main.c	\
			$(SOURCES_FILES)/print.c	\
			$(SOURCES_FILES)/singleton.c	\


CLI_OBJS = $(patsubst $(SOURCES_FILES)/%.c,$(OBJECTS_FILES)/%.o,$(CLI_SRCS))

SRC_INCLUDE = $(HEADERS_FILES)/otool.h \

RM ?= rm -f
MKDIR ?= mkdir
CD ?= cd

all: $(NAME)

print-% : ; $(info $* is $(flavor $*) variable set to [$($*)]) @true

$(NAME): $(LIBFT) $(CLI_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(INC) $(LIBS)

$(OBJECTS_FILES)/%.o: $(SOURCES_FILES)/%.c $(SRC_INCLUDE)
	$(MKDIR) -p $(dir $@)
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBSDIR)

clean:
	$(RM) $(CLI_OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(CLI_OBJS)
	$(MAKE) -C $(LIBSDIR) fclean

re: fclean all

.PHONY: clean fclean re all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 15:00:50 by woorikim          #+#    #+#              #
#    Updated: 2024/01/10 17:15:22 by woorikim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
CC = cc
SRCS = ft_isalpha.c ft_memcmp.c  ft_strdup.c  ft_strnstr.c \
ft_atoi.c    ft_isascii.c ft_memcpy.c  ft_strlcat.c ft_strrchr.c \
ft_bzero.c   ft_isdigit.c ft_memmove.c ft_strlcpy.c ft_tolower.c \
ft_calloc.c  ft_isprint.c ft_memset.c  ft_strlen.c  ft_toupper.c \
ft_isalnum.c ft_memchr.c  ft_strchr.c  ft_strncmp.c ft_substr.c \
ft_strjoin.c ft_strtrim.c  ft_split.c  ft_itoa.c  ft_strmapi.c \
ft_striteri.c  ft_putchar_fd.c ft_putstr_fd.c  ft_putendl_fd.c \
ft_putnbr_fd.c

SRCS_B = ft_lstnew.c  ft_lstadd_front.c  ft_lstsize.c  ft_lstlast.c \
ft_lstadd_back.c  ft_lstdelone.c  ft_lstclear.c  ft_lstiter.c  ft_lstmap.c

OBJECTS = $(SRCS:.c=.o)
OBJECTS_B = $(SRCS_B:.c=.o)

ifdef BONUS
    OBJ_FILES = $(OBJECTS) $(OBJECTS_B)
else
    OBJ_FILES = $(OBJECTS)
endif

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	ar cr $@ $(OBJ_FILES)

.c.o: $(OBJ_FILES)
	$(CC) $(CFLAGS) -c -o $@ $< -I .

bonus :
	make BONUS=1 all

clean :
	rm -f $(OBJECTS)
	rm -f $(OBJECTS_B)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean re
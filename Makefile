NAME = minitalk
NAME_CLIENT	= client
NAME_SERVER = server
SRCS_CLIENT	= client.c sent_char.c
SRCS_SERVER = server.c print_pid.c
HEADER	= ./includes
OBJS_CLIENT	= $(addprefix $(OBJ_DIR)/, $(SRCS_CLIENT:.c=.o))
OBJS_SERVER	= $(addprefix $(OBJ_DIR)/, $(SRCS_SERVER:.c=.o))
CC		= gcc
CFLAG	= -Wall -Wextra -Werror

OBJ_DIR	:= ./objs
VPATH	:=	srcs
DEPS	:= $(OBJS_CLIENT:.o=.d) $(OBJS_SERVER:.o=.d)
LIBFT_DIR := ./libft
LIBFT := libft.a



$(NAME): $(LIBFT) $(OBJ_DIR) $(NAME_CLIENT) $(NAME_SERVER)

$(LIBFT): 
	make bonus -C $(LIBFT_DIR)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAG) $(OBJS_CLIENT) $(LIBFT_DIR)/$(LIBFT) -o $(NAME_CLIENT) -I $(HEADER)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAG) $(OBJS_SERVER) $(LIBFT_DIR)/$(LIBFT) -o $(NAME_SERVER) -I $(HEADER)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@ -I $(HEADER)

$(OBJ_DIR):
	mkdir -p $@
	
all: $(NAME)

clean:
	make clean -C $(LIBFT_DIR) 
	rm -rf $(OBJ_DIR)

fclean:		clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)/$(LIBFT)
	rm -f $(NAME_CLIENT)
	rm -f $(NAME_SERVER)

re:			fclean all

-include $(DEPS)

.PHONY:     all clean fclean re $(NAME)

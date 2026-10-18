NAME = RPN
CXX = c++
CPPFLAGS = -Werror -Wextra -Wall -std=c++98
SRCS = main.cpp RPN.cpp
OBJS = $(SRCS:%.cpp=%.o)

%.o:%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CPPFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
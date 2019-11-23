SRC1		=	$(wildcard server/*.cpp utils/*.cpp utils/element_map/*.cpp)

OBJ1		=	$(SRC1:%.cpp=%.o)

NAME1		=	zappyServer

SRC2		=	$(wildcard client/*.cpp utils/*.cpp utils/element_map/*.cpp)

OBJ2		=	$(SRC2:%.cpp=%.o)

NAME2		=	zappyClient

CXX			=	g++
CXXFLAGS	=	-Wall -pedantic -Wextra -Werror -std=c++14
LIBFLAGS	=	-lpthread -lboost_program_options -lsfml-network -lsfml-system

RM			=	rm -f

all:		$(NAME1) $(NAME2)

$(NAME1):	$(OBJ1)
			$(CXX) $(CXXFLAGS) $(LIBFLAGS) $(OBJ1) -o $(NAME1)

$(NAME2):	$(OBJ2)
			$(CXX) $(CXXFLAGS) $(LIBFLAGS) $(OBJ2) -o $(NAME2)

clean:
	$(RM)	$(OBJ1) $(OBJ2)

fclean:		clean
			$(RM) $(NAME1) $(NAME2)

re:			fclean all
.PHONY:		all clean fclean re

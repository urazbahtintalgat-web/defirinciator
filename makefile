CXX := g++
CXXFLAGS := -Wall -Wextra -Wpedantic -O2 -g -std=c++17

TARGET := differentiator

SRCS := \
	main.cpp \
	differentiator.cpp \
	diff_part/basic_derivatives.cpp \
	diff_part/take_diff.cpp \
	double_compare/double_compare.cpp \
	folder_names/generate_folder_and_names.cpp \
	graph/make_dot.cpp \
	html_SVAGA/make_html.cpp \
	init_destroy/diff_init_destroy.cpp \
	Letex_dump/Latex_derivatives.cpp \
	Letex_dump/make_Latex.cpp \
	math_part/calculate.cpp \
	read_data_differentiator/infix_read.cpp \
	read_data_differentiator/read_data.cpp \
	simplification/simplify.cpp

OBJS := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
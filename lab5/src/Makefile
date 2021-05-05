.PHONY: all clean

#переменные
OBJS= main.o


NAME= heap.exe
RM= del
# цель
all: $(NAME)

#удаляет ненужные файлы
clean:
	$(RM) -f $(OBJS)
	$(RM) -f $(OBJS:.o=.d)

#ставим флаги
CFLAGS= -std=c11 -pedantic -Wall -Wextra

#путь к папке include
INCLUDES+= -I../include

#где make ищет файлы. Тобишь в include и в проекте во всём
vpath %.h ../include

vpath %.c ./

#создаём либу
$(NAME): $(OBJS)
	gcc $(CFLAGS) -o $(NAME) $(INCLUDES) $(OBJS) -L.. -lHeap
	$(RM) -f $(OBJS)

#создаем обьектный файл и exe
%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -c -o $@ $<


-include $(OBJS:.o=.d)

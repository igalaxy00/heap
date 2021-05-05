.PHONY: all test


OBJS= heap.o
RM= del
MAKE= make
MYLIBNAME= libHeap.a


all: $(MYLIBNAME)

#если надо удалить нашу либу
uninstall:
	$(RM) -f $(MYLIBNAME)


#-Wno-pedantic-ms-format в попытках избежать конфликтов из-за size_t
CFLAGS= -std=c11 -pedantic -Wall -Wextra

# Включаемые файлы следует искать в каталоге "include"
INCLUDES+= -I./include

# Make должна искать файлы *.h в каталогах include и src
vpath %.h include src
# ..., а файлы *.c - в каталоге src
vpath %.c src
#создание либы и удаление мусора
$(MYLIBNAME): $(OBJS)
	$(AR) -rsc $@ $^
	$(RM) -f $(OBJS)

# Построение объектных файлов
%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -c -o $@ $<
#запуск test
test:
	$(MAKE) -C test
#запуск cmd
cmd: $(MYLIBNAME)
	$(MAKE) -C src

-include $(OBJS:.o=.d)
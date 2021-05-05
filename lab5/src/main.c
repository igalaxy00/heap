#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "../include/libHeap.h"

static void sort(char *input_file, char *output_file) {
    key_heap tmp = 0;
    key_heap *array = (key_heap *) malloc(sizeof(key_heap));//выделяем память для массива пар
    size_t size = 0;
    unsigned int data = 1;
    FILE *fin = fopen(input_file, "r");//открываем файл для чтения
    if (strcmp(input_file, "") == 0) {//если файл пустой то считываем из консоли

        fin = stdin;
    }
    int x;

    x = fscanf(fin, "%d", &tmp);// смотрим есть ли ещё что считать из потока и записываем в тмп

    while (x == 1) {//если есть
        if (size + 1 > data) {
            data *= 2;
            array = (key_heap *) realloc(array, sizeof(key_heap) * data);//переопредел память тк больше элементов
        }
        array[size] = tmp;//записываем в массив элементы которые считали
        size++;
        x = fscanf(fin, "%d", &tmp);// смотрим есть ли ещё что считать из потока и записываем в тмп
    }
    fclose(fin);//закрываем поток
    heapSort(array, size);// сортируем нашу кучу

    FILE *fout = fopen(output_file, "w");//открываем файл для письма
    if (strcmp(output_file, "") == 0) {//если файл пустой то поток вывода на консоль
        fout = stdout;
    }
    for (size_t i = 0; i < size; i++) {//печатаем
        fprintf(fout, "%d ", array[i]);
    }

    fclose(fout);//отчищаем память
    free(array);
}

static void tree(char *input_file, char *output_file, bool type) {//четыре
    heap *h;
    if (type) {//относительно типа создаем базу кучи
        h = maxHeap(8);
    } else {
        h = minHeap(8);
    }

    FILE *fin = fopen(input_file, "r");//открываем файл для чтения
    if (strcmp(input_file, "") == 0) {//если файла нет то идем на консоль
        printf("Print 1 node on 1 string like: key value\n");//пишем чтобы пользователь вводил
        fin = stdin;//поток ввода из кмд
    }
    int x = 0;
    key_heap tmp_key = 0;
    value_heap tmp_value = 0;
    x = fscanf(fin, "%d %u\n", &tmp_key, &tmp_value);//считываем и ключ и значение
    while (x == 2) {//пока есть что считывать
        heapAdd(h, (pair_heap) {tmp_key, tmp_value}); // добавляем в кучу  ключ значение
        x = fscanf(fin, "%d %u\n", &tmp_key, &tmp_value);//считываем и ключ и значение
    }
    fclose(fin);//закрываем поток
    printHeap(h);//печатаем кучу
    heapRemove(h);//убираем кучу

    FILE *fout = fopen(output_file, "w");//открываем файл для записи
    if (strcmp(output_file, "") == 0) {
        fout = stdout;
    }

    fclose(fout);
}

static void extract(char *input_file, char *output_file, bool type) {
    heap *h;
    if (type) {//понимаем по типу какая у нас куча мин или макс
        h = maxHeap(8);
    } else {
        h = minHeap(8);
    }

    FILE *fin = fopen(input_file, "r");//открываем файл и запускаем поток
    if (strcmp(input_file, "") == 0) {//если нет файла то читаем из консоли
        printf("Print 1 node on 1 string like: key value\n");
        fin = stdin;
    }
    int x = 0;
    key_heap tmp_key = 0;
    value_heap tmp_value = 0;
    x = fscanf(fin, "%d %u\n", &tmp_key, &tmp_value);//считываем  ключ и значение
    while (x == 2) {//считываем пока есть что считывать
        heapAdd(h, (pair_heap) {tmp_key, tmp_value});//добавляем в кучу ключ значение
        x = fscanf(fin, "%d %u\n", &tmp_key, &tmp_value);
    }
    fclose(fin);//закрываем поток
    pair_heap root = heapRoot(h);//корень
    printf("key=%d value=%u was extracted\n", root.key, root.value);//пишем что мы извлекли


    FILE *fout = fopen(output_file, "w");//открываем файл и поток для записи
    if (strcmp(output_file, "") == 0) {//если нет файла
        fout = stdout;//пишем в консоль
    }

    for (size_t i = 0; i < h->size; i++) {//печатаем всю кучу списком
        fprintf(fout, "%d %u\n", h->array[i].key, h->array[i].value);
    }
    heapRemove(h);//убираем кучу
    fclose(fout);//закрываем поток
}


int main(int argc, char *argv[]) {

    char *output_file = "";
    char *input_file = "";
    int output_arg = -1;
    int input_arg = -1;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {//если у нас есть файл маркер o
            if (output_arg != -1) {// и если нету файла
                printf("ILLEGAL FORMAT\n");//ошибка
                return -1;
            } else {//i +1 чтобы при 2 итерации записать нуждный аргумент
                output_arg = i + 1;//при второй итерации цикла мы записываем в output_file название файла
            }
        }
        if (i == output_arg) {
            output_file = argv[i];//записываем первый аргумент в аутпут файл
        }

        if (strcmp(argv[i], "-i") == 0) {//если у нас есть файл маркер -i
            if (input_arg != -1) {// и если нету файла
                printf("ILLEGAL FORMAT\n");//ошибка
                return -1;
            } else {//i +1 чтобы при 2 итерации записать нуждный аргумент
                input_arg = i + 1;//при второй итерации цикла мы записываем в input_file название файла
            }
        }
        if (i == input_arg) {
            input_file = argv[i];
        }
    }


    switch (argc) {
        case 1: {//если не хватает аргументов
            printf("Too few arguments, type --help for a list of options\n");
            return 0;
        }
        case 2: {// help
            if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
                printf(""
                       "a sort [-i] [input file] [-o] [output file] \n"
                       "Sorting array of integers\n"
                       "If you use input from CMD print any letter in the end\n"
                       "a (-max|-min) tree [-i] [input file] [-o] [output file]\n"
                       "Print heap\n"
                       "a (-max|-min) extract [-i] [input file] [-o] [output file]\n"
                       "Deleting max or min key in heap\n"
                );
                break;
            }

        }
        default: {
            break;
        }
    }

    bool type;
    if (strcmp(argv[1], "sort") == 0) {//аргумент сортировки
        sort(input_file, output_file);
    } else if (strcmp(argv[1], "-max") == 0) {//аргумент типа дерева
        type = true;
    } else if (strcmp(argv[1], "-min") == 0) {//аргумент типа дерева
        type = false;
    } else {
        printf("Invalid input, check --help option");
    }

    if (strcmp(argv[2], "tree") == 0) {
        tree(input_file, output_file, type);
    } else if (strcmp(argv[2], "extract") == 0) {
        extract(input_file, output_file, type);
    }



    return 0;

}
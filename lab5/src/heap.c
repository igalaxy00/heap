#include "../include/heap.h"
#include "malloc.h"
#include <stdbool.h>
#include <stdio.h>

//передаем кучу и 2 элемента
bool compare(const heap *h, const size_t i, const size_t j) {
    const int result = (int) h->array[i].key - (int) h->array[j].key;//сравниваем i элемент и j
    if (result > 0) {
        return true;// первый элемент больше
    } else {
        return false;// второй элемент больше
    }
}

heap *heapInit(const unsigned int start_data) {
    heap *h = (heap *) malloc(sizeof(heap));//выделяем память для структуры
    h->array = (pair_heap *) malloc(sizeof(pair_heap) * start_data);//выделяем память для элементов структуры(map)
    h->data = start_data ? start_data : 1; // если есть start_data(длина списка) то оставляем. Если нет то ставим 1
    h->size = 0; // размер 0
    return h;//возвращаем кучу
}


heap *maxHeap(const unsigned int start_data) {
    heap *h = heapInit(start_data);//создаем кучу с длинной start_data
    h->max = true;//флаг для max кучи
    return h;
}

heap *minHeap(const unsigned int start_data) {
    heap *h = heapInit(start_data);//создаем кучу с длинной start_data
    h->max = false;//флаг для min кучи
    return h;
}

// меняет местами узел, который слишком велик, со своим родителем
//пока он не станет не больше узла над ним
//
void heapShiftUp(heap *h, size_t i) {
    // если ребенок больше родителя и максимальная куча то занимаемся перестановкой
    while ((compare(h, i, (i - 1) / 2) == h->max) && (i >= 1)) {
        //меняем местами родителя и дочь
        const pair_heap tmp = h->array[i];
        h->array[i] = h->array[(i - 1) / 2];
        h->array[(i - 1) / 2] = tmp;
        i = (i - 1) / 2;//переход на новую итерацию
    }

}

//меняет местами узел, который слишком мал, с его самым большим дочерним узлом
void heapShiftDown(heap *h, size_t i) {

    while (2 * i + 1 < h->size) {//пока можно спускаться вниз
        const size_t left = 2 * i + 1;//левый потомок
        const size_t right = 2 * i + 2;//правый потомок
        size_t j = left;

        if ((right < h->size) && (compare(h, right, left) == h->max)) {
            j = right;//если правый больше чем левый то j правый
        }
        if (compare(h, i, j) == h->max) {
            break;//если отец больше чем сын и куча max то все работает
        }
        const pair_heap tmp = h->array[i];//меняем местами
        h->array[i] = h->array[j];
        h->array[j] = tmp;
        i = j;
    }
}


void heapAdd(heap *h, pair_heap p) {
    if (h->size + 1 >= h->data) {//если выходим за изначальный размер то мы перераспределяем память
        h->data *= 2;
        h->array = (pair_heap *) realloc(h->array, h->data * sizeof(pair_heap));
    }
    h->array[(h->size)++] = p;//добавляем элемент
    heapShiftUp(h, h->size - 1);//двигаем его куда надо
}


pair_heap heapRoot(heap *h) {//извлекаем и возвращаем корень
    const pair_heap min = h->array[0];//мин == корень
    h->array[0] = h->array[h->size - 1];
    h->size--;
    heapShiftDown(h, 0);//сортируем кучу
    return min;
}

void buildHeap(heap *h) {//строим кучу из набора данных
    for (size_t i = h->size / 2; i <= h->size / 2; i--) {
        heapShiftDown(h, i);
    }
}

heap *minHeapArray(pair_heap *p, size_t size) {

    heap *h = heapInit(size);//инициализируем кучу

    for (size_t i = 0; i < size; i++) {//копирует массив в выделенную память
        h->array[i] = p[i];
    }
    h->data = size;
    h->size = size;
    h->max = false;//маркер кучи

    buildHeap(h);
    return h;
}

heap *maxHeapArray(pair_heap *p, size_t size) {

    heap *h = heapInit(size);//выделяем память для всей кучи и элементов

    for (size_t i = 0; i < size; i++) {//копирует массив в выделенную память
        h->array[i] = p[i];
    }
    h->data = size;
    h->size = size;
    h->max = true;//маркер кучи

    buildHeap(h);//строим саму кучу
    return h;
}

void heapSort(key_heap *array, size_t size) {
    pair_heap *array_pairs = (pair_heap *) malloc(sizeof(pair_heap) * size);//массив пар
    for (size_t i = 0; i < size; i++) {
        array_pairs[i] = (pair_heap) {array[i], 0};//список ключей
    }
    heap *h = minHeapArray(array_pairs, size);//строим кучу
    for (size_t i = 0; i < size; i++) {
        array[i] = heapRoot(h).key;//кладетм в массив все отсортированные ключи
    }
    //отчищаем память
    free(array_pairs);
    heapRemove(h);
}


void heapRemove(heap *h) {//отчищение памяти кучи
    free(h->array);
    free(h);
}

//вывод дерева в консоль
void printBT(heap *h, char *prefix, size_t index, bool isLeft) {
    if (index < h->size) {
        printf("%s", prefix);
        printf("%s", isLeft ? "|_" : "\\_");
        printf("%d (%u)_\n", h->array[index].key, h->array[index].value);

        char buff[256];
        snprintf(buff, sizeof(buff), "%s%s", prefix, isLeft ? "|   " : "    ");
        printBT(h, buff, index * 2 + 1, true);
        printBT(h, buff, index * 2 + 2, false);
    } else {
        printf("%s\n", prefix);
    }
}

void printHeap(heap *h) {//напечатать кучу
    printBT(h, "", 0, false);
}
#include "../include/heap.h"
#include "CuTest.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

static bool heapIsValid(heap *h) {//проверяем куча ли это
    for (size_t i = 0; i < h->size; i++) {//идём по всей куче
        size_t left = 2 * i + 1;//левый потомок
        size_t right = 2 * i + 2;//правый потомок
        if (left < h->size) {//если левый потомок сущзествует
            if (h->max) {//маркер кучи
                if (h->array[i].key < h->array[left].key) {
                    return false;//проверяем если родитель меньше потомка и куча max
                }
            } else {
                if (h->array[i].key > h->array[left].key) {
                    return false;//проверяем если родитель больше потомка и куча min
                }
            }
        }
        if (right < h->size) {//если правый потомок существует
            if (h->max) {//маркер кучи
                if (h->array[i].key < h->array[right].key) {
                    return false;//проверяем если родитель меньше потомка и куча max
                }
            } else {
                if (h->array[i].key > h->array[right].key) {
                    return false;//проверяем если родитель больше потомка и куча min
                }
            }
        }
    }
    return true;//если всё ок то ретерним тру
}


static void TestHeapInit(CuTest *tc) {//проверяем инициализацию кучи
    printf("1) Heap init test\n");
    heap *h = heapInit(0);//инициализируем кучу
    //мы инициализируем кучу с 0 памятью и она не может быть создана. Проверка на это
    CuAssertIntEquals_Msg(tc, "Heap with data 0 is created!", 1, h->data);

    h = heapInit(10);
    //проверка то ли колличество памяти выделилось
    CuAssertIntEquals_Msg(tc, "Wrong amount of memory allocated!", sizeof(pair_heap) * 10, sizeof(pair_heap) * h->data);
    heapRemove(h);
}


static void TestShiftUp(CuTest *tc) {
    printf("2) Heap shift up test\n");
    heap *h = maxHeap(8);
    h->size = 4;
    pair_heap p[4] = {{8, 0},
                      {7, 0},
                      {4, 0},
                      {6, 0}};
    for (size_t i = 0; i < sizeof(p) / sizeof(p[0]); i++) {
        h->array[i] = p[i];
    }
    heapAdd(h, (pair_heap) {10, 0});//добавляем в правильную кучу новый элемент
    CuAssert(tc, "Prepared heap is wrong", heapIsValid(h));//проверяем отбалансировалось ли оно

    h->array[4] = (pair_heap) {10, 0};//вручную меняем элемент
    CuAssert(tc, "Changing element didn't brake heap", !heapIsValid(h));// проверяем норм ли все

    heapShiftUp(h, 4);//вручную делаем поворот в куче
    CuAssert(tc, "Heap is wrong after shifting up", heapIsValid(h));//проверяем правильность кучи
    heapRemove(h);

    //то же самое как и с max heap
    heap *x = minHeap(1000);
    x->size = 1000;
    for (size_t i = 0; i < 999; i++) {
        x->array[i] = (pair_heap) {1, 0};
    }
    x->array[999] = (pair_heap) {0, 0};
    CuAssert(tc, "Prepared heap is valid!", !heapIsValid(x));

    heapShiftUp(x, 999);
    CuAssert(tc, "Heap is not valid!", heapIsValid(x));
    heapRemove(x);
}

static void TestShiftDown(CuTest *tc) {
    printf("3) Heap shift down test\n");
    heap *h = minHeap(8);//создаем мин кучу
    h->size = 4;
    pair_heap p[4] = {{8, 0},
                      {7, 0},
                      {4, 0},
                      {7, 0}}; // prepared heap
    for (size_t i = 0; i < sizeof(p) / sizeof(p[0]); i++) {
        h->array[i] = p[i];
    }

    heapShiftDown(h, 0); // двигаем 8 вниз
    CuAssert(tc, "Heap is not valid!", heapIsValid(h));//проверяем норм ли куча
    //проверяем поменялся ли корень
    CuAssertIntEquals_Msg(tc, "Node with key 8 not shifted down", 4, h->array[0].key);

    heapShiftDown(h, 0); // вигаем 8 вниз
    CuAssert(tc, "Heap is not valid!", heapIsValid(h));//проверяем норм ли куча
    //проверяем поменялся ли корень
    CuAssertIntEquals_Msg(tc, "Node 4 shifted down", 4, h->array[0].key);
    heapRemove(h);

}

static void TestHeapAdd(CuTest *tc) {
    printf("4) Heap add test\n");
    heap *h = minHeap(2);
    heapAdd(h, (pair_heap) {10, 0});
    CuAssert(tc, "Heap is not valid!", heapIsValid(h));//проверяем норм ли куча
    //пихаем элемент в зарезервированную память . Она не должна измениться
    CuAssertIntEquals_Msg(tc, "Size of allocated memory increase, but shouldn't", 2, h->data);
    //проверяем изменился ли размер кучи
    CuAssertIntEquals_Msg(tc, "Size of heap incorrect", 1, h->size);

    heapAdd(h, (pair_heap) {15, 0});//добавляем в кучу
    CuAssert(tc, "Heap is not valid!", heapIsValid(h));//проверяем норм ли куча
    //пихаем элемент в зарезервированную память . Она  должна измениться
    CuAssertIntEquals_Msg(tc, "Size of allocated memory dont increase, but should", 4, h->data);
    //проверяем изменился ли размер кучи
    CuAssertIntEquals_Msg(tc, "Size of heap incorrect", 2, h->size);

    heapAdd(h, (pair_heap) {6, 0});
    CuAssert(tc, "Heap is not valid!", heapIsValid(h));//проверяем норм ли куча
    heapRemove(h);
}

static int cmp(const void *a, const void *b) {//функция сравнения
    return *(int *) a - *(int *) b;
}

static void TestHeapRoot(CuTest *tc) {
    printf("5) Heap insert root test\n");
    heap *h = minHeap(16);
    key_heap array[10] = {23, 23, 42, 24, 22, 2, 42, 2222, 6464, 1};//массив
    for (size_t i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        heapAdd(h, (pair_heap) {array[i], 0});//добавляем массив в кучу
    }
    //быстро сортируем список
    qsort(array, sizeof(array) / sizeof(array[0]), sizeof(array[0]), cmp);
    for (size_t i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        //проверяем является ли i элемент корнем а потом извлекаем его
        CuAssertIntEquals_Msg(tc, "Invalid item removed", array[i], heapRoot(h).key);
        CuAssert(tc, "Heap is not valid after extraction", heapIsValid(h));//проверяем норм ли куча
    }
    heapRemove(h);
}



static void HeapSortTest(struct CuTest *tc) {
    printf("6) HeapSort test\n");
    for (size_t i = 0; i < 100; i++) {
        size_t array_size = rand() % 1000 + 1;
        //создаем 2 одинаковых по памяти массива
        key_heap *array_ex = (key_heap *) malloc(sizeof(key_heap) * array_size);
        key_heap *array_ac = (key_heap *) malloc(sizeof(key_heap) * array_size);
        for (size_t j = 0; j < array_size; j++) {
            key_heap next = rand();//заполняем рандомными ключами
            array_ex[j] = next;
            array_ac[j] = next;
        }

        qsort(array_ex, array_size, sizeof(key_heap), cmp);//сортируем быстрой сортировкой
        heapSort(array_ac, array_size);//сортируем нашей функцией

        for (size_t j = 0; j < array_size; j++) {
            //наша сортировка и qsort должны совпадать
            CuAssertIntEquals_Msg(tc, "HeapSort is invalid", array_ex[j], array_ac[j]);
        }

    }

}


static CuSuite *StrUtilGetSuite() {
    //функция для кучи тестов
    printf("Tests:\n");
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestHeapInit);
    SUITE_ADD_TEST(suite, TestShiftUp);
    SUITE_ADD_TEST(suite, TestShiftDown);
    SUITE_ADD_TEST(suite, TestHeapAdd);
    SUITE_ADD_TEST(suite, TestHeapRoot);
    SUITE_ADD_TEST(suite, HeapSortTest);

    return suite;
}


static void RunAllTests(void) {//запускаем все тесты
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    CuSuiteAddSuite(suite, StrUtilGetSuite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    printf("Printing MAX heap example:\n");
    size_t array_size = 15;
    pair_heap *array = (pair_heap *) malloc(sizeof(pair_heap) * array_size);
    for (size_t j = 0; j < array_size; j++) {
        array[j] = (pair_heap) {rand() % 1000, rand() % 42};
    }
    heap *h = maxHeapArray(array, array_size);
    printHeap(h);
    heapRemove(h);
    free(array);
}


int main(void) {
    RunAllTests();
}

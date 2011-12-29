/*
 * Пилообразная последовательность
 * 
 * (Время: 1 сек. Память: 16 Мб Сложность: 38%)
 * 
 * Последовательность a1, a2, a3, … , an-1, an называется пилообразной, если она
 * удовлетворяет одному из следующих условий: 
 * 1)	a1 < a2 > a3 < … > an-1 < an
 * 2)	a1 > a2 < a3 > … < an-1 > an
 * 
 * Дана числовая последовательность. Требуется определить длину самой длинной ее
 * пилообразной непрерывной подпоследовательности.
 * 
 * Входные данные
 * 
 * В первой строке входного файла INPUT.TXT записано натуральное число N –
 * количество элементов последовательности. Во второй строке файла через
 * пробел записаны N элементов целочисленной последовательности {ai}.
 * Ограничения: N<106, |ai| < 32000.
 * 
 * Выходные данные
 * 
 * В единственную строку выходного файла OUTPUT.TXT нужно вывести одно целое
 * число — длину самой длиной непрерывной пилообразной подпоследовательности.
 */

#include <stdio.h>

enum {
    LESS_THAN,
    GREATER_THAN,
    EQUAL
};

int cur_op(int lhs, int rhs, int *prev_op, int first_run)
{
    int ret = 0;

    if(first_run) {
        if(lhs < rhs) {        
            *prev_op = GREATER_THAN;
            ret = 1;
        } else if(lhs > rhs) {
            *prev_op = LESS_THAN;
            ret = 1;
        } else if(lhs == rhs) {
            *prev_op = EQUAL;
            ret = 0;
        }
    } else {
        switch(*prev_op) {
            case LESS_THAN:
                ret = (lhs < rhs);
                *prev_op = GREATER_THAN;
                break;
            case GREATER_THAN:
                ret = (lhs > rhs);
                *prev_op = LESS_THAN;
                break;
            case EQUAL:
                ret = 0;
                break;
        }
    }

    return ret;
}

int main(int argc, char **argv)
{
    int N = 0;
    int cur = 0;
    int next = 0;
    int max = 0;

    int first_run = 1;
    int cnt = 1;

    int operation = LESS_THAN;

    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    
    scanf("%d", &N);
    scanf("%d", &cur);
    scanf("%d", &next);


    for(int i = 1; i < N; ) {
        
        if(cur_op(cur, next, &operation, first_run)) {
            ++cnt;
            first_run = 0;
        } else {
            cnt = 1;
            first_run = 1;            
        } 

        if(operation == EQUAL || !first_run) {
            cur = next;
            scanf("%d", &next);  
            ++i;
        }

        if(max < cnt) {
            max = cnt;
        }
    }

    printf("%d", max);

    return 0;
}

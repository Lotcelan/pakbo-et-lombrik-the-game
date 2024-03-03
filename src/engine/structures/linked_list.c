#include "../include/linked_list.h"


int length(List *list)
    {
        int length = 0 ;
        while (list != NULL) 
            {
                length ++ ;
                list = list->next ;
            }
        return length ;
    }

List *create_list(void *value, List *next) 
    {
        List *list = malloc(sizeof(*list)) ;
        list->value = value ;
        list->next = next ;
        return list ;
    }

List *list_del_first( List *l, void delete(List*) ) 
    {
        List *p = l->next ;
        if (delete!=NULL) 
            {
                delete(l) ;
            }
        return p ;
    }

List *append_end(void *value, List *list) 
    {
        if (list == NULL)
            {
                return create_list(value, NULL) ;
            }
        return create_list(list->value, append_end(value, list->next)) ;
    }

List *append_first(void *value, List *list)
    {
        return create_list(value, list) ;
    }

List *reverse(List *list)
    {
        void *first_element = list->value ;
        List *new_list = create_list(first_element, NULL) ;
        list = list->next ;
        while (list != NULL)
            {
                void *element = list->value ;
                new_list = create_list(element, new_list) ;
                list = list->next ;
            }
        return new_list ;
    }

List *list_del_i_element(List *l, int ind, void delete(List*))
    {
        int len = lengh(l) ;
        if (ind>len)
            {
                return l ;
            }
        if (ind == 1)
            {
                return list_del_first(l, delete) ;
            }
        ind -- ;
        return create_list(l->value, list_del_i_element(list_del_first(l, delete), ind, delete)) ;
    }

void print_list(List *list)
    {   
        if (list == NULL)
            {
                printf("[] \n") ;
            }
        if (list != NULL)
        {
            printf("[") ;
            void *element = list->value ;
            list = list->next ;
            printf("%s", (char*)element) ;
            while (list != NULL)
                {
                    void *element = list->value ;
                    list = list->next ;
                    printf(", %s", (char*)element) ;
                }
            printf("] \n") ;
        }
    }

void delete_all_non_struct(List *l)
    {
        free(l) ;
    }

List *merge(List *list1, List *list2, void delete(List*), int comparaison(void*, void*))
{
    if (list1 == NULL)
    {
        return list2;
    }
    else if (list2 == NULL)
    {
        return list1;
    }

    void *val1 = list1->value;
    void *val2 = list2->value;

    if (comparaison(val1, val2) == 1)
    {
        List *l1 = list_del_first(list1, delete) ;
        return create_list(val1, merge(l1, list2, delete, comparaison));
    }
    else
    {
        List *l2 = list_del_first(list2, delete) ;
        return create_list(val2, merge(list1, l2, delete, comparaison));
    }
}

int compare_int(void *a, void *b)
    {
        if (*(int*)a <= *(int*)b)
            {
                return 1 ;
            }
        return 0 ;
    }

List *prefix(List *list, int n, void delete(List*))
    {   
        if (n == 0)
            {
                return NULL ;
            }
        void *val = list->value ;
        List *suit = list_del_first(list,delete) ;
        List *pre = prefix(suit, n-1, delete) ;
        return create_list(val, pre) ;
    }

List *suffix(List *list, int n, void delete(List*))
    {
        if (n == 0)
            {
                return list ;
            }
        return suffix(list_del_first(list,delete), n-1, delete) ;
    }

List *suffix_non_delete(List *list, int n)
    {
        if (n == 0)
            {
                return list ;
            }
        List *p = list ;
        return suffix_non_delete(p->next, n-1) ;
    }

List *prefix_non_delete(List *list, int n)
    {
        if (n == 0)
            {
                return NULL ;
            }
        List *p = list ;
        return create_list(p->value, prefix_non_delete(p->next, n-1)) ;
    }

void list_delete(List *list, void delete(List*))
    {
        while (list != NULL)
            {
                list = list_del_first(list, delete) ;
            }
        print_list(list) ;
    }

List *merge_sort(List *list, void delete(List*), int comparaison(void*, void*))
    {
        if (lengh(list) <= 1)
            {
                return list ;
            }
        else
            {
                int len = lengh(list) ;
                List *begin = prefix_non_delete(list, (len/2)) ;
                List *end = suffix_non_delete(list, (len/2)) ;
                List *l1 = merge_sort(begin, delete, comparaison) ;
                List *l2 = merge_sort(end, delete, comparaison) ;
                List *merged = merge(l1, l2, delete, comparaison) ;
                return merged ;
                list_delete(list, delete) ;
            } 
    }

int compare_str(void *a, void *b)
    {
        char mot1[30 + 1];
        char mot2[30 + 1];
        strncpy(mot1, (char*)a, 30) ;
        mot1[30] = '\0';  // Assurez-vous de terminer la chaîne avec un caractère nul

        strncpy(mot2, (char*)b, 30);
        mot2[30] = '\0';
        int resultat = strcasecmp(mot1, mot2);
        if (resultat == 0) 
            {
                //Les mots sont égaux.
                return 1 ;
            } 
        else if (resultat < 0) 
            {
                //mot1 vient avant mot2 dans l'ordre alphabétique.
                return 1 ;
            } 
        else 
            {
                //mot1 vient après mot2 dans l'ordre alphabétique.
                return 0 ;
            }
    }



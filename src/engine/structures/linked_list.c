#include "../include/linked_list.h"

void* head(List *list)
    {
        if (list == NULL) {
            return NULL;
        }
        return list->value ;
    }

List* tail(List *list)
    {
        if (list == NULL) {
            return NULL;
        }
        return list->next ;
    }


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
        List *list = malloc(sizeof(List)) ;
        list->value = value ;
        list->next = next ;
        return list ;
    }

List* delete_compare(List* l, void* value, int compare(void*, void*), void delete(void*)) {
    if (l == NULL) {
        return NULL;
    }
    if (l->next == NULL) {
        if (compare(l->value, value) == 1) {
            if (delete != NULL) {
                delete(l->value);
            }
            free(l);
            return NULL;
        }
        return l;
    }
    if (compare(l->value, value) == 1) {
        List* next = l->next;
        if (delete != NULL) {
            delete(l->value);
        }
        free(l);
        return delete_compare(next, value, compare, delete);
    }
    l->next = delete_compare(l->next, value, compare, delete);
    return l;


}


List *list_del_first( List *l, void delete(void*) ) 
    {
        if (l == NULL)
            {
                return NULL ;
            }
        List *p = tail(l) ;
        if (delete!=NULL) 
            {
                delete(l->value) ;
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
        if (list == NULL)
            {
                return NULL ;
            }
        
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

void* get_i_element(List *list, int i)
    {
        if (list == NULL)
            {
                return NULL ;
            }

        if (i == 0)
            {
                return list->value ;
            }
        return get_i_element(list->next, i-1) ;
    }

List *list_del_i_element(List *l, int ind, void delete(void*))
    {
        int len = length(l) ;
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

List *merge(List *list1, List *list2, void delete(void*), int comparaison(void*, void*))
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

List *prefix(List *list, int n, void delete(void*))
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

List *suffix(List *list, int n, void delete(void*))
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

void list_delete(List *list, void delete(void*))
    {
        while (list != NULL)
            {
                list = list_del_first(list, delete) ;
            }
    }

List *merge_sort(List *list, void delete(void*), int comparaison(void*, void*))
    {
        if (length(list) <= 1)
            {
                return list ;
            }
        else
            {
                int len = length(list) ;
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



List *create_list_cyclic(void *value, List *next)
    {
        if (next == NULL)
            {
                List *list = malloc(sizeof(List)) ;
                list->value = value ;
                list->next = list ;
                return list ;
            }
        List *list = malloc(sizeof(List)) ;
        list->value = value ;
        list->next = next ;
        List *p = next ;
        while(p != NULL)
            if (p->next != next)
            {
                p = p->next ;
            } else {
                break;
            }
        if (p == NULL) return NULL; // there was an error
        p->next = list ;
        return list ;
    }

void print_list_cyclic(List *list) 
    {
        if (list == NULL) 
            {
                printf("\n [] \n \n") ;
                return ;
            }

        printf("\n [") ;
        void *element = list->value ;
        List *head = list ;
        list = list->next ;
        printf("%s", (char*)element) ;
        while (list != head)
            {
                void *element = list->value ;
                list = list->next ;
                printf(", %s", (char*)element) ;
            }
        printf("] \n \n") ;
    }

List *list_cyclic_del_first( List *l, void delete(void*) )
    {
        if (l == NULL) return NULL;
        List *move = l ;
        if (move->next == l)
            {
               delete(l->value) ;
               return NULL ;
            }
        while (move->next != l)
            {
                move = move->next ;
            }
        move->next = l->next ;
        List *p = l->next ;
        if (delete!=NULL) 
            {
                // if ()
                delete(l->value) ;
            }
        return p ;
    }

int length_cyclic(List *list)
    {
        if (list != NULL)
        {
            int length = 1 ;
            List *p = list ;
            while (p->next != list) 
                {
                    length ++ ;
                    p = p->next ;
                }
            return length ;
        }
        return 0 ;
    }

List *append_cyclic_end(void *value, List *list, void delete(void*)) 
    {
        if (list == NULL)
            {
                return create_list_cyclic(value, NULL) ;
            }
        if (list->next == list)
            {
                void *element = list->value ;
                List *suit = list_cyclic_del_first(list, delete) ;
                suit = create_list_cyclic(value, suit) ;
                suit = create_list_cyclic(element, suit) ;
                return suit ;
            }
        void *element = list->value ;
        List *suit = list_cyclic_del_first(list, delete) ;
        return create_list_cyclic(element, append_cyclic_end(value, suit, delete)) ;
    }

List *append_cyclic_first(void *value, List *list)
    {
        return create_list_cyclic(value, list) ;
    }

List *reverse_cyclic(List *list, void delete(void*))
    {
        if (list == NULL)
            {
                return NULL ;
            }
        void *first_element = list->value ;
        List *new_list = create_list_cyclic(first_element, NULL) ;
        list = list_cyclic_del_first(list, delete) ;
        while (list != NULL)
            {
                void *element = list->value ;
                new_list = create_list_cyclic(element, new_list) ;
                list = list_cyclic_del_first(list, delete) ;
            }
        return new_list ;
    }

List *list_cyclic_del_i_element(List *l, int ind, void delete(void*))
    {
        int len = length_cyclic(l) ;
        if (ind>len)
            {
                return l ;
            }
        if (ind == 1)
            {
                return list_cyclic_del_first(l, delete) ;
            }
        ind -- ;
        return create_list_cyclic(l->value, list_cyclic_del_i_element(list_cyclic_del_first(l, delete), ind, delete)) ;
    }

List *merge_cyclic(List *list1, List *list2, void delete(void*), int comparaison(void*, void*))
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

    if (comparaison(val1, val2) == 1) //signifie que val1 arrive avant val2 dans l'ordre de comparaison
    {
        list1 = list_cyclic_del_first(list1, delete) ;
        List *suit = merge_cyclic(list1, list2, delete, comparaison) ;
        return create_list_cyclic(val1, suit);
    }
    else
    {
        list2 = list_cyclic_del_first(list2, delete) ;
        List *suit = merge_cyclic(list1, list2, delete, comparaison) ;
        return create_list_cyclic(val2, suit);
    }
}

List *suffix_cyclic_non_delete(List *list, int n, List *first)
    {
        int len = length_cyclic(first) ;
        if (n >= len)
            {
                return NULL ;
            }
        if (n == 0)
            {
                if (list == first)
                {
                    return NULL ;
                }
                List *p = list ;
                return create_list_cyclic(p->value, suffix_cyclic_non_delete(p->next, n, first)) ;
            }
        List *p = list ;
        return suffix_cyclic_non_delete(p->next, n-1, first) ;
    }

List *prefix_cyclic_non_delete(List *list, int n)
    {
        if (n == 0)
            {
                return NULL ;
            }
        List *p = list ;
        return create_list_cyclic(p->value, prefix_cyclic_non_delete(p->next, n-1)) ;
    }

void list_cyclic_delete(List *list, void delete(void*))
    {
        while (list != NULL)
            {
                list = list_cyclic_del_first(list, delete) ;
            }
    }

List *merge_sort_cyclic(List *list, void delete(void*), int comparaison(void*, void*))
    {
        if (length_cyclic(list) <= 1)
            {
                return list ;
            }
        else
            {
                int len = length_cyclic(list) ;
                List *begin = prefix_cyclic_non_delete(list, (len/2)) ;
                List *end = suffix_cyclic_non_delete(list, (len/2), list) ;
                List *l1 = merge_sort_cyclic(begin, delete, comparaison) ;
                List *l2 = merge_sort_cyclic(end, delete, comparaison) ;
                List *merged = merge_cyclic(l1, l2, delete, comparaison) ;
                return merged ;
                list_cyclic_delete(list, delete) ;
            } 
    }

List *map_list_cyclic(List *list, void *f(void *a), void delete(void*))
    {
        if (list == NULL)
            {
                return list ;
            }
        void *element = list->value;
        list = list_cyclic_del_first(list, delete);
        element = f(element);
        return create_list_cyclic(element, map_list_cyclic(list, f, delete)) ;
    }


List* copy_list(List* to_copy, void* (*copy_value)(void*)) {
    // Quand on veut copier LE CONTENU de la liste (genre une Entity)
    List* new = NULL;
    List* current = to_copy;
    while (current != NULL) {
        new = append_first(copy_value(current->value), new);
        current = current->next;
    }
    return reverse(new);

}

List* copy_cyclic_list(List* to_copy, void* (*copy_value)(void*)) {
    // Quand on veut copier LE CONTENU de la liste (genre une Entity)
    List* new = NULL;
    List* current = to_copy;
    List* first = to_copy;
    while (current != NULL) {
        if ( current->next == first) break;
        new = append_cyclic_first(copy_value(current->value), new);
        current = current->next;
    }
    if (current != NULL) {
        new = append_cyclic_first(copy_value(current->value), new);
    }
    return new;
}

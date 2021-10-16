#include <cgreen/cgreen.h>
#include <string.h>

#include "hiker.h"

/*
[OK] 1 Run the program without file then out put list shall be empty.
[OK] 2 Run the program with file "one.txt", then recent file list shall contain "one.txt"
[OK] 3 Run the program with the file "one.txt" and followed by
   two.txt then, once again file one.txt then list should contain one.txt 
   on top followed by two.txt.
[OK] 4 While adding any file in the list. Check size of list. If >10 remove oldest item in list
[OK] 5 Return NULL if asked about non-existent item
*/
 
Describe(hiker);
BeforeEach(hiker) {}
AfterEach(hiker) {}

/*******************/
/* PRODUCTION CODE */
/*******************/
#define NULL ((void*)0)
#define MAX_ITEMS 10

typedef struct {
    int   length;
    char* items[MAX_ITEMS];
} recently_used_list_t;

recently_used_list_t create_rul() {
    recently_used_list_t rul;
    rul.length = 0;
    return rul;
}
 
// Argument convention:
// - Pass by pointer when modifying structure (aliasing)
// - Pass by value when pure computation

int get_length(recently_used_list_t rul) {
    return rul.length;
}

int find_item(recently_used_list_t rul, char* item) {
    for (int i = 0; i < rul.length; ++i)
        if (strcmp(rul.items[i], item) == 0)
            return i;
    return rul.length;
}

char* item_at(recently_used_list_t rul, int index) {
    if(index >= rul.length)
        return NULL;
    return rul.items[index];
}

void add_item(recently_used_list_t* rul, char* item) {
    int n = find_item(*rul, item);
    for(int i = n; i > 0; i--)
        rul->items[i] = rul->items[i-1];
    rul->items[0] = item;
    if(n == rul->length && rul->length < MAX_ITEMS)
        rul->length++;
}

recently_used_list_t create_rul_from_string(char* str) {
    char copy[5000];
    strcpy(copy, str);
    recently_used_list_t reversed = create_rul();
    char * pch;
    pch = strtok(copy,"\n");
    while (pch != NULL)
    {
        add_item(&reversed, pch);
        pch = strtok (NULL, "\n");
    }
    recently_used_list_t rul = create_rul();
    for(int i = 0; i < reversed.length; i++)
        add_item(&rul, item_at(reversed, i));
    return rul;
}

void rul_to_string(recently_used_list_t rul, char* dest) {
    for(int i = 0; i < rul.length; i++)
        dest += sprintf(dest, "%s\n", item_at(rul, i));
}

/***************/
/* MICRO TESTS */
/***************/

Ensure(hiker, converting_rul_to_string_one_item) {
    char buffer[5000];
    recently_used_list_t rul = create_rul();
    add_item(&rul, "one.txt");
    rul_to_string(rul, buffer);
    assert_that(buffer, is_equal_to_string("one.txt\n"));
}

Ensure(hiker, converting_rul_to_string_two_items) {
    char buffer[5000];
    recently_used_list_t rul = create_rul();
    add_item(&rul, "one.txt");
    add_item(&rul, "two.txt");
    rul_to_string(rul, buffer);
    assert_that(buffer, is_equal_to_string("two.txt\none.txt\n"));
}

Ensure(hiker, creating_rul_from_one_item_string) {
    recently_used_list_t rul = create_rul_from_string("one.txt\n");
    assert_that(item_at(rul, 0), is_equal_to_string("one.txt"));
}

Ensure(hiker, creating_rul_from_two_item_string) {
    recently_used_list_t rul = create_rul_from_string("one.txt\ntwo.txt\n");
    assert_that(item_at(rul, 0), is_equal_to_string("one.txt"));
    assert_that(item_at(rul, 1), is_equal_to_string("two.txt"));
}

Ensure(hiker, check_length_one_element) {
    recently_used_list_t rul = create_rul();
    add_item(&rul, "one.txt");
    assert_that(get_length(rul), is_equal_to(1));
}

Ensure(hiker, check_item_one_element) {
    recently_used_list_t rul = create_rul();
    add_item(&rul, "one.txt");
    assert_that(item_at(rul, 0), is_equal_to_string("one.txt"));
}

Ensure(hiker, access_outside_returns_null) {
    recently_used_list_t rul = create_rul();
    add_item(&rul, "one.txt");
    assert_that(item_at(rul, 1), is_null);
}

Ensure(hiker, finding_an_item) {
    recently_used_list_t rul = create_rul();
    add_item(&rul, "one");
    assert_that(find_item(rul, "one"), is_equal_to(0));
}
 
Ensure(hiker, not_finding_an_item) {
    recently_used_list_t rul = create_rul();
    add_item(&rul, "one");
    assert_that(find_item(rul, "two"), is_equal_to(1));
}

Ensure(hiker, add_two_items_check_length) {
    recently_used_list_t rul = create_rul();
    add_item(&rul, "one");
    add_item(&rul, "two");
    assert_that(rul.length, is_equal_to(2));
}

Ensure(hiker, add_same_item) {
    recently_used_list_t rul = create_rul();
    add_item(&rul, "one");
    add_item(&rul, "one");
    assert_that(rul.length, is_equal_to(1));
}

Ensure(hiker, adding_two_items_places_last_at_top) {
    recently_used_list_t rul = create_rul();
    add_item(&rul, "one");
    add_item(&rul, "two");
    assert_that(item_at(rul, 0), is_equal_to_string("two"));
}

/*********************/
/* INTEGRATION TESTS */
/*********************/

Ensure(hiker, init_list_and_add_two_new_items_different_order) {
    recently_used_list_t rul = create_rul();
    add_item(&rul, "one.txt");
    add_item(&rul, "two.txt");
    add_item(&rul, "one.txt");
    
    assert_that(get_length(rul), is_equal_to(2));
    assert_that(item_at(rul, 0), is_equal_to_string("one.txt"));
    assert_that(item_at(rul, 1), is_equal_to_string("two.txt"));
}

Ensure(hiker, more_than_max_items_added) {
    recently_used_list_t rul = create_rul();
    add_item(&rul, "1"); add_item(&rul, "2");
    add_item(&rul, "3"); add_item(&rul, "4");
    add_item(&rul, "5"); add_item(&rul, "6");
    add_item(&rul, "7"); add_item(&rul, "8");
    add_item(&rul, "9"); add_item(&rul, "10");
    add_item(&rul, "11");
    assert_that(get_length(rul), is_equal_to(10));
    assert_that(item_at(rul, 0), is_equal_to_string("11"));
    assert_that(item_at(rul, 9), is_equal_to_string("2"));
}

Ensure(hiker, loading_and_saving) {
    recently_used_list_t rul = create_rul_from_string("one.txt\ntwo.txt\nthree.txt\n");
    char buffer[5000];
    rul_to_string(rul, buffer);
    assert_that(buffer, is_equal_to_string("one.txt\ntwo.txt\nthree.txt\n"));
}

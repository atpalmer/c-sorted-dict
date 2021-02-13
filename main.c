#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    char c;
} Item;

typedef struct {
    int count;
    Item *items[];
} Items;

#define TO_KEY(i) (((i) % 26))
#define TO_ALPHA(i) (((i) % 26) + 65)

Item *Item_rand(void) {
    Item *item = malloc(sizeof *item);
    int val = rand();
    item->key = TO_KEY(val);
    item->c = TO_ALPHA(val);
    return item;
}

void Item_free(Item *this) {
    free(this);
}

Items *Items_new(void) {
    static const int COUNT = 15;
    Items *new = malloc(sizeof *new + COUNT * sizeof(Item *));
    new->count = 0;
    for(int i = 0; i < COUNT; ++i) {
        new->items[i] = Item_rand();
        ++new->count;
    }
    return new;
}

void Items_free(Items *this) {
    for(int i = 0; i < this->count; ++i)
        Item_free(this->items[i]);
    free(this);
}

void Items_print(Items *this) {
    printf("Items count: %d\n", this->count);
    for(int i = 0; i < this->count; ++i)
        printf("%c (%d); ", this->items[i]->c, this->items[i]->key);
    printf("\n");
}

void Items_sort(Items *this) {
    /* selection sort */
    for(int place = 0; place < this->count - 1; ++place) {
        for(int seek = place + 1; seek < this->count; ++seek) {
            if(this->items[seek]->key < this->items[place]->key) {
                Item *tmp = this->items[place];
                this->items[place] = this->items[seek];
                this->items[seek] = tmp;
            }
        }
    }
}

int main(void) {
    Items *items = Items_new();
    Items_print(items);
    Items_sort(items);
    Items_print(items);
    Items_free(items);
}

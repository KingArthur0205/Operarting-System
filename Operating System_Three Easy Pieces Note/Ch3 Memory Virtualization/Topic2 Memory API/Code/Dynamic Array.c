#include <stdlib.h>
#include <stdio.h>

struct Dynamic_Array {
	int *arr;
	int size, capacity;	

	int* (*init) (struct Dynamic_Array* array);
	int* (*push_back) (int val, struct Dynamic_Array* array);
	void (*free_array) (struct Dynamic_Array* array);
};

static int *init(struct Dynamic_Array* array) {
	array->size = 0;
	array->capacity = 1;
	return array->arr = (int*)malloc(sizeof(int));
}

static int *push_back(int val, struct Dynamic_Array* array) {
	array->size += 1;
	if(array->capacity < array->size) {
		array->capacity *= 2;
		array->arr = (int*)realloc(array->arr, sizeof(int) * array->capacity);
	}
	array->arr[array->size - 1] = val;
	return array->arr;
}

static void free_array(struct Dynamic_Array* array) {
	free(array->arr);
}

int main() {
	struct Dynamic_Array array; 
	array.init = init;
	array.push_back = push_back;
	init(&array);
	push_back(3, &array);
	free_array(&array);
	return 0;
}

# Singly-linked list in C.

**Created:** August 8, 2024  
**Author:**  pochtiTolstoy

## What is it?

An implementation of linked list, written in C. 
It stores object data in three primitive data types, pairs and generic pointers.

The list object is a c struct, which is defind in the list.h header file.
You may browse that file for information about list operation functions.

## How to use it?

You may build the linked list source into a static library and include it in your project to give you linked list functionality.

To do so, run 'make release' from the command line th the root directory of the list project. 
After compiling, you will find a `tim_listg.a` file in the `lib` directory of this project.
You may have to configure your project's compiler options
to include the library correctly.

## List struct

The `List` struct type may be used to declare the list. 
The `List` itself can be placed on the stack, but its nodes will be allocated in dynamic memory.
Simple valid program:
```C
#include "tim_listg.h"

List list;
init_list(&list, "d");
push(&list, 100);
free_list(&list);
```
After working with the list, you need to deallocate memory by calling `free_list`.

## Data Types

Note that you should pass the address of the list if you made it on the stack.
Also in `init_list` you should pass `const char*` argument to set element type of list.
* `d` - `int64_t` Decimal.
* `f` - `double`  Real.
* `s` - `char*`   String.
* `p` - `Pair`    Pair.
* `v` - `void*`   Custom data type.

If you are using void pointer, you must be aware of you own data types, and must cast all pointers to data objects as void pointers `(void*)`.

## List Utility Functions

### Node* push(List*, ...);
Takes any data you provide, based on list data type you set earlier. Add a node containing that data after head node of the list.
```C
List list;
init_list(&list, "v");
push(&list, (void*)&car1);
free_list(&list);
```



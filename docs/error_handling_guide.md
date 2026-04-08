## Beginner's Guide to Error Handling in Data Structures

This guide is designed to help you understand error handling, not just memorize it. As a student, you want your code to be robust — meaning it does not crash even when someone uses it incorrectly.

---

## The Mental Model: "Check Before You Step"

Think of your data structure as a house. Memory allocation with `malloc` is like building a new room — you must first confirm you have the land, or memory, available. Pointers are the addresses of those rooms, and `NULL` means the address leads nowhere. You cannot enter a room that does not exist, and you cannot access data through a pointer that points to nothing.

---

## The Three Golden Rules

Every time you write a function, ask yourself three questions before writing any logic:

1. Is it empty? (Can I delete or peek at anything?)
2. Is it full? (Can I insert something new?)
3. Does it exist? (Is the pointer NULL?)

---

## Common Errors and How to Fix Them

### 1. The Memory Full Crash (Heap Overflow)

When you create a new node, the system might not have memory to give you. You must account for that possibility.

**Bad:**
```c
node *temp = malloc(sizeof(node));
temp->data = 10; // Crashes if malloc failed
```

**Good:**
```c
node *temp = malloc(sizeof(node));
if (temp == NULL) {
    printf("Error: Memory Full!\n");
    return;
}
temp->data = 10; // Safe to proceed
```

### 2. The NULL Pointer Dereference

Trying to access data through a `NULL` pointer is the single most common cause of crashes, known as a segmentation fault.

**Bad:**
```c
while (temp->data != target) { // Crashes if temp becomes NULL
    temp = temp->next;
}
```

**Good:**
```c
while (temp != NULL && temp->data != target) {
    temp = temp->next;
}
```

Always check whether the pointer exists before reading from it.

### 3. The Lost Head (Updating the Head Pointer)

When inserting at the beginning or deleting the first node, the head of your list changes. If you forget to update `head`, you either lose track of the new node — causing a memory leak — or you continue referencing a node that has already been freed.

Always explicitly update `head = newItem` when inserting at the start of a list.

### 4. The Off-By-One Error (Array Bounds)

Arrays are zero-indexed. If a structure has a capacity of 5, the valid indices are 0 through 4. A common mistake is writing conditions that exclude the zero index.

**Bad:**
```c
if (top > 0) ... // Misses index 0
```

**Good:**
```c
if (top >= 0) ... // Correctly includes index 0
```

---

## Checklist for Specific Data Structures

**Linked List**
- Insert: Did you handle a `malloc` failure?
- Delete: Is the list empty (`head == NULL`)?
- Delete: Are you deleting the first node? If so, update `head`.
- Delete: Are you deleting the last node? If so, update the tail or the previous node's `next` pointer.
- Traversal: Does your loop stop at `NULL`?

**Stack (Array-based)**
- Push: Is `top == capacity - 1`? That is a stack overflow.
- Pop: Is `top == -1`? That is a stack underflow.

**Queue (Array-based)**
- Enqueue: Is `rear == capacity - 1`?
- Dequeue: Is `front == -1`? The queue is empty.
- Front and rear boundary checks should use `>= 0`, not `> 0`.

---

## Fail Early

A clean habit is to handle all error conditions at the very top of your function, before any real logic begins. This keeps the main body of your code uncluttered and easy to read.

```c
void deleteFirst() {
    // Error check first
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    // Real logic second
    node *temp = head;
    head = head->next;
    free(temp);
}
```

When the error path exits early with a `return`, the rest of the function can be written with the confidence that all preconditions are already satisfied.

### 🟦 Linked List
- [ ] **Insert**: Did I handle `malloc` failure?
- [ ] **Delete**: Is the list empty (`head == NULL`)?
- [ ] **Delete**: Am I deleting the *first* node? (Update head)
- [ ] **Delete**: Am I deleting the *last* node? (Update tail or previous node's next)
- [ ] **Traversal**: Did I stop at `NULL`?

### 🟩 Stack (Array)
- [ ] **Push**: Is `top == capacity - 1`? (Stack Overflow)
- [ ] **Pop**: Is `top == -1`? (Stack Underflow)

### 🟨 Queue (Array)
- [ ] **Enqueue**: Is `rear == capacity - 1`?
- [ ] **Dequeue**: Is `front == -1`? (Empty)
- [ ] **Front/Rear**: Check `>= 0`, not just `> 0`!

---

## 💡 Pro Tip: "Fail Early"
Handle errors at the very top of your function. It makes code cleaner.

```c
void deleteFirst() {
    // 1. Error check FIRST
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    // 2. Real logic SECOND
    node *temp = head;
    head = head->next;
    free(temp);
}
```

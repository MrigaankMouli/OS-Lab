#include <stdio.h>
#include <stdlib.h>

struct mab {
    int offset;
    int size;
    int allocated;
    struct mab *next;
    struct mab *prev;
};

typedef struct mab Mab;
typedef Mab *MabPtr;

MabPtr memChk(MabPtr m, int size) {
    MabPtr current = m;
    while (current) {
        if (!current->allocated && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

MabPtr memSplit(MabPtr m, int size) {
    if (!m || size > m->size) return NULL;

    if (m->size == size) {
        m->allocated = 1;
        return m;
    }

    MabPtr newBlock = (MabPtr) malloc(sizeof(Mab));
    if (!newBlock) {
        perror("malloc failed");
        return NULL;
    }

    newBlock->offset = m->offset + size;
    newBlock->size = m->size - size;
    newBlock->allocated = 0;

    newBlock->next = m->next;
    newBlock->prev = m;

    if (m->next) {
        m->next->prev = newBlock;
    }

    m->next = newBlock;
    m->size = size;
    m->allocated = 1;

    return m;
}

MabPtr memMerge(MabPtr m) {
    if (!m) return NULL;

    while (m->next && !m->allocated && !m->next->allocated) {
        MabPtr nextBlock = m->next;
        m->size += nextBlock->size;
        m->next = nextBlock->next;
        if (nextBlock->next) {
            nextBlock->next->prev = m;
        }
        free(nextBlock);
    }

    return m;
}

MabPtr memAlloc(MabPtr m, int size) {
    MabPtr block = memChk(m, size);
    if (!block) {
        return NULL;
    }
    return memSplit(block, size);
}

MabPtr memFree(MabPtr m) {
    if (!m) return NULL;

    m->allocated = 0;
    if (m->prev && !m->prev->allocated) {
        m = memMerge(m->prev);
    }
    memMerge(m);

    return m;
}

MabPtr createMemory(int size) {
    MabPtr m = (MabPtr) malloc(sizeof(Mab));
    if (!m) {
        perror("malloc failed");
        exit(1);
    }
    m->offset = 0;
    m->size = size;
    m->allocated = 0;
    m->next = NULL;
    m->prev = NULL;
    return m;
}

void printMemory(MabPtr m) {
    printf("Memory Blocks:\n");
    MabPtr current = m;
    while (current) {
        printf("Offset: %d, Size: %d, %s\n", current->offset, current->size,
               current->allocated ? "Allocated" : "Free");
        current = current->next;
    }
    printf("\n");
}

int main() {
    MabPtr memory = createMemory(1000);

    printMemory(memory);

    MabPtr a = memAlloc(memory, 200);
    printMemory(memory);

    MabPtr b = memAlloc(memory, 300);
    printMemory(memory);

    memFree(a);
    printMemory(memory);

    memFree(b);
    printMemory(memory);

    return 0;
}

#include <stdio.h>

struct Segment {
    int base;
    int limit;
};

int convertToPhysical(struct Segment segTable[], int segment, int offset) {
    if (offset >= segTable[segment].limit) {
        printf("Error: Offset %d exceeds limit %d for segment %d\n", offset, segTable[segment].limit, segment);
        return -1;
    }
    return segTable[segment].base + offset;
}

int main() {
    struct Segment segTable[5] = {
        {1400, 1000},   
        {6300, 400},   
        {4300, 400},    
        {3200, 1100},  
        {4700, 5700}    
    };

    int segment, offset, physicalAddress;

    segment = 2; offset = 53;
    physicalAddress = convertToPhysical(segTable, segment, offset);
    if (physicalAddress != -1)
        printf("Physical Address of %d byte of segment %d = %d\n", offset, segment, physicalAddress);

    segment = 3; offset = 852;
    physicalAddress = convertToPhysical(segTable, segment, offset);
    if (physicalAddress != -1)
        printf("Physical Address of %d byte of segment %d = %d\n", offset, segment, physicalAddress);

    segment = 0; offset = 1222;
    physicalAddress = convertToPhysical(segTable, segment, offset);
    if (physicalAddress != -1)
        printf("Physical Address of %d byte of segment %d = %d\n", offset, segment, physicalAddress);

    return 0;
}

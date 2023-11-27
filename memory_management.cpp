#include <bits/stdc++.h>
using namespace std;

class MemoryBlock {
public:
    int size;
    bool allocated;

    MemoryBlock(int s) : size(s), allocated(false) {}
};

class MemoryManager {
private:
    std::vector<MemoryBlock> memoryBlocks;

public:
    void allocateMemory(int requestedSize) {
        auto bestFitBlock = findBestFitBlock(requestedSize);

        if (bestFitBlock != memoryBlocks.end()) {
            bestFitBlock->allocated = true;
            std::cout << "Memory allocated successfully.\n";
        } else {
            std::cout << "Memory allocation failed. No suitable block found.\n";
        }
    }

    void deallocateMemory() {
        // Merge adjacent free blocks
        for (auto it = memoryBlocks.begin(); it != memoryBlocks.end(); ++it) {
            if (it->allocated) {
                auto nextBlock = std::next(it);
                if (nextBlock != memoryBlocks.end() && !nextBlock->allocated) {
                    it->size += nextBlock->size;
                    memoryBlocks.erase(nextBlock);
                    --it; // Revisit the merged block
                }
            }
        }

        // Reset allocation status
        for (auto& block : memoryBlocks) {
            if (block.allocated) {
                block.allocated = false;
            }
        }

        std::cout << "Memory deallocated successfully.\n";
    }

    void displayMemory() const {
        for (const auto& block : memoryBlocks) {
            std::cout << "Block Size: " << block.size << ", Allocated: " << (block.allocated ? "Yes" : "No") << "\n";
        }
        std::cout << "-------------------------\n";
    }

    void addMemoryBlock(int size) {
        memoryBlocks.emplace_back(size);
    }

private:
    std::vector<MemoryBlock>::iterator findBestFitBlock(int requestedSize) {
        auto bestFitBlock = memoryBlocks.end();
        int minBlockSize = INT_MAX;

        for (auto it = memoryBlocks.begin(); it != memoryBlocks.end(); ++it) {
            if (!it->allocated && it->size >= requestedSize && it->size < minBlockSize) {
                minBlockSize = it->size;
                bestFitBlock = it;
            }
        }

        return bestFitBlock;
    }
};

int main() {
    MemoryManager memoryManager;
    memoryManager.addMemoryBlock(20);
    memoryManager.addMemoryBlock(30);
    memoryManager.addMemoryBlock(15);
    std::cout << "Initial Memory State:\n";
    memoryManager.displayMemory();
    memoryManager.allocateMemory(25);
    std::cout << "Updated Memory State:\n";
    memoryManager.displayMemory();
    memoryManager.deallocateMemory();
    std::cout << "Final Memory State:\n";
    memoryManager.displayMemory();

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm> // 用于 std::swap

using namespace std;

// 【核心引擎】分区函数 (Partition)
// 职责：选定基准值，将小于它的扔左边，大于它的扔右边
// 返回：基准值最终所在的索引位置
int partition(vector<int>& nums, int left, int right) {
    // 1. 选基准 (Pivot Selection)
    // 这里的策略是简单的“选最右侧元素”。
    // 工程优化点：可以使用随机数选择 pivot，避免有序数组的最坏情况 O(N^2)
    int pivot = nums[right]; 
    
    int i = left; // i 指向的是“比 pivot 小的区域”的下一个位置

    // 2. 扫描与交换 (Scanning & Swapping)
    for (int j = left; j < right; j++) {
        if (nums[j] < pivot) { // 如果发现比基准小
            swap(nums[i], nums[j]); // 把它扔到左边去 (即 i 的位置)
            i++; // 左边区域扩大
        }
    }

    // 3. 基准归位 (Pivot Placement)
    // 此时，0 到 i-1 都是比 pivot 小的。把 pivot 放到 i 的位置。
    swap(nums[i], nums[right]);
    
    return i; // 返回基准现在的确切索引
}

// 【调度逻辑】快速选择主函数 (Quickselect)
// 职责：根据 pivot 的位置，决定是“命中返回”还是“向左/向右递归”
int quickSelect(vector<int>& nums, int left, int right, int k) {
    if (left >= right) return nums[left];
    
    // 1. 执行分区，获取基准位置
    int p = partition(nums, left, right);

    // 2. 判断逻辑 (剪枝的核心)
    if (p == k) {
        // 命中！当前 p 位置就是我们要找的第 k 个数
        return nums[p];
    } else if (k < p) {
        // 目标在左边，右边的所有数据从此与我无关（剪枝）
        return quickSelect(nums, left, p - 1, k);
    } else {
        // 目标在右边，左边的所有数据从此与我无关（剪枝）
        return quickSelect(nums, p + 1, right, k);
    }
}

// 封装接口，方便调用
int findKthSmallest(vector<int> nums, int k) {
    // k 对应的是索引，如果是找“第 k 小”，通常指索引 k-1
    // 这里我们假设 k 就是索引值
    return quickSelect(nums, 0, nums.size() - 1, k);
}

int main() {
    // 测试用例
    vector<int> data = {3, 2, 1, 5, 6, 4};
    int k = 2; // 我们想找排序后索引为 2 的元素（即第 3 小的数）
               // 排序后应为: [1, 2, 3, 4, 5, 6]，索引 2 的值是 3
    
    cout << "Original array: ";
    for(int n : data) cout << n << " ";
    cout << endl;

    int result = findKthSmallest(data, k);
    
    cout << "The element at index " << k << " (sorted) is: " << result << endl;

    return 0;
}

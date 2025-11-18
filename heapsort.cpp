#include <stdio.h>

// Hàm hoán đổi giá trị 2 số nguyên
void Swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Thủ tục PushDown: Đẩy nút xuống đúng vị trí để tạo Heap
// Logic dựa trên Slide 17 [cite: 291]
void PushDown(int a[], int first, int last) {
    int r = first;

    // Điều kiện lặp: r vẫn còn là nút trong (chưa phải lá)
    // r <= (last - 1) / 2
    while (r <= (last - 1) / 2) {

        // Trường hợp 1: Nút r chỉ có con trái (last == 2*r + 1)
        if (last == 2 * r + 1) {
            // Nếu cha lớn hơn con trái thì đổi chỗ
            if (a[r] > a[last]) {
                Swap(&a[r], &a[last]);
            }
            r = last; // Kết thúc vòng lặp
        }
        // Trường hợp có đủ 2 con
        else {
            // Trường hợp 2: Khóa cha > con trái VÀ con trái <= con phải
            // => Đổi chỗ cha cho con trái (để đẩy số lớn xuống)
            if ((a[r] > a[2 * r + 1]) && (a[2 * r + 1] <= a[2 * r + 2])) {
                Swap(&a[r], &a[2 * r + 1]);
                r = 2 * r + 1;
            }
            // Trường hợp 3: Khóa cha > con phải VÀ con phải < con trái
            // => Đổi chỗ cha cho con phải
            else if ((a[r] > a[2 * r + 2]) && (a[2 * r + 2] < a[2 * r + 1])) {
                Swap(&a[r], &a[2 * r + 2]);
                r = 2 * r + 2;
            }
            // Nếu cha đã nhỏ hơn cả 2 con (đúng vị trí Min-Heap)
            else {
                r = last; // Thoát vòng lặp
            }
        }
    }
}

// Thuật toán HeapSort
// Logic dựa trên Slide 20 [cite: 342]
void HeapSort(int a[], int n) {
    int i;

    // 1. Tạo Heap ban đầu từ mảng (Vun đống)
    // Duyệt từ nút trong cuối cùng (n-2)/2 ngược về gốc a[0]
    for (i = (n - 2) / 2; i >= 0; i--) {
        PushDown(a, i, n - 1);
    }

    // 2. Giai đoạn sắp xếp
    // Hoán đổi phần tử gốc (nhỏ nhất) xuống cuối và vun lại đống
    for (i = n - 1; i >= 2; i--) {
        Swap(&a[0], &a[i]);      // Đưa phần tử nhỏ nhất về vị trí i
        PushDown(a, 0, i - 1);   // Vun đống lại phần còn lại
    }

    // 3. Hoán đổi 2 phần tử cuối cùng (a[0] và a[1])
    Swap(&a[0], &a[1]);
}

// Hàm in mảng
void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    // Dữ liệu test từ bài tập 5 (Slide 54) [cite: 1108]
    int arr[] = {50, 10, 143, 0, 10, 120, 90, 10, 90, 140, 20, 30};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Mang ban dau:\n");
    printArray(arr, n);

    HeapSort(arr, n);

    printf("\nMang sau khi sap xep (Giam dan):\n");
    printArray(arr, n);

    // Kết quả mong đợi giống Slide 55[cite: 1111]:
    // 143 140 120 90 90 50 30 20 10 10 10 0

    return 0;
}

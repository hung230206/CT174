#include <stdio.h>
#include <stdlib.h>

// Cấu trúc lưu thông tin đồ vật
typedef struct {
    char ten[20];
    float trongLuong;
    float giaTri;
    float donGia;
    int soLuong; // Số lượng được chọn trong phương án tốt nhất
} DoVat;

// Biến toàn cục
float GiaLonNhat = 0.0; // Giá trị lớn nhất tạm thời (GLNTT)
float W_balo;           // Trọng lượng tối đa của ba lô
int n;                  // Số lượng loại đồ vật

// Hàm tính đơn giá (Giá trị / Trọng lượng)
void TinhDonGia(DoVat *ds, int n) {
    for (int i = 0; i < n; i++) {
        ds[i].donGia = ds[i].giaTri / ds[i].trongLuong;
    }
}

// Hàm đổi chỗ 2 đồ vật (để sắp xếp)
void Swap(DoVat *a, DoVat *b) {
    DoVat temp = *a;
    *a = *b;
    *b = temp;
}

// Sắp xếp đồ vật theo đơn giá giảm dần (Bubble Sort)
// Theo Slide 29: Sắp xếp theo thứ tự giảm của đơn giá 
void SapXep(DoVat *ds, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ds[i].donGia < ds[j].donGia) {
                Swap(&ds[i], &ds[j]);
            }
        }
    }
}

// Hàm tính cận trên (Upper Bound)
// Công thức Slide 31: CT = TGT + W * DG(Vật kế) [cite: 1795]
float TinhCanTren(float TGT, float W_con_lai, int index, DoVat *ds) {
    if (index >= n) return TGT; // Hết đồ vật
    float donGiaVatKe = ds[index].donGia;
    return TGT + W_con_lai * donGiaVatKe;
}

// Hàm Nhánh cận (Đệ quy)
// index: chỉ số vật đang xét
// TGT: Tổng giá trị hiện tại
// W_con_lai: Trọng lượng còn lại của ba lô
// phuongAnHienTai: mảng lưu số lượng vật đang chọn tạm thời
void NhanhCan(int index, float TGT, float W_con_lai, DoVat *ds, int *phuongAnHienTai) {
    // Tính cận trên tại nút hiện tại
    float CT = TinhCanTren(TGT, W_con_lai, index, ds);

    // Cắt tỉa: Nếu Cận trên <= Giá lớn nhất hiện tại thì cắt nhánh
    // Slide 42: Cắt khi CT <= GLNTT [cite: 2181]
    if (CT <= GiaLonNhat) {
        return;
    }

    // Tính số lượng tối đa vật thứ 'index' có thể chọn
    int soLuongMax = (int)(W_con_lai / ds[index].trongLuong);

    // Duyệt từ soLuongMax về 0 (Ưu tiên nhánh có giá trị cao trước)
    for (int k = soLuongMax; k >= 0; k--) {
        phuongAnHienTai[index] = k;
        float TGT_moi = TGT + k * ds[index].giaTri;
        float W_moi = W_con_lai - k * ds[index].trongLuong;

        if (index == n - 1) { // Đã xét đến vật cuối cùng
            if (TGT_moi > GiaLonNhat) {
                GiaLonNhat = TGT_moi; // Cập nhật GLNTT
                // Lưu phương án tốt nhất vào cấu trúc DoVat
                for (int i = 0; i < n; i++) {
                    ds[i].soLuong = phuongAnHienTai[i];
                }
            }
        } else {
            // Tiếp tục phân nhánh cho vật tiếp theo
            NhanhCan(index + 1, TGT_moi, W_moi, ds, phuongAnHienTai);
        }
    }
}

int main() {
    // Dữ liệu test từ Slide 32 [cite: 1804]
    W_balo = 37.0;
    DoVat ds[] = {
        {"A", 15, 30, 0, 0},
        {"B", 10, 25, 0, 0},
        {"C", 2, 2, 0, 0},
        {"D", 4, 6, 0, 0}
    };
    n = sizeof(ds) / sizeof(ds[0]);

    // Mảng tạm để lưu phương án trong quá trình đệ quy
    int *phuongAnHienTai = (int *)malloc(n * sizeof(int));

    TinhDonGia(ds, n);
    SapXep(ds, n); // Sắp xếp giảm dần theo đơn giá

    printf("=== BAI TOAN CAI BA LO (Branch and Bound) ===\n");
    printf("Trong luong ba lo: %.1f\n", W_balo);
    
    // Bắt đầu thuật toán
    NhanhCan(0, 0, W_balo, ds, phuongAnHienTai);

    printf("\nGia tri lon nhat tim duoc: %.1f\n", GiaLonNhat);
    printf("Phuong an chon (theo thu tu Don gia giam dan):\n");
    for (int i = 0; i < n; i++) {
        if (ds[i].soLuong > 0)
            printf("- Vat %s (TL: %.0f, GT: %.0f): %d cai\n", 
                   ds[i].ten, ds[i].trongLuong, ds[i].giaTri, ds[i].soLuong);
    }

    free(phuongAnHienTai);
    return 0;
}

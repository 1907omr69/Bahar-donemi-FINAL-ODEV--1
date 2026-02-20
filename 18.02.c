#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    TYPE_FLOAT32, 
    TYPE_INT8
} TensorType;

typedef union {
    float* f32_ptr;
    int8_t* i8_ptr;
} TensorData;

typedef struct {
    TensorData data;
    TensorType type;
    int size;
    float scale;
} DynamicTensor;

// Tensör Oluþturma
DynamicTensor* create_tensor(int size, TensorType type) {
    DynamicTensor* t = (DynamicTensor*)malloc(sizeof(DynamicTensor));
    if (!t) return NULL;
    
    t->size = size;
    t->type = type;
    t->scale = 1.0f;

    if (type == TYPE_FLOAT32) {
        t->data.f32_ptr = (float*)malloc(size * sizeof(float));
    } else {
        t->data.i8_ptr = (int8_t*)malloc(size * sizeof(int8_t));
    }
    return t;
}

// Quantization Ýþlemi
void quantize_tensor(DynamicTensor* t) {
    if (t == NULL || t->type != TYPE_FLOAT32) return;

    float* original_float_data = t->data.f32_ptr;
    float max_abs = 0.0f;
    int i;

    // Mutlak deðerce en büyük olaný bul (Doðru Ölçekleme)
    for(i = 0; i < t->size; i++) {
        float val = (original_float_data[i] < 0) ? -original_float_data[i] : original_float_data[i];
        if(val > max_abs) max_abs = val;
    }

    t->scale = (max_abs == 0) ? 1.0f : max_abs / 127.0f;

    int8_t* quantized_data = (int8_t*)malloc(t->size * sizeof(int8_t));
    
    for (i = 0; i < t->size; i++) {
        quantized_data[i] = (int8_t)(original_float_data[i] / t->scale);
    }

    free(original_float_data);
    t->data.i8_ptr = quantized_data;
    t->type = TYPE_INT8;
    
    printf("\n[Sistem] Quantization tamamlandi. Veri i8 formatina donusturuldu.\n");
}

int main() {
    int i;
    int n = 5;
    printf("=== TinyML Tensor Yonetim Simulasyonu ===\n\n");

    // 1. Adým: Float Tensör Oluþtur
    DynamicTensor* myTensor = create_tensor(n, TYPE_FLOAT32);
    if(!myTensor) return 1;

    // Veri giriþi
    myTensor->data.f32_ptr[0] = 12.5f;
    myTensor->data.f32_ptr[1] = -25.0f;
    myTensor->data.f32_ptr[2] = 48.2f;
    myTensor->data.f32_ptr[3] = -5.5f;
    myTensor->data.f32_ptr[4] = 100.0f;

    printf("Orijinal (F32) Veriler: ");
    for (i = 0; i < n; i++) printf("%.1f  ", myTensor->data.f32_ptr[i]);
    printf("\n");

    // 2. Adým: Quantize Et
    quantize_tensor(myTensor);

    // 3. Adým: Sonuçlarý Yazdýr
    printf("Sikistirilmis (I8) Veriler: ");
    for (i = 0; i < n; i++) printf("%d  ", myTensor->data.i8_ptr[i]);
    
    // BURADAKI HATA DUZELTILDI: t->scale yerine myTensor->scale kullanildi
    printf("\n\nOlcme (Scale) Faktoru: %f", myTensor->scale);
    printf("\nDonusturulmus Degerler: ");
    for (i = 0; i < n; i++) printf("%.1f  ", myTensor->data.i8_ptr[i] * myTensor->scale);

    printf("\n\nBellek temizleniyor...\n");
    free(myTensor->data.i8_ptr);
    free(myTensor);
    
    printf("Program sonlandi. Dev-C++ kapatilabilir.\n");
    return 0;
}

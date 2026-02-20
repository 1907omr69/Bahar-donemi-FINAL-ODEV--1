# Bahar-donemi-F-NAL-DEV--1
kısıtlı bellek kaynaklı cihazlarda dinamik tensör yapısı 
# TinyML Dinamik Tensör Yönetimi ve Bellek Optimizasyonu

Bu proje, kaynak kısıtlı gömülü sistemlerde (Arduino, ESP32 vb.) yapay zeka modellerinin çalıştırılabilmesi için geliştirilmiş, **C dilinde ilkel (primitive)** bir tensör yapısı simülasyonudur.

## 🎯 Projenin Amacı
Gömülü sistemlerde RAM oldukça kısıtlıdır. Standart 32-bit (4 byte) float dizileri belleği hızla tüketir. Bu proje, `Union` yapısı kullanarak aynı bellek alanında veriyi hem `float` hem de sıkıştırılmış `int8` (1 byte) olarak tutmayı ve **Quantization (Nicemleme)** tekniği ile bellek kullanımını %75 oranında azaltmayı hedefler.

## 🚀 Teknik Özellikler
* **Dinamik Tip Yönetimi:** `Enum` yapısı ile çalışma anında veri tipi takibi.
* **Bellek Tasarrufu:** C dilindeki `Union` yapısı ile aynı bellek adresinde farklı veri tiplerini barındırma.
* **Symmetric Quantization:** Float verileri $[-127, 127]$ aralığına doğrusal olarak haritalayan ölçekleme algoritması.
* **Dinamik Bellek:** `malloc` ve `free` fonksiyonları ile optimize edilmiş heap yönetimi.

## 🛠️ Kullanılan Teknolojiler ve Yöntemler
* **Programlama Dili:** C
* **IDE:** Dev-C++
* **Geliştirme Yöntemi:** Agentic Kodlama (Yapay zeka modelleri ile iteratif geliştirme süreci).
* **AI Desteği:** Gemini 2.0 Flash üzerinden mimari tasarım ve hata ayıklama desteği alınmıştır.

## 📊 Bellek Karşılaştırması
| Veri Tipi | Boyut (Byte) | RAM Kullanımı (5 Eleman İçin) |
| :--- | :--- | :--- |
| **Float32** | 4 Byte | 20 Byte |
| **Int8 (Quantized)** | 1 Byte | 5 Byte |
| **Tasarruf** | **%75** | **15 Byte Kazanç** |

## 💻 Nasıl Çalıştırılır?
1. `tensor_proje.c` dosyasını indirin.
2. Dev-C++ IDE'si ile dosyayı açın.
3. `F11` (Compile & Run) tuşuna basarak simülasyonu başlatın.
4. Çıktıda verilerin nasıl sıkıştırıldığını ve geri dönüştürüldüğünü gözlemleyin.

## 📺 Sunum İçeriği
Proje videosunda aşağıdaki sorulara yanıt verilmiştir:
- Agentic kodlama süreci nasıl yönetildi?
- Union yapısı bellekte nasıl yer tutar?
- Debugger üzerinde matris/dizi yönetimi nasıl izlenir?
- Quantization algoritması nasıl çalışır?

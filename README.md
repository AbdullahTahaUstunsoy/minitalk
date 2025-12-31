# Minitalk - Simple Client/Server Communication

Bu proje, UNIX sinyalleri (`SIGUSR1` ve `SIGUSR2`) aracılığıyla minimal bir iletişim protokolü oluşturma üzerine kuruludur. Temel amaç, bir mesajın bit seviyesine indirilerek bir işlemden diğerine hatasız bir şekilde iletilmesini sağlamaktır.

---

## Özellikler

- **Sinyal Tabanlı İletişim:** Mesaj iletimi için sadece iki farklı UNIX sinyalinin kullanılması.
- **Hızlı ve Güvenilir:** Verilerin bit bit gönderilip sunucu tarafında yeniden karakterlere (char) dönüştürülmesi.
- **PID Yönetimi:** Sunucunun kendi işlem kimliğini (PID) paylaşması ve istemcinin bu kimlik üzerinden hedefi bulması.
- **Unicode Desteği:** Standart ASCII karakterlerin yanı sıra genişletilmiş karakter setlerinin iletilebilmesi.

---

## Teknik Kazanımlar

Bu proje sürecinde sistem programlama ve düşük seviyeli veri yönetimi konularında şu yetkinlikleri kazandım:
- **Signal Handling:** `sigaction` yapısı kullanarak sinyallerin yakalanması ve özel fonksiyonlarla işlenmesi.
- **Bitwise Operations:** Verinin bit seviyesinde manipülasyonu ve bit kaydırma (shifting) işlemleriyle veri paketleme.
- **Inter-process Communication (IPC):** Süreçler arası iletişimin temelleri ve sinyal senkronizasyonu mantığı.
- **Hata Yönetimi:** Yanlış PID girişi veya iletim sırasındaki veri kayıplarının kontrol edilmesi.

---

## Kurulum ve Kullanım

1. **Depoyu klonlayın:**
   ```bash
   git clone [https://github.com/AbdullahTahaUstunsoy/minitalk.git](https://github.com/AbdullahTahaUstunsoy/minitalk.git)
   cd minitalk
2. Derleme yapın: Terminalde make komutunu çalıştırarak hem sunucu hem de istemci dosyalarını derleyip server ve client yürütülebilir dosyalarını oluşturun.
3. Sunucuyu başlatın: ./server komutuyla sunucuyu çalıştırın ve ekrana yazdırılan PID numarasını not edin.
4. Mesaj gönderin: Başka bir terminal ekranından ./client [PID] [MESAJ] formatını kullanarak (Örn: ./client 1234 "Merhaba") iletişimi başlatın.

# •  **Knapsack Algoritması Nedir? Nasıl Çalışır?**

Knapsack algoritması bir kısıtlı değere karşılık alabileceğiniz maksimum değeri bulmamızı sağlayan bir algoritmadır. 

Örnek vermek gerekirse bir tüccar olduğunuzu düşünün ve aracınızda son kalan 10kg’lık alanı en değerli hangi ürünleri alarak doldurabileceğinizi düşünüyorsunuz. (Bu değer bizim kısıtımızdır.) Almak istediğiniz ürünlerin ise bir ağırlık değerleri ve satış değerleri olsun. Burada amaç çantayı en iyi şekilde (satış değeri fazla) olacak şekilde doldurmaktır.

Örneğimizi biraz daha açacak olursak maksimum taşıma kapasitemiz 10kg idi.  Yani W değerimizi W → 10’dur. 

Ürünlerimizi ise aşağıdaki gibi kabul edelim;

Ürün   →   Değer   →   Ağırlık

A       →     6        →   2

B       →     9        →   3

C       →    10       →   4

D       →    16       →   6

E       →     17       →   8

Bu değerleri baz alarak aşağıdaki tablomuzu oluşturabiliriz. Burada satırlar sırasıyla eklenerek aşağıya doğru ilerler. Örneğin W:2 ağırlığına sahip 3.satırda başka bir nesne yoktur. Fakat bir alt satırda hem W:2 nesnesi hem W:3 nesnesinin olduğunu kabul edilir. Bunun sonucunda toplam ağırlık(W) değeri 5 olduğunda ikisini de alabilirsiniz. Bu yüzden değerleri toplamına eşit olur. (6+9)

|  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Boş | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| W:2 V:6 | 0 | 0 | 6 | 6 | 6 | 6 | 6 | 6 | 6 | 6 | 6 |
| W:3 V:9 | 0 | 0 | 6 | 9 | 9 | 15 | 15 | 15 | 15 | 15 | 15 |
| W:4 V:10 | 0 | 0 | 6 | 9 | 10 | 15 | 16 | 19 | 19 | 19 | 19 |
| W:5 V:16 | 0 | 0 | 6 | 9 | 10 | 15 | 16 | 19 | 22 | 25 | 26 |
| W:6 V:17 | 0 | 0 | 6 | 9 | 10 | 15 | 16 | 19 | 22 | 25 | 26 |

# 📜 Boyut - Zaman Grafikleri

Burada kıyaslama yapabilmek için ms noktasında ölçüm yapan bir sınıf kullandım. Fakat ondalık hassasiyeti nanosaniye desteği bulunmadığı için her listeyi 10 kez tekrarlayarak baz değerler oluşturdum ve kategorilendirdim.

- Bu test sırasında arkaplanda çalışan  herhangi bir uygulama olmadı. Laptop prize takılı bir şekilde işlem gerçekleştirildi..
- Sistem Özelliklerim → I7 11800H İşlemci / 16GB RAM (2366Mhz RAM) / PCI GEN4x0 Samsung SSD

Tabloda gösterilen değerler **milisaniye (ms**) olarak ölçülmüştür. Ölçüm için **time.h kütüphanesi altındaki clock_t fonksiyonu** kullanılmıştır.

<aside>
🚫 İşlemcinin çalışma süresinin nanosaniye zaman ölçümünü Kernel izin vermediği için alamadım.

</aside>

 Bu yüzden buradaki değerlerin min. ve max. değerlerini kabul ederek bir durum tablosu daha oluşturdum. Sıfır hassasiyeti **içerisinde yuvarlama bulunduğu için incelerken dikkate alınız.**

| Dosyadaki Eleman Sayısı | Dosyadan Okuma | Knapsack İşlemi |
| --- | --- | --- |
| 4 | 0 ms | 0 ms |
| 4 | 0 ms | 0 ms |
| 4 | 0 ms | 0 ms |
| 4 | 0 ms | 0 ms |
| 4 | 1 ms | 0 ms |
| 4 | 0 ms | 0 ms |
| 4 | 0 ms | 0 ms |
| 4 | 1 ms | 0 ms |
| 4 | 0 ms | 0 ms |
| 4 | 0 ms | 0 ms |
| 100 | 1 ms | 56 ms |
| 100 | 0 ms | 55 ms |
| 100 | 0 ms | 43 ms |
| 100 | 1 ms | 64 ms |
| 100 | 0 ms | 51 ms |
| 100 | 1 ms | 55 ms |
| 100 | 0 ms | 61 ms |
| 100 | 0 ms | 54 ms |
| 100 | 1 ms | 60 ms |
| 100 | 1 ms | 42 ms |
| 100.000 | 12 ms | 57554 ms |
| 100.000 | 14 ms | 57588 ms |
| 100.000 | 12 ms | 57508 ms |
| 100.000 | 12 ms | 57452 ms |
| 100.000 | 13 ms | 57463 ms |
| 100.000 | 11 ms | 57515 ms |
| 100.000 | 12 ms | 57697 ms |
| 100.000 | 12 ms | 57652 ms |
| 100.000 | 15 ms | 57604 ms |
| 100.000 | 24 ms | 57631 ms |

Tüm durumlar baz alınarak hazırlandığında n sayısını gerçekleşme zamanı baz alırsak çıkan aralıklar;

| Dosyadaki Eleman Sayısı | Dosyadan Okuma | Knapsack İşlemi |
| --- | --- | --- |
| 10 | 0 ms < n ≤ 1 ms | 0 ms < n ≤ 1 ms |
| 100 | 0 ms < n ≤ 1 ms | 42 ms≤ n ≤ 64 ms |
| 100.000 | 11 ms ≤ n ≤ 24ms | 57452 ms ≤ n ≤ 57697 ms |

Aşağıdaki tobla yukarıdaki metrik değerlerin en kötüleri ele alınarak hazırlanmıştır.

![Untitled](https://github.com/KaganCanSit/KnapsackAlgorithm/blob/main/Documantation/OutputPictures/table.png)

# 🧠 Boyut - Zaman Grafiklerinin Yorumu

Knapsack algoritmasının var olan sistem için kullandığımız tablonun en alt satırı için uyarlanmış ve dinamik alan hesabına dayalı bir algortima. Buna dayalı performans değerlerimiz optimize edilmemiş Knapsack algoritmalarına kıyasla kat ve kat iyi bir süre zarfı sağlıyor. Fakat unutmamak gerekir. Knapsack için bellek alanı zarfı çok önemli bir masraf. Şu an için 900MB Process Memory’e sahip olarak işlem yapıyoruz. 9.nesil i7 işlemci ve 2633Mhz RAM, PCI 4.0’ın gücünü görüyoruz.

Fakat Brute Force mantığına kıyasla bakacak olursak algoritmamız gayet iyi performans gösterdi. Optimize edilmeden Knapsack veya Brute Force’a dayalı işlem yapmış olsaydık. 1 saati geçen sürelere ulaşabilirdik.

# 🏆 Knapsack Algoritmasının En İyi ve En Kötü Zaman Karmaşıkları Nedir?

Knapsack Algoritmasının zaman karmaşıklığı O(n*W) ile ölçülür. Bu sebeple algoritmamız “Çanta Büyüklüğü ve Eleman Sayısı” ile bağıntılıdır. Her ağırlık elemanına gelince, tüm ağırlık kapasiteleri 1<=w<=W arasında dolaşıyoruz.

Bellek Karmaşıklığı temel Knapsack Algoritmalarında 2 boyutlu dizi kullanımı bulunduğu için “N*W” seviyesindedir. Fakat biz çözümümüzde tek boyutlu dizi kullanıyoruz. Değerleri üstüne ekleyerek gidiyoruz. Bu yüzden değerimiz “W” ile kısıtlıdır.

# 😢 Knapsack Algoritmasının En İyi ve En Kötü Çalışma Zamanı Hangi Durumlarda Oluşur?

Her iki durum için elimizde olan kilit veriler çanta büyüklüğü ve eleman sayısıdır. Bu değerler doğrultusunda durum belirlenir. En iyi durum n değeri veya W değerinin 1 gibi değerlere sahip olmasıdır. (Değerlerin ortak yakınlık yerine birinin küçük diğerinin büyük olması daha idealdir. Taranacak alanı azaltır.)

En kötü durum ise her ikisinin de en büyük olduğu durumdur. Örneğin 25/25 → 10/30’dan kötü performans verecektir.

Kanıtlayacak olursak;

O(n*W) → 25 x 25 → 625

O(n*W) → 10 x 30 → 300

---
# Birinci Dosya (4)
![Untitled](https://github.com/KaganCanSit/KnapsackAlgorithm/blob/main/Documantation/OutputPictures/4-19.jpg)

# İkinci Dosya (100)
![Untitled](https://github.com/KaganCanSit/KnapsackAlgorithm/blob/main/Documantation/OutputPictures/100-99837.jpg)

# Üçüncü  Dosya (100.000)
![Untitled](https://github.com/KaganCanSit/KnapsackAlgorithm/blob/main/Documantation/OutputPictures/100000-1099893.jpg)

<aside> 📌 Kaynakça: </aside>

Ders Notları

[0-1 Knapsack Problem | DP-10 - GeeksforGeeks](https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/)

[Knapsack Problem solving problems on Dynamic](https://medium.com/analytics-vidhya/knapsack-problem-7f05d0900db8)

[Veri Türü Aralıkları | Microsoft Docs](https://docs.microsoft.com/tr-tr/cpp/cpp/data-type-ranges?view=msvc-170)

[visual studio - C++ - array type 'unsigned __int64 [amount*]' is not assignable - Stack Overflow](https://stackoverflow.com/questions/34484034/c-array-type-unsigned-int64-amount-is-not-assignable)

[c++ array - expression must have a constant value - Stack Overflow](https://stackoverflow.com/questions/9219712/c-array-expression-must-have-a-constant-value)

[new operator - How do you 'realloc' in C++? - Stack Overflow](https://stackoverflow.com/questions/3482941/how-do-you-realloc-in-c)

[c++ - x = malloc(n * sizeof (int)); cannot convert void to int - Stack Overflow](https://stackoverflow.com/questions/43337761/x-mallocn-sizeof-int-cannot-convert-void-to-int)

[visual studio - ERROR: Cannot open source file " " - Stack Overflow](https://stackoverflow.com/questions/9753887/error-cannot-open-source-file)

[Knapsack-Problem/Q1-3_dynamic_programming_knapsack.c at master · ambarmodi/Knapsack-Problem (github.com)](https://github.com/ambarmodi/Knapsack-Problem/blob/master/Q1-3_dynamic_programming_knapsack.c)

[c++ - Function exceeds stack size, consider moving some data to heap (C6262) - Stack Overflow](https://stackoverflow.com/questions/58477291/function-exceeds-stack-size-consider-moving-some-data-to-heap-c6262)

<aside>
📌 Hazırlayan: Kağan Can Şit
</aside>

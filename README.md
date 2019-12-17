# DNA Sequence Mapping With Needleman Wunsch Algorithm
  
  Her biri 200 baz uzunluğunda 5K, 10K ve 15K sayıda sekansları içeren dosyalardan ilgili sekanslar elde edildikten sonra her bir sekans diğer tüm sekanslarla Needleman Wunsch algoritması kullanılarak karşılaştırılır. 
  Bu karşılaştırmalar sonucunda elde edilen skor değerlerinden maksimum 20 tanesi yeni bir dosyaya bu skorların ait olduğu sekans değerleri ile beraber yazdırılır.
  
  Büyük veriler üzerinde çalıştığımız için alışılagelmiş olarak kodumuzu seri yapıda yazıp çalıştırdığımızda bir hayli uzun sürüyor. Örneğin 5K sekans içeren dosyamızı okuyup bu sekansları ilgili algoritma ile 
  karşılaştırıp sonuç üretmemiz kodumuzu seri bir şekilde çalıştırdığımızda yaklaşık olarak 2 saat 40 dakika falan sürmekte ve bu pek de istenen bir durum olmamaktadır. Bu sorunu gidermek amacıyla kodumuzu paralelleştirilebilecek şekilde yazıp 
  parallelleştirme işlemlerini yaparak, yani iş yükünü birden çok threadlere dağıtarak işlemimizi hızlandırabiliriz.
  
  C++ tabanlı çalışan paralelleştirme yapılarından biri olan OpenMP kütüphanesini DEV-C++ IDE'si aracılığıyla kullanabilmek için bazı ayarlar yapmamız gerekiyor. DEV-C++ açıldıktan sonra menüden **"Tools->Compiler Options"** seçeneği seçilerek compiler ayarlarında **"Add the following commands when calling the compiler"** seçeneği aktifleştirilir ve hemen altındaki metin kutusuna **"-fopenmp"** ifadesi eklenir:
  
  ![Settings For DEV-C++](https://github.com/zumrudu-anka/NeedlemanWunschAlgorithmWithOpenMP/blob/master/Images/ForSettings.png)
  
  ![Needleman Wunsch Algoritması](Needleman Wunsch Algoritması için:
http://bilgisayarkavramlari.sadievrenseker.com/2012/06/05/needleman-wunsch-algoritmasi/)

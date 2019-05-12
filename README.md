# DNA Sequence Mapping With Needleman Wunsch Algorithm
  
  Projemizde her biri 200 baz uzunluğunda 5K, 10K ve 15K sayıda sekansları içeren dosyalardan ilgili sekanslar elde edildikten sonra her bir sekans diğer tüm sekanslarla Needleman Wunsch algoritması kullanılarak karşılaştırılır. 
  Bu karşılaştırmalar sonucunda elde edilen skor değerlerinden maksimum 20 tanesi yeni bir dosyaya bu skorların ait olduğu sekans değerleri ile beraber yazdırılır.
  
  Projemizde büyük veriler üzerinde çalıştığımız için alışılagelmiş olarak kodumuzu seri yapıda yazıp çalıştırdığımızda bir hayli uzun sürüyor. Örneğin 5K sekans içeren dosyamızı okuyup bu sekansları ilgili algoritma ile 
  karşılaştırıp sonuç üretmemiz kodumuzu seri bir şekilde çalıştırdığımızda yaklaşık olarak 2 saat 40 dakika falan sürmekte ve bu pek de istenen bir durum olmamaktadır. Bu sorunu gidermek amacıyla kodumuzu paralelleştirilebilecek şekilde yazıp 
  parallelleştirme işlemlerini yaparak, yani iş yükünü birden çok threadlere dağıtarak işlemimizi hızlandırabiliriz.
  
  <pre>
	Bu algoritmayı C++ dilini kullanarak gerçeklediğim için C++ tabanlı çalışan OpenMP kütüphanesini kullandım. IDE olarak Dev-C++ tercih ettim. Bu IDE aracılığıyla OpenMP yapısını kullanabilmek için Dev-C++ açıldıktan sonra menüden 
	**"Tools->Compiler Options"** seçeneği seçilerek compiler ayarlarında **"Add the following commands when calling the compiler"** seçeneği aktifleştirilir ve hemen altındaki metin kutusuna **"-fopenmp"** ifadesi eklenir:
  </pre>
  
  ![Settings For Dev-C++](https://github.com/zumrudu-anka/NeedlemanWunschAlgorithmWithOpenMP/blob/master/Images/ForSettings.png)
  
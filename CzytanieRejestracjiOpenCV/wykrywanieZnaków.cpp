
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

//zmienne globalne

cv::Ptr<cv::ml::KNearest> kNearest = cv::ml::KNearest::create();

//

bool AlgorytmKNN(void) {

	cv::Mat matKlasyfikacjaInts;   //bêdziemy czytaæ numery klasyfikacyjne do tej zmiennej, jakby to by³ wektor

	cv::FileStorage fsKlasyfikacja("classifications.xml", cv::FileStorage::READ);

	if (fsKlasyfikacja.isOpened() == false) {                                                         //Je¿eli plik nie zostanie poprawnie otwarty
		std::cout << "B³¹d , niemo¿na otwo¿yæ pliku classifications , wy³¹czanie programu\n\n\n";     //Zostanie wyœwietlony nastêpuj¹cy b³¹d
		return(false);                                                                                //Program zostanie wy³¹czony
	}       
    
	fsKlasyfikacja["classifications"] >> matKlasyfikacjaInts;     //Przeczytaæ rozdzia³ klasyfikacji w zmiennej Mat
	fsKlasyfikacja.release();                                     //Zamykanie kliku classifications

	//Czytanie obrazów szkoleniowych

	cv::Mat matTrainingImagesAsFlattenedFloats;          //bêdziemy czytaæ wiele obrazów w tej zmiennej pojedynczego obrazu, jakby to by³ wektor

	cv::FileStorage fsSzkolenieObrazu("images.xml", cv::FileStorage::READ);   //otworzyæ plik zdjêæ szkoleniowych

	if (fsSzkolenieObrazu.isOpened() == false) {
		std::cout << "B³¹d , niemo¿na otwo¿yæ pliku images , wy³¹czanie programu\n\n\n";
		return(false);
	}

	fsSzkolenieObrazu["images"] >> matTrainingImagesAsFlattenedFloats;
}

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

//zmienne globalne

cv::Ptr<cv::ml::KNearest> kNearest = cv::ml::KNearest::create();

//

bool AlgorytmKNN(void) {

	cv::Mat matKlasyfikacjaInts;   //b�dziemy czyta� numery klasyfikacyjne do tej zmiennej, jakby to by� wektor

	cv::FileStorage fsKlasyfikacja("classifications.xml", cv::FileStorage::READ);

	if (fsKlasyfikacja.isOpened() == false) {                                                         //Je�eli plik nie zostanie poprawnie otwarty
		std::cout << "B��d , niemo�na otwo�y� pliku classifications , wy��czanie programu\n\n\n";     //Zostanie wy�wietlony nast�puj�cy b��d
		return(false);                                                                                //Program zostanie wy��czony
	}       
    
	fsKlasyfikacja["classifications"] >> matKlasyfikacjaInts;     //Przeczyta� rozdzia� klasyfikacji w zmiennej Mat
	fsKlasyfikacja.release();                                     //Zamykanie kliku classifications

	//Czytanie obraz�w szkoleniowych

	cv::Mat matTrainingImagesAsFlattenedFloats;          //b�dziemy czyta� wiele obraz�w w tej zmiennej pojedynczego obrazu, jakby to by� wektor

	cv::FileStorage fsSzkolenieObrazu("images.xml", cv::FileStorage::READ);   //otworzy� plik zdj�� szkoleniowych

	if (fsSzkolenieObrazu.isOpened() == false) {
		std::cout << "B��d , niemo�na otwo�y� pliku images , wy��czanie programu\n\n\n";
		return(false);
	}

	fsSzkolenieObrazu["images"] >> matTrainingImagesAsFlattenedFloats;
}
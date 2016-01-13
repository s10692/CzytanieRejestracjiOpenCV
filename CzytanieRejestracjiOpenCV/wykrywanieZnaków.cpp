
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

	fsSzkolenieObrazu["images"] >> matTrainingImagesAsFlattenedFloats;  //odcinek do odczytu zdjêæ Mat obrazów treningowych zmiennej

	fsSzkolenieObrazu.release();                                      //zamykanie pliku

	//Koniec Czytania obrazów szkoleniowych

	     //W koñcu docieramy do wezwania do poci¹gu, nale¿y pamiêtaæ, ¿e oba parametry musz¹ byæ typu Mat
		// Nawet jeœli w rzeczywistoœci s¹ one wieloma obrazkami / liczbami

	kNearest->setDefaultK(1);

	kNearest->train(matTrainingImagesAsFlattenedFloats, cv::ml::ROW_SAMPLE, matKlasyfikacjaInts);

	return true;
}

//Koniec algorytmu KNN

std::vector<Rejestracje> znajdzZnakiwTablicy(std::vector<Rejestracje> &vectorRejestracji) {
	int intLicznikRejestracji = 0;   //tylko do zobaczenia postêpu Szukania Znaków
	cv::Mat imgKontury;
	cv::RNG rng;

	if (vectorRejestracji.empty()) {
		return(vectorRejestracji);
	}
	//W tym momencie mo¿emy byæ pewni, wektor mo¿liwych p³yt ma co najmniej jedn¹ p³ytê

	for (auto &Rejestracje : vectorRejestracji) {

		preprocess(Rejestracje.imgRejestacja, Rejestracje.imgOdcienieSzarosci, Rejestracje.imgObcinanie);

		if (blnWidziKroki) {
			cv::imWidzi("5a", Rejestracje.imgRejestracja);
			cv::imWidzi("5b"), Rejestracje.imgOdcienieSzarosci);
			cv::imWidzi("5c"), Rejestracje.imgObcinanie);
		}

		//zwiêkszenie wielkoœci rejestracji zdjêcia w celu ³atwiejszego ogl¹dania i wykrywania znaków
		cv::resize(Rejestracje.imgObcinanie, Rejestracje.imgObcinanie, cv::Size(), 1.6, 1.6);

	}

}
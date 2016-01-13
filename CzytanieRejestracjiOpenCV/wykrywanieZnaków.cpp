
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

	fsSzkolenieObrazu["images"] >> matTrainingImagesAsFlattenedFloats;  //odcinek do odczytu zdj�� Mat obraz�w treningowych zmiennej

	fsSzkolenieObrazu.release();                                      //zamykanie pliku

	//Koniec Czytania obraz�w szkoleniowych

	     //W ko�cu docieramy do wezwania do poci�gu, nale�y pami�ta�, �e oba parametry musz� by� typu Mat
		// Nawet je�li w rzeczywisto�ci s� one wieloma obrazkami / liczbami

	kNearest->setDefaultK(1);

	kNearest->train(matTrainingImagesAsFlattenedFloats, cv::ml::ROW_SAMPLE, matKlasyfikacjaInts);

	return true;
}

//Koniec algorytmu KNN

std::vector<Rejestracje> znajdzZnakiwTablicy(std::vector<Rejestracje> &vectorRejestracji) {
	int intLicznikRejestracji = 0;   //tylko do zobaczenia post�pu Szukania Znak�w
	cv::Mat imgKontury;
	cv::RNG rng;

	if (vectorRejestracji.empty()) {
		return(vectorRejestracji);
	}
	//W tym momencie mo�emy by� pewni, wektor mo�liwych p�yt ma co najmniej jedn� p�yt�

	for (auto &Rejestracje : vectorRejestracji) {

		preprocess(Rejestracje.imgRejestacja, Rejestracje.imgOdcienieSzarosci, Rejestracje.imgObcinanie);

		if (blnWidziKroki) {
			cv::imWidzi("5a", Rejestracje.imgRejestracja);
			cv::imWidzi("5b"), Rejestracje.imgOdcienieSzarosci);
			cv::imWidzi("5c"), Rejestracje.imgObcinanie);
		}

		//zwi�kszenie wielko�ci rejestracji zdj�cia w celu �atwiejszego ogl�dania i wykrywania znak�w
		cv::resize(Rejestracje.imgObcinanie, Rejestracje.imgObcinanie, cv::Size(), 1.6, 1.6);

	}

}
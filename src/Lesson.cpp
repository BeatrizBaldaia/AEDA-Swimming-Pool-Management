#include "Lesson.h"
#include "Class.h"

Lesson::Lesson(DayOfWeek d, Modality m){
	day = d;
	modality = m;
	//adicionar um metodo que atribui um professor a aula avaliando as condições necessárias para a escolha do professor
}
string Lesson::getTeacher() const{
	return teacher->getName();
}

void Lesson::DayDisplay() const{
	switch (day){
	case MON : cout << "Monday"; break;
	case TUE : cout << "Tuesday"; break;
	case WED : cout << "Wednesday"; break;
	case THU : cout << "Thursday"; break;
	case FRI : cout << "Friday"; break;
	case SAT : cout << "Saturday"; break;
	case SUN : cout << "Sunday"; break;
	}
}

void Lesson::ModalityDisplay() const{
	switch (modality){
	case HydroGym : cout << "Hydrogymnastic"; break;
	case Zumba : cout << "Aqua Zumba"; break;
	case AquaticPolo : cout << "Water Polo"; break;
	case ArtisticSwimming : cout << "Synchronised Swimming"; break;
	case CompetitiveSwimming : cout << "Competitive Swimming"; break;
	case Learning : cout << "Learning Techniques"; break;
	}
}





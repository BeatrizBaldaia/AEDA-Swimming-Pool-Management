#pragma once

#include <utility>
#include "Date.h"

typedef pair <DayOfWeek, Time> ClassTime;

enum Modality {
	HydroGym, Zumba, AquaticPolo, ArtisticSwimming, CompetitiveSwimming, Learning
};

class Class {
	Modality modality;
	vector <ClassTime> schedule;
};

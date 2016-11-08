#ifndef _POOLUSE_H_
#define _POOLUSE_H_

#include "Date.h"
#include "Lesson.h"

class PoolUse {
public:
<<<<<<< HEAD
	PoolUse(Date d, Time t, unsigned int dur);
	Time getTime() const;
	Date getDate() const;
	virtual float getCost() const = 0;
	Lesson * getLesson() const = 0;
=======
    PoolUse(Date d, Time t, unsigned int dur);
    Time getTime() const;
    Date getDate() const;
    virtual float getCost() const = 0;
>>>>>>> origin/master
protected:
    Date date;
    Time time;
    unsigned int duration;
};

class FreeSwimUse : public PoolUse {
public:
<<<<<<< HEAD
	FreeSwimUse (Date d, Time t, unsigned int dur);
	float getCost() const;
	Time getTime() const;
	Date getDate() const;
	Lesson * getLesson() const;
=======
    FreeSwimUse (Date d, Time t, unsigned int dur);
    float getCost() const;
    Time getTime() const;
    Date getDate() const;
>>>>>>> origin/master
private:
    static float cost30;
};

class LessonUse : public PoolUse {
public:
    LessonUse (Date d, Time t, Lesson *l); //duração sempre 1 hora
    float getCost() const;
    Lesson * getLesson() const;
    Time getTime() const;
    Date getDate() const;
private:
    Lesson * lesson;

    static float lessonCost;
};
#else
class PoolUse;
class LessonUse;

#endif

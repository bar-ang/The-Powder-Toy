#include <iostream>

#ifndef EYE_H_
#define EYE_H_

#define MAX_EYES 100
#define MAX_EYE_SIZE 100
struct eyest
{
	int x;
	int y;
	int size;
	// The pupil location is defined using radial coordinates
	// That is, the distance from the center of the eye and angle with the x-asix.
	int pup_dist;
	float pup_rot;
	int pup_size;
	bool visible;
	int spawnID;
	int lookAt;
	std::vector<int> eye_parts;
};

void pupil_look_to_point(eyest *eye, float x, float y);

#endif


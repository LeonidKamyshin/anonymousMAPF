#ifndef ANONYMOUSMAPF_CONSTRAINT_H
#define ANONYMOUSMAPF_CONSTRAINT_H

struct Constraint {
    const int x, y, timestep;

    Constraint(int _x, int _y, int _timestep);
};
#endif //ANONYMOUSMAPF_CONSTRAINT_H
#ifndef FORCE_H_INCLUDED
#define FORCE_H_INCLUDED

class Force{

    private:

        //Force Properties
        float magnitude;
        float angle;

        //Duration Info
        int initTime;       //Ticks
        int duration;       //Frames

    public:

        Force( float nmagnitude, float nangle, int nduration );
        float Magnitude();
        float Angle();
        int InitTime();
        int Duration();

};

#endif // FORCE_H_INCLUDED

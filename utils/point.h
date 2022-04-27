#ifndef _POINT_H_
#define _POINT_H_

class Point{
    private:
        float x, y, z;

    public:
        Point(){
            x = 0;
            y = 0;
            z = 0;
        }

        Point(float a, float b, float c){
            x = a;
            y = b;
            z = c;
        }

        float getX();
        float getY();
        float getZ();
        void setX(float);
        void setY(float);
        void setZ(float);
};

#endif
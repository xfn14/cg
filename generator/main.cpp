#include "main.h"

void plane(float units, int divisions, string filename){
    Model model;   
    float x, z, div, divt;
    z = x = -(units/2);
    div = units / (float) divisions;
    divt = (float) 1 / divisions;


    for (int i=0; i<divisions; i++){
        for(int j=0; j<divisions; j++){
            Patch patch;

            patch.addPoint(*(new Point(x + (float) j*div, 0, z + (float) i*div)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, 0, z + (float) (i+1)*div)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, 0, z + (float) i*div)));

            /*
            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));

            texture.push_back(new Point(j*divt, 1-i*divt, 0));
            texture.push_back(new Point((j+1)*divt, 1-(i+1)*divt, 0));
            texture.push_back(new Point((j+1)*divt, 1-i*divt, 0));
             */

            patch.addPoint(*(new Point(x + (float) j*div, 0, z + (float) i*div)));
            patch.addPoint(*(new Point(x + (float) j*div, 0, z + (float) (i+1)*div)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, 0, z + (float) (i+1)*div)));

            /*
            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));

            texture.push_back(new Point(j*divt, 1-i*divt, 0));
            texture.push_back(new Point(j*divt, 1-(i+1)*divt, 0));
            texture.push_back(new Point((j+1)*divt, 1-(i+1)*divt, 0));
            */


            model.addPatch(patch);
        }
    }
    model.writeToFile(filename);
}

void box(float units, int grid, string filename){
    Model model;
    float x, y, z, div, divx, divy;
    x = y = z = - units/2;
    div = units/(float) grid;
    divx =  (float) 0.25 / (float) grid;
    divy = (float)0.33 /(float)grid;

    for (int i=0; i < grid; i++){
        for(int j=0; j < grid; j++){
            Patch patch;
            //face de cima
            patch.addPoint(*(new Point(x + (float) (j+1)*div, -y, z + (float) (i+1)*div)));
            patch.addPoint(*(new Point(x + (float) j*div, -y, z + (float) i*div)));
            patch.addPoint(*(new Point(x + (float) j*div, -y, z + (float) (i+1)*div)));

            /*
            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));

            texture.push_back(new Point(0.25+(j+1)*divx, 1-(i+1)*divy, 0));
            texture.push_back(new Point(0.25+j*divx, 1-i*divy, 0));
            texture.push_back(new Point(0.25+j*divx, 1-(i+1)*divy, 0));
             */

            patch.addPoint(*(new Point(x + (float) (j+1)*div, -y, z + (float) (i+1)*div)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, -y, z + (float) i*div)));
            patch.addPoint(*(new Point(x + (float) j*div, -y, z + (float) i*div)));

            /*
            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));

            texture.push_back(new Point(0.25+(j+1)*divx, 1-(i+1)*divy, 0));
            texture.push_back(new Point(0.25+(j+1)*divx, 1-i*divy, 0));
            texture.push_back(new Point(0.25+j*divx, 1-i*divy, 0));
             */

            //face de baixo
            patch.addPoint(*(new Point(x + (float) j*div, y, z + (float) i*div)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y, z + (float) (i+1)*div)));
            patch.addPoint(*(new Point(x + (float) j*div, y, z + (float) (i+1)*div)));

            /*
            normal.push_back(new Point(0, -1, 0));
            normal.push_back(new Point(0, -1, 0));
            normal.push_back(new Point(0, -1, 0));

            texture.push_back(new Point(0.25+j*divx, 0.33-i*divy, 0));
            texture.push_back(new Point(0.25+(j+1)*divx, 0.33-(i+1)*divy, 0));
            texture.push_back(new Point(0.25+j*divx, 0.33-(i+1)*divy, 0));
             */

            patch.addPoint(*(new Point(x + (float) (j+1)*div, y, z + (float) (i+1)*div)));
            patch.addPoint(*(new Point(x + (float) j*div, y, z + (float) i*div)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y, z + (float) i*div)));

            /*
            normal.push_back(new Point(0, -1, 0));
            normal.push_back(new Point(0, -1, 0));
            normal.push_back(new Point(0, -1, 0));

            texture.push_back(new Point(0.25+(j+1)*divx, 0.33-(i+1)*divy, 0));
            texture.push_back(new Point(0.25+j*divx, 0.33-i*divy, 0));
            texture.push_back(new Point(0.25+(j+1)*divx, 0.33-i*divy, 0));
             */

            //face lateral -x
            patch.addPoint(*(new Point(x , y + (float) i*div, z + (float) j*div)));
            patch.addPoint(*(new Point(x , y + (float) (i+1)*div, z + (float) (j+1)*div)));
            patch.addPoint(*(new Point(x , y + (float) (i+1)*div, z + (float) j*div)));

            /*
            normal.push_back(new Point(-1, 0, 0));
            normal.push_back(new Point(-1, 0, 0));
            normal.push_back(new Point(-1, 0, 0));

            texture.push_back(new Point(j*divx, 0.66-i*divy, 0));
            texture.push_back(new Point((j+1)*divx, 0.66-(i+1)*divy, 0));
            texture.push_back(new Point(j*divx, 0.66-(i+1)*divy, 0));
             */

            patch.addPoint(*(new Point(x , y + (float) (i+1)*div, z + (float) (j+1)*div)));
            patch.addPoint(*(new Point(x , y + (float) i*div, z + (float) j*div)));
            patch.addPoint(*(new Point(x , y + (float) i*div, z + (float) (j+1)*div)));

            /*
            normal.push_back(new Point(-1, 0, 0));
            normal.push_back(new Point(-1, 0, 0));
            normal.push_back(new Point(-1, 0, 0));

             texture.push_back(new Point((j+1)*divx, 0.66-(i+1)*divy, 0));
            texture.push_back(new Point(j*divx, 0.66-i*divy, 0));
            texture.push_back(new Point((j+1)*divx, 0.66-i*divy, 0));
             */

            //face lateral x
            patch.addPoint(*(new Point(-x, y + (float) i*div, z + (float) j*div )));
            patch.addPoint(*(new Point(-x, y + (float) (i+1)*div, z + (float) j*div)));
            patch.addPoint(*(new Point(-x, y + (float) (i+1)*div, z + (float) (j+1)*div)));

            /*
            normal.push_back(new Point(1, 0, 0));
            normal.push_back(new Point(1, 0, 0));
            normal.push_back(new Point(1, 0, 0));

             texture.push_back(new Point(0.5+j*divx, 0.66-i*divy, 0));
            texture.push_back(new Point(0.5+j*divx, 0.66-(i+1)*divy, 0));
            texture.push_back(new Point(0.5+(j+1)*divx, 0.66-(i+1)*divy, 0));
             */

            patch.addPoint(*(new Point(-x, y + (float) (i+1)*div, z + (float) (j+1)*div)));
            patch.addPoint(*(new Point(-x, y + (float) i*div, z + (float) (j+1)*div)));
            patch.addPoint(*(new Point(-x, y + (float) i*div, z + (float) j*div)));

            /*
            normal.push_back(new Point(1, 0, 0));
            normal.push_back(new Point(1, 0, 0));
            normal.push_back(new Point(1, 0, 0));

            texture.push_back(new Point(0.5+(j+1)*divx, 0.66-(i+1)*divy, 0));
            texture.push_back(new Point(0.5+(j+1)*divx, 0.66-i*divy, 0));
            texture.push_back(new Point(0.5+j*divx, 0.66-i*divy, 0));
             */

            //face lateral z
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) (i+1)*div, -z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) i*div, -z)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) i*div, -z)));

            /*
            normal.push_back(new Point(0, 0, 1));
            normal.push_back(new Point(0, 0, 1));
            normal.push_back(new Point(0, 0, 1));

             texture.push_back(new Point(0.25+(j+1)*divx, 0.66-(i+1)*divy, 0));
            texture.push_back(new Point(0.25+j*divx, 0.66-i*divy, 0));
            texture.push_back(new Point(0.25+(j+1)*divx, 0.66-i*divy, 0));
             */

            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) (i+1)*div, -z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) (i+1)*div, -z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) i*div, -z)));

            /*
            normal.push_back(new Point(0, 0, 1));
            normal.push_back(new Point(0, 0, 1));
            normal.push_back(new Point(0, 0, 1));

             texture.push_back(new Point(0.25+(j+1)*divx, 0.66-(i+1)*divy, 0));
            texture.push_back(new Point(0.25+j*divx, 0.66-(i+1)*divy, 0));
            texture.push_back(new Point(0.25+j*divx, 0.66-i*divy, 0));
             */

            //face lateral -z
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) i*div, z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) (i+1)*div, z)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) (i+1)*div, z)));

            /*
            normal.push_back(new Point(0, 0, -1));
            normal.push_back(new Point(0, 0, -1));
            normal.push_back(new Point(0, 0, -1));

             texture.push_back(new Point(0.75+j*divx, 0.66-i*divy, 0));
            texture.push_back(new Point(0.75+j*divx, 0.66-(i+1)*divy, 0));
            texture.push_back(new Point(0.75+(j+1)*divx, 0.66-(i+1)*divy, 0));
             */

            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) (i+1)*div, z)));
            patch.addPoint(*(new Point(x + (float) (j+1)*div, y + (float) i*div, z)));
            patch.addPoint(*(new Point(x + (float) j*div, y + (float) i*div, z)));

            /*
            normal.push_back(new Point(0, 0, -1));
            normal.push_back(new Point(0, 0, -1));
            normal.push_back(new Point(0, 0, -1));

             texture.push_back(new Point(0.75+(j+1)*divx, 0.66-(i+1)*divy, 0));
            texture.push_back(new Point(0.75+(j+1)*divx, 0.66-i*divy, 0));
            texture.push_back(new Point(0.75+j*divx, 0.66-i*divy, 0));
             */

            model.addPatch(patch);

        }
    }
    model.writeToFile(filename);

}

void cone(float radius, float height, int slices, int stacks, string filename){
    Model model;
    float deltah = (2.0f*(float)M_PI/(float)slices), deltav = height/(float) stacks, deltaRaio = radius/(float) stacks;
    float y=height;
    float  alturaS,alturaS2;

    for(int j=0; j<stacks; j++){
        for(int i=0; i<slices; i++){
            float angle1 = (float) i * deltah, angle2 = (float) (i + 1) * deltah;
            Patch patch;
            if(j == 0) {
                //base
                patch.addPoint(*(new Point(0.0f, 0.0f, 0.0f)));
                patch.addPoint(*(new Point(radius * sinf(angle2), 0.0f, radius * cosf(angle2))));
                patch.addPoint(*(new Point(radius * sinf(angle1), 0.0f, radius * cosf(angle1))));

                /*
                normal.push_back(new Point(0, -1, 0));
                normal.push_back(new Point(0, -1, 0));
                normal.push_back(new Point(0, -1, 0));

                texture.push_back(new Point(0.5, 0, 0));
                texture.push_back(new Point(1, 1, 0));
                texture.push_back(new Point(0, 1, 0));
                */
            }
            //laterais
            float raioStack1 = radius - (float) j * deltaRaio;
            float raioStack2 = radius - (float) (j+1) * deltaRaio;
            alturaS = (float) j * deltav;
            alturaS2 =  (float) (j+1) * deltav;
            float textv = (float) 1 / (float) stacks, texth = (float) 1 / (float) slices;
            if (j < stacks-1) {
                patch.addPoint(*(new Point(raioStack1 * sinf(angle1), alturaS, raioStack1 * cosf(angle1))));
                patch.addPoint(*(new Point(raioStack1 * sinf(angle2), alturaS, raioStack1 * cosf(angle2))));
                patch.addPoint(*(new Point(raioStack2 * sinf(angle1), alturaS2, raioStack2 * cosf(angle1))));

                /*
                normal.push_back(new Point(sinf(angle1), deltav, cosf(angle1)));
                normal.push_back(new Point(sinf(angle2), deltav, cosf(angle2)));
                normal.push_back(new Point(sinf(angle1), deltav, cosf(angle1)));

                 texture.push_back(new Point(i*texth, j*textv, 0));
                texture.push_back(new Point((i+1)*texth, j*textv, 0));
                texture.push_back(new Point(i*texth, (j+1)*textv, 0));
                 */

                patch.addPoint(*(new Point(raioStack2 * sinf(angle1), alturaS2, raioStack2 * cosf(angle1))));
                patch.addPoint(*(new Point(raioStack1 * sinf(angle2), alturaS, raioStack1 * cosf(angle2))));
                patch.addPoint(*(new Point(raioStack2 * sinf(angle2), alturaS2, raioStack2 * cosf(angle2))));

                /*
                normal.push_back(new Point(sinf(angle1), deltav, cosf(angle1)));
                normal.push_back(new Point(sinf(angle2), deltav, cosf(angle2)));
                normal.push_back(new Point(sinf(angle2), deltav, cosf(angle2)));

                 texture.push_back(new Point(i*texth, (j+1)*textv, 0));
                texture.push_back(new Point((i+1)*texth, j*textv, 0));
                texture.push_back(new Point((i+1)*texth, (j+1)*textv, 0));
                 */
            }
            else{
                patch.addPoint(*(new Point(raioStack1 * sinf(angle1), alturaS, raioStack1 * cosf(angle1))));
                patch.addPoint(*(new Point(raioStack1 * sinf(angle2), alturaS, raioStack1 * cosf(angle2))));
                patch.addPoint(*(new Point(0, y, 0)));

                /*
                normal.push_back(new Point(sinf(angle1), deltav, cosf(angle1)));
                normal.push_back(new Point(sinf(angle2), deltav, cosf(angle2)));
                normal.push_back(new Point(sinf(angle2), deltav, cosf(angle2)));

                 texture.push_back(new Point(i*texth, j*textv, 0));
                texture.push_back(new Point((i+1)*texth, j*textv, 0));
                texture.push_back(new Point(i*texth, (j+1)*textv, 0));
                 */
            }
            model.addPatch(patch);
        }
    }
    model.writeToFile(filename);
}

void sphere(float radius, int slices, int stacks, string filename){
    Model model;
    float deltah = (2.0f*(float)M_PI/(float)slices), deltav = (float)M_PI/(float) stacks;
    for(int i=0; i<slices; i++){
        for(int j=0; j<stacks; j++) {
            float beta1 = (float) i * deltah, beta2 = (float) (i + 1) * deltah;
            float theta1 = (float) j * deltav, theta2 = (float) (j + 1) * deltav;
            float textv = (float) 1 / (float) stacks, texth = (float) 1 / (float) slices;
            Patch patch;
            if (j == 0) {
                //triangulo de cima
                patch.addPoint(*(new Point(0, radius, 0)));
                patch.addPoint(*(new Point(radius*sinf(theta2)*sinf(beta1),radius*cosf(theta2),radius*sinf(theta2)*cosf(beta1))));
                patch.addPoint(*(new Point(radius*sinf(theta2)*sinf(beta2),radius*cosf(theta2),radius*sinf(theta2)*cosf(beta2))));

                /*
                normal.push_back(new Point(0, 1, 0));
                normal.push_back(new Point(sinf(theta2)*sinf(beta1),cosf(theta2),sinf(theta2)*cosf(beta1)));
                normal.push_back(new Point(sinf(theta2)*sinf(beta2),cosf(theta2),sinf(theta2)*cosf(beta2)));

                 texture.push_back(new Point(j*textV, i*textH, 0));
                texture.push_back(new Point(j*textV, (i+1)*textH, 0));
                texture.push_back(new Point((j+1)*textV, (i+1)*textH, 0));
                 */
            } else if (j == stacks - 1) {
                //triangulo de baixo
                patch.addPoint(*(new Point(radius*sinf(theta2)*sinf(beta2), radius*cosf(theta2), radius*sinf(theta2)*cosf(beta2))));
                patch.addPoint(*(new Point(radius*sinf(theta2)*sinf(beta1), radius*cosf(theta2), radius*sinf(theta2)*cosf(beta1))));
                patch.addPoint(*(new Point(0, -radius, 0)));

                /*
                normal.push_back(new Point(sinf(theta2)*sinf(beta2), cosf(theta2), sinf(theta2)*cosf(beta2)));
                normal.push_back(new Point(sinf(theta2)*sinf(beta1), cosf(theta2), sinf(theta2)*cosf(beta1)));
                normal.push_back(new Point(0,-1,0));

                 texture.push_back(new Point((j+1)*textV, (i+1)*textH, 0));
                texture.push_back(new Point(j*textV, (i+1)*textH, 0));
                texture.push_back(new Point(j*textV, i*textH, 0));
                 */

            } else{
                patch.addPoint(*(new Point(radius*sinf(theta1)*sinf(beta1), radius*cosf(theta1), radius*sinf(theta1)*cosf(beta1))));
                patch.addPoint(*(new Point(radius*sinf(theta2)*sinf(beta1), radius*cosf(theta2), radius*sinf(theta2)*cosf(beta1))));
                patch.addPoint(*(new Point(radius*sinf(theta2)*sinf(beta2), radius*cosf(theta2), radius*sinf(theta2)*cosf(beta2))));

                /*
                normal.push_back(new Point(sinf(theta1)*sinf(beta1), cosf(theta1), sinf(theta1)*cosf(beta1)));
                normal.push_back(new Point(sinf(theta2)*sinf(beta1), cosf(theta2), sinf(theta2)*cosf(beta1)));
                normal.push_back(new Point(sinf(theta2)*sinf(beta2), cosf(theta2), sinf(theta2)*cosf(beta2)));

                texture.push_back(new Point(j*textV, i*textH, 0));
                texture.push_back(new Point(j*textV, (i+1)*textH, 0));
                texture.push_back(new Point((j+1)*textV, (i+1)*textH, 0));
                 */

                patch.addPoint(*(new Point(radius*sinf(theta1)*sinf(beta2), radius*cosf(theta1), radius*sinf(theta1)*cosf(beta2))));
                patch.addPoint(*(new Point(radius*sinf(theta1)*sinf(beta1), radius*cosf(theta1), radius*sinf(theta1)*cosf(beta1))));
                patch.addPoint(*(new Point(radius*sinf(theta2)*sinf(beta2), radius*cosf(theta2), radius*sinf(theta2)*cosf(beta2))));

                /*
                normal.push_back(new Point(sinf(theta1)*sinf(beta2), cosf(theta1), sinf(theta1)*cosf(beta2)));
                normal.push_back(new Point(sinf(theta1)*sinf(beta1), cosf(theta1), sinf(theta1)*cosf(beta1)));
                normal.push_back(new Point(sinf(theta2)*sinf(beta2), cosf(theta2), sinf(theta2)*cosf(beta2)));

                texture.push_back(new Point((j+1)*textV, i*textH, 0));
                texture.push_back(new Point(j*textV, i*textH, 0));
                texture.push_back(new Point((j+1)*textV, (i+1)*textH, 0));
                 */
            }
            model.addPatch(patch);
        }
    }
    model.writeToFile(filename);
}

void tronco(float radius1, float radius2, float height, int slices, int stacks, string filename){
    Model model;
    float deltah = (2.0f*(float)M_PI/(float)slices), deltav = height/(float) stacks, deltaRaio = abs(radius1-radius2)/(float) stacks;
    float y=height/2;
    float  alturaS,alturaS2;
    float normalAlt = deltav;

    for(int j=0; j<stacks; j++){
        for(int i=0; i<slices; i++){
            float angle1 = (float) i * deltah, angle2 = (float) (i + 1) * deltah;
            Patch patch;
            if(j == 0) {
                //base
                patch.addPoint(*(new Point(0.0f, -y, 0.0f)));
                patch.addPoint(*(new Point(radius2 * sinf(angle2), -y, radius2 * cosf(angle2))));
                patch.addPoint(*(new Point(radius2 * sinf(angle1), -y, radius2 * cosf(angle1))));

                /*
                normal.push_back(new Point(0, -1, 0));
                normal.push_back(new Point(0, -1, 0));
                normal.push_back(new Point(0, -1, 0));

                texture.push_back(new Point(0.8125, 0.1875, 0));
                texture.push_back(new Point(0.8125 + 0.1875*sinf(angle2), 0.1875 + 0.1875*cosf(angle2), 0));
                texture.push_back(new Point(0.8125 + 0.1875*sinf(angle1), 0.1875 + 0.1875*cosf(angle1), 0));
                 */
            }
            //laterais
            float raioStack1 = radius2 - (float) j * deltaRaio;
            float raioStack2 = radius2 - (float) (j+1) * deltaRaio;
            float textv = (float)(1-0.375) / (float)stacks, texth = (float) 1 / (float) slices;
            if(radius1>radius2){
                raioStack1 = radius2 + (float) j * deltaRaio;
                raioStack2 = radius2 + (float) (j+1) * deltaRaio;
                normalAlt = -deltav;
            }
            alturaS = -y + (float) j * deltav;
            alturaS2 = -y + (float) (j+1) * deltav;
            if (j == stacks-1) {
                patch.addPoint(*(new Point(0.0f, y, 0.0f)));
                patch.addPoint(*(new Point(radius1 * sinf(angle1), y, radius1 * cosf(angle1))));
                patch.addPoint(*(new Point(radius1 * sinf(angle2), y, radius1 * cosf(angle2))));

                /*
                normal.push_back(new Point(0, 1, 0));
                normal.push_back(new Point(0, 1, 0));
                normal.push_back(new Point(0, 1, 0));

                 texture.push_back(new Point(0.4375, 0.1875, 0));
                texture.push_back(new Point(0.4375 + 0.1875*sinf(angle1), 0.1875 + 0.1875*cosf(angle1), 0));
                texture.push_back(new Point(0.4375 + 0.1875*sinf(angle2), 0.1875 + 0.1875*cosf(angle2), 0));
                 */
            }

            patch.addPoint(*(new Point(raioStack1 * sinf(angle1), alturaS, raioStack1 * cosf(angle1))));
            patch.addPoint(*(new Point(raioStack1 * sinf(angle2), alturaS, raioStack1 * cosf(angle2))));
            patch.addPoint(*(new Point(raioStack2 * sinf(angle1), alturaS2, raioStack2 * cosf(angle1))));

            /*
            normal.push_back(new Point(sinf(angle1), normalAlt, cosf(angle1)));
            normal.push_back(new Point(sinf(angle2), normalAlt, cosf(angle2)));
            normal.push_back(new Point(sinf(angle1), normalAlt, cosf(angle1)));

             texture.push_back(new Point(j*textV, 0.375 + i*textH, 0));
            texture.push_back(new Point((j+1)*textV, 0.375 + i*textH, 0));
            texture.push_back(new Point(j*textV, 0.375 + (i+1)*textH, 0));
            */

            patch.addPoint(*(new Point(raioStack2 * sinf(angle1), alturaS2, raioStack2 * cosf(angle1))));
            patch.addPoint(*(new Point(raioStack1 * sinf(angle2), alturaS, raioStack1 * cosf(angle2))));
            patch.addPoint(*(new Point(raioStack2 * sinf(angle2),alturaS2, raioStack2 * cosf(angle2))));

            /*
            normal.push_back(new Point(sinf(angle1), normalAlt, cosf(angle1)));
            normal.push_back(new Point(sinf(angle2), normalAlt, cosf(angle2)));
            normal.push_back(new Point(sinf(angle2), normalAlt, cosf(angle2)));

             texture.push_back(new Point(j*textV, 0.375 + (i+1)*textH, 0));
            texture.push_back(new Point((j+1)*textV, 0.375 + i*textH, 0));
            texture.push_back(new Point((j+1)*textV, 0.375 + (i+1)*textH, 0));
             */

            model.addPatch(patch);
        }
    }
    model.writeToFile(filename);
}

void anel(float radius1, float radius2, int slices, string filename){
    Model model;
    float deltah = (2.0f*(float)M_PI/(float)slices);
    float y=0;

    if (radius1 < radius2){
        float temp = radius2;
        radius2 = radius1;
        radius1 = temp;
    }

    for(int i=0; i<slices; i++) {
        float angle1 = (float) i * deltah, angle2 = (float) (i + 1) * deltah;
        Patch patch;

        patch.addPoint(*(new Point(radius2 * sinf(angle1), y, radius2 * cosf(angle1))));
        patch.addPoint(*(new Point(radius1 * sinf(angle2), y, radius1 * cosf(angle2))));
        patch.addPoint(*(new Point(radius2 * sinf(angle2), y, radius2 * cosf(angle2))));

        /*
        normal.push_back(new Point(0, 1, 0));
        normal.push_back(new Point(0, 1, 0));
        normal.push_back(new Point(0, 1, 0));

        texture.push_back(new Point(0, 1, 0));
        texture.push_back(new Point(1, 0, 0));
        texture.push_back(new Point(1, 1, 0));
        */

        patch.addPoint(*(new Point(radius2 * sinf(angle1), y, radius2 * cosf(angle1))));
        patch.addPoint(*(new Point(radius1 * sinf(angle1), y, radius1 * cosf(angle1))));
        patch.addPoint(*(new Point(radius1 * sinf(angle2), y, radius1 * cosf(angle2))));

        /*
        normal.push_back(new Point(0, 1, 0));
        normal.push_back(new Point(0, 1, 0));
        normal.push_back(new Point(0, 1, 0));

        texture.push_back(new Point(0, 1, 0));
        texture.push_back(new Point(0, 0, 0));
        texture.push_back(new Point(1, 0, 0));
        */

        model.addPatch(patch);
    }
    model.writeToFile(filename);
}



int main(int argc, char const *argv[]) {
    if(argc == 3) {
        string filename = argv[1];
        int tesselation = stoi(argv[2]);
        Model model = Model(filename);
        model.tessellate(tesselation, filename);
    }
    if (argc == 5 && strcmp(argv[1], "plane") == 0) {
        plane(
            atof(argv[2]),
            atoi(argv[3]),
            argv[4]
        );
        return 0;
    } else if (argc == 5 && strcmp(argv[1], "box") == 0) {
        box(
            atof(argv[2]),
            atoi(argv[3]),
            argv[4]
        );
        return 0;
    } else if (argc == 7 && strcmp(argv[1], "cone") == 0) {
        cone(
            atof(argv[2]),
            atof(argv[3]),
            atoi(argv[4]),
            atoi(argv[5]),
            argv[6]
        );
        return 0;
    } else if (argc == 6 && strcmp(argv[1], "sphere") == 0) {
        sphere(
            atof(argv[2]),
            atoi(argv[3]),
            atoi(argv[4]),
            argv[5]
        );
        return 0;
    }  else if (argc == 8 && strcmp(argv[1], "tronco") == 0) {
        tronco(
                atof(argv[2]),
                atof(argv[3]),
                atof(argv[4]),
                atoi(argv[5]),
                atoi(argv[6]),
                argv[7]
        );
        return 0;
    } else if (argc == 6 && strcmp(argv[1], "anel") == 0) {
        anel(
                atof(argv[2]),
                atof(argv[3]),
                atoi(argv[4]),
                argv[5]
        );
        return 0;

    }
    return 0;
}

//
// Created by Mathis Saillot on 09/07/2022.
//

#ifndef HACKNSLPROJECT_DESSINATEURSTATIONTYPE_H
#define HACKNSLPROJECT_DESSINATEURSTATIONTYPE_H

#include <StationType.h>
#include <FenetreMonde.h>

class DessinateurStationType {
public:
    static void dessineStationType(FenetreMonde * fenetre, const StationType & type, const Vecteur2D<double> & center,
                                   double rayon, const Couleur & couleur, int epaisseurTraitEnPixel) {
        switch (type) {
            case SQUARE:
                fenetre->dessineSquareSimple(center, rayon, couleur, epaisseurTraitEnPixel);
                break;
            case CIRCLE:
                fenetre->dessineCercle(center, rayon, couleur, epaisseurTraitEnPixel);
                break;
            case PENTAGONE:
                fenetre->dessinePentagoneSimple(center, rayon, couleur, epaisseurTraitEnPixel);
                break;
            case TRIANGLE:
                fenetre->dessineTriangleSimple(center, rayon, couleur, epaisseurTraitEnPixel);
                break;
            default:
                fenetre->dessineCrossSimple(center, rayon, couleur, epaisseurTraitEnPixel);
                break;
        }
    }
};

#endif //HACKNSLPROJECT_DESSINATEURSTATIONTYPE_H

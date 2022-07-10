//
// Created by Mathis Saillot on 09/07/2022.
//

#include "FenetreMonde.h"

Vecteur2D<double> FenetreMonde::pentagone_corners[5] = {
        Vecteur2D<double>(cos(M_PI / 2), sin(M_PI / 2)),
        Vecteur2D<double>(cos(9 * M_PI / 10), sin(9 * M_PI / 10)),
        Vecteur2D<double>(cos(13 * M_PI / 10), sin(13 * M_PI / 10)),
        Vecteur2D<double>(cos(17 * M_PI / 10), sin(17 * M_PI / 10)),
        Vecteur2D<double>(cos(21 * M_PI / 10), sin(21 * M_PI / 10))
};

Vecteur2D<double> FenetreMonde::square_corners[4] = {
        Vecteur2D<double>(cos(M_PI / 4), sin(M_PI / 4)),
        Vecteur2D<double>(cos(3 * M_PI / 4), sin(3 * M_PI / 4)),
        Vecteur2D<double>(cos(5 * M_PI / 4), sin(5 * M_PI / 4)),
        Vecteur2D<double>(cos(7 * M_PI / 4), sin(7 * M_PI / 4))
};

Vecteur2D<double> FenetreMonde::triangle_corners[3] = {
        Vecteur2D<double>(cos(M_PI / 2), sin(M_PI / 2)),
        Vecteur2D<double>(cos(7 * M_PI / 6), sin(7 * M_PI / 6)),
        Vecteur2D<double>(cos(11 * M_PI / 6), sin(11 * M_PI / 6))
};

void
FenetreMonde::dessineTriangleSimple(const Vecteur2D<double> &centre, double rayon, const Couleur &couleur,
                      int epaisseurTraitEnPixel) {
    dessinePolygoneSimple(centre, triangle_corners, 3, rayon, couleur, epaisseurTraitEnPixel);
}

void FenetreMonde::dessineSquareSimple(const Vecteur2D<double> &centre, double rayon, const Couleur &couleur,
                         int epaisseurTraitEnPixel) {
    dessinePolygoneSimple(centre, square_corners, 4, rayon, couleur, epaisseurTraitEnPixel);
}

void FenetreMonde::dessineCrossSimple(const Vecteur2D<double> &centre, double rayon, const Couleur &couleur,
                        int epaisseurTraitEnPixel) {
    for (int i = 0; i < 2; ++i) {
        dessineSegment(centre + square_corners[i] * rayon,
                       centre + square_corners[(i + 2)] * rayon, couleur, epaisseurTraitEnPixel);
    }

}

void
FenetreMonde::dessinePentagoneSimple(const Vecteur2D<double> &centre, double rayon, const Couleur &couleur,
                       int epaisseurTraitEnPixel) {
    dessinePolygoneSimple(centre, pentagone_corners, 5, rayon, couleur, epaisseurTraitEnPixel);
}

void
FenetreMonde::dessinePolygoneSimple(const Vecteur2D<double> &centre, const Vecteur2D<double> *corners, int size,
                                    double rayon, const Couleur &couleur, int epaisseurTraitEnPixel) {
    for (int i = 0; i < size; ++i) {
        dessineSegment(centre + corners[i] * rayon,
                                centre + corners[(i + 1) % size] * rayon, couleur, epaisseurTraitEnPixel);
    }
}
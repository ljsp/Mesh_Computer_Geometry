//
// Created by lucas on 18/09/23.
//
#include <iostream>
#include "Include/mesh.h"

int main() {
    Mesh titi;
    titi.loadOFF("../Asset/queen.off");
    Mesh::Iterator_on_vertices itv(titi.vertices_begin());
    Mesh::Circulator_on_faces cf(titi.incident_faces(*itv));
    for (itv=titi.vertices_begin(); itv != titi.vertices_past_the_end(); ++itv)
    {
        Mesh::Circulator_on_faces cfbegin = titi.incident_faces(*itv);
        int cmpt=0 ;
        for (cf = cfbegin; cf != cfbegin; cf++) {
            cmpt++;
        }
        std::cout<< "valence of the vertex " << cmpt <<std::endl ;
    }
    /*Mesh::Iterator_on_faces itf(titi.faces_begin());
    for (itf=titi.faces_begin();
             itf != titi.faces_past_the_end();
             ++itf)
        {
            std::cout << "ID of the face " << itf.it->adjacentTrianglesId[0] << " " <<
                      "made with the points " << itf.it->vertices[0] << " " << itf.it->vertices[1] <<
                      " " << itf.it->vertices[2] << std::endl ;
        }*/
}
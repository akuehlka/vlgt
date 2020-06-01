/* 
 * File:   main.cpp
 * Author: andrey
 *
 * Created on 7 de Março de 2012, 11:44
 */

#include <cstdlib>
#include <iostream>

#include "testaWebCam.h"
#include "testaToGray.h"
#include "testaFaceDetector.h"
#include "testaModeloFace.h"
#include "testaOlhos.h"
#include "ExperimentRunner.h"
#include "testeSolvePoly.h"
#include "realTimeTracker.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    cout << "Visible Light Gaze Tracker v. 0.1.\n";
    
//    if (!testaWebCam()) {
//        cerr << "Erro testando a webcam.\n";
//        return 1;
//    } else
//        cout << "Sucesso!\n";
// ======================================
//    if (!testaToGray()) {
//        cerr << "Erro testando toGray.\n";
//        return 1;
//    } else
//        cout << "Sucesso!\n";
// ======================================
//    if (!testaFaceDetector()) {
//        cerr << "Erro testando FaceDetector.\n";
//        return 1;
//    } else
//        cout << "Sucesso!\n";
// ======================================
    if (!testaModeloFace(3)) {
        cerr << "Erro testando Modelo de face.\n";
        return 1;
    } else
        cout << "Sucesso!\n";
// ======================================
//    if (!experimentRunner()) {
//        cerr << "Erro rodando experimento.\n";
//        return 1;
//    } else
//        cout << "Sucesso!\n";
// ======================================
//    if (!testeSolvePoly()) {
//        cerr << "Erro rodando experimento.\n";
//        return 1;
//    } else
//        cout << "Sucesso!\n";
// ======================================
//    if (!realTimeTracker()) {
//        cerr << "Erro testando Real Time Tracker.\n";
//        return 1;
//    } else
//        cout << "Sucesso!\n";
// ======================================
//    if (!testaOlhos()) {
//        cerr << "Erro testando Detecção dos olhos.\n";
//        return 1;
//    } else
//        cout << "Sucesso!\n";

    return 0;
}


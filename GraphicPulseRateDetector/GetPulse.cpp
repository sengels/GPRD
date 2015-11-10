#pragma once
//#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include "highgui.hpp"
#include "stdafx.h"
#include <list>
#include <iostream>

double GetPulse(cv::Mat timeVector) //RGB Wert rausholen aus cv Mat in bekanntes Format
{
	double ret = 0;
	cv::_OutputArray output;
	/*std::list<int>vectorValues(600);
	int x = 0, y = 0;
	
	for (cv::MatConstIterator it = timeVector.begin(); it != timeVector.end(); ++it) 
	{
		//Funktion die aus einer Matrix einen Wert errechnet

		int value = computeValue(*it, x, y); //Liest Wert an der Stelle (x,y) aus und schreibt ihn in value

		vectorValues.push_back(value);		//erstellt eine Liste vectorValues mit Inhalten von values
	}

	int inputArray[600];
	*/
	//list2array(inputArray, vectorValues);

	//output = cv::compareHist(inputArray,...);
	cv::dft(timeVector, output, cv::DFT_ROWS, 600);		//DFT_SCALE? cv array
	//geht erst im Nachhinein. Funktion erwartet openCV format
	//vectorElement = ein Element aus der Matrix mit Koordinaten (x,y)

		return 0;
}

//Bild einlesen -> cv-Format -> Bild bearbeiten mit openCV Funktionen/Filter 
//-> RGB mit 3 Dimensionen Listenarray speichern (typ den ich kenne) Kopieren -> Manipulieren
//-> Zurück in OpenCV Format
//Mat > Array
/*
int computeValue(cv::Mat frame, int x, int y)
{
	int value;
	unsigned char *input = (unsigned char*)(frame.data);

	value = input[frame.step*x + y];

	return value;
}

int list2array(int inputArray[], std::list<int>vectorValues) //list2array(dst, src)
{
	//http://stackoverflow.com/questions/2087582/converting-stdlist-to-c-friendly-type
	
	*inputArray = new int[vectorValues.size()];
	copy(vectorValues.begin(), vectorValues.end(), inputArray);

	//return 
}*/
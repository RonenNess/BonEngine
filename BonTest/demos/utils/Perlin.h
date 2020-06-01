#pragma once

double Noise(int i, int x, int y);

double SmoothedNoise(int i, int x, int y);
double Interpolate(double a, double b, double x);

double InterpolatedNoise(int i, double x, double y);
double ValueNoise_2D(double x, double y);
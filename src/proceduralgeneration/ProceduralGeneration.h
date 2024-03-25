#pragma once
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include <cmath>
namespace pg 
{
   float Noise(unsigned int x);
   float Interpolate(float a, float b, float x);
   float InterpolateNoise(float x);
   float PerlinNoise1D(float x, float persistence, int n);
   float SmoothedNoise(float x);
   float QuanticCurve(float x);


}